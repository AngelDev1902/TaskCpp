#include "myday.h"

int MyDay::numberTask = 1;

MyDay::MyDay(QWidget *parent, QString userName) :
        QWidget(parent),
        userName(userName) {

    QDateTime currentDateTime = QDateTime::currentDateTime(); // Obtener la fecha y hora actuales
    QDate currentDate = currentDateTime.date(); // Obtener la fecha actual
    dateString = currentDate.toString("dd MMMM yyyy"); // extraer con cierto formato la fecha actual
    timeString = currentDateTime.toString("hh:mm"); // extraer con cierto formato la hora actual

    layout = new QGridLayout(this);

    initComponents();
}

void MyDay::initComponents() {
    QLabel *title = new QLabel("Bienvenido a tu dia " + userName + "!");
    title->setStyleSheet("color: #ffffff; font-size: 30px; font-weight: bold;");
    title->setAlignment(Qt::AlignCenter);
    title->setFixedHeight(50);

    QLabel *date = new QLabel(dateString);
    date->setStyleSheet("color: #ffffff; font-size: 20px; font-weight: bold;");
    date->setAlignment(Qt::AlignCenter);
    date->setFixedHeight(50);

    // Frame para las tareas
    tasksFrame = new QFrame();

    // Layout para las tareas
    QVBoxLayout *tasksLayout = new QVBoxLayout(tasksFrame);
    tasksLayout->setAlignment(Qt::AlignTop);
    tasksLayout->setMargin(50);

    QPushButton *addTask = new QPushButton("Agregar Tarea");
    addTask->setStyleSheet("background-color: #ffffff; color: #000000; font-size: 20px; font-weight: bold;");
    QObject::connect(addTask, SIGNAL(clicked(bool)), this, SLOT(createNewTaskButton()));
    
    layout->addWidget(title, 0, 0, 1, 1);
    layout->addWidget(date, 1, 0, 1, 1);
    layout->addWidget(tasksFrame, 2, 0, 1, 1);
    layout->addWidget(addTask, 3, 0, 1, 1);
}

void MyDay::viewTasks() {

    // Eliminar todas las tareas existentes del layout
    QLayoutItem *child;
    while ((child = tasksFrame->layout()->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    // Agregar las tareas copiadas al layout
    for (const auto &task : tasksList) {
        if (task) {
            QPointer<TaskDay> taskCopy = new TaskDay(nullptr, task->getId(), task->getTitle(), task->getDescription(), task->getDate(), task->getTime());

            QObject::connect(taskCopy.data(), SIGNAL(deleteTaskSignal(int)), this, SLOT(deleteTaskFromList(int)));
            QObject::connect(taskCopy.data(), SIGNAL(editTaskSignal(int)), this, SLOT(editTaskFromList(int)));

            tasksFrame->layout()->addWidget(taskCopy.data());
        }
    }
}

void MyDay::createNewTaskButton(){
    NewTask *newTask = new NewTask();
    newTask->setFixedSize(400, 400);
    newTask->setModal(true);

    newTask->disableDateEdit();

    newTask->show();

    QObject::connect(newTask, SIGNAL(taskCreated(QString, QString, QDate, QTime)), this, SLOT(createNewTask(QString, QString, QDate, QTime)));
}

void MyDay::createNewTask(const QString &title, const QString &description, const QDate &date, const QTime &time) {
    QPointer<TaskDay> task = new TaskDay(nullptr, numberTask, title, description, date.toString("dd MMMM yyyy"), time.toString("hh:mm"));
    tasksList.append(task);

    viewTasks();
    numberTask++;
}


void MyDay::deleteTaskFromList(int taskId) {
    for (const auto &task : tasksList) {
        if (task && task->getId() == taskId) {
            tasksList.removeOne(task);

            viewTasks();
            break;
        }
    }
}

void MyDay::editTaskFromList(int taskId) {
    for (const auto &task : tasksList) {
        if (task && task->getId() == taskId) {
            QString title = task->getTitle();
            QString description = task->getDescription();
            QString date = task->getDate();
            QString time = task->getTime();

            NewTask *newTask = new NewTask(nullptr, title, description, QDate::fromString(date, "dd MMMM yyyy"), QTime::fromString(time, "hh:mm"));
            newTask->setFixedSize(400, 400);
            newTask->setModal(true);

            newTask->disableDateEdit();

            newTask->show();

            QObject::connect(newTask, &NewTask::taskCreated, [=](QString newTitle, QString newDescription, QDate newDate, QTime newTime) {
                task->updateDates(newTitle, newDescription, newDate.toString("dd MMMM yyyy") , newTime.toString("hh:mm"));
                viewTasks();
            });

            break;
        }
    }
}

MyDay::~MyDay() {
    // Liberar memoria de los elementos del layout
    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    // Liberar memoria de los elementos del layout
    QLayoutItem *child2;
    while ((child2 = tasksFrame->layout()->takeAt(0)) != nullptr) {
        delete child2->widget();
        delete child2;
    }

}
