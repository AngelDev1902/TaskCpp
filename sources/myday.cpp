#include "../headers/myday.h"

MyDay::MyDay(QWidget *parent, QString userName) :
        QWidget(parent),
        userName(userName) {

    QDateTime currentDateTime = QDateTime::currentDateTime(); // Obtener la fecha y hora actuales
    QDate currentDate = currentDateTime.date(); // Obtener la fecha actual
    dateString = currentDate.toString("dd MMMM yyyy"); // extraer con cierto formato la fecha actual
    timeString = currentDateTime.toString("hh:mm"); // extraer con cierto formato la hora actual

    layout = new QGridLayout(this); // Crear el layout de la ventana

    file = new QFile("../assets/" + userName + ".txt");
    numberTask = 1;
    tasksList = new QList<QPointer<Task>>();

    initComponents();
    readTasksFile();
}

void MyDay::initComponents() {
    QLabel *titleLabel = new QLabel("¡Bienvenido a tu dia " + userName + "!");
    titleLabel->setStyleSheet("color: #ffffff; font-size: 30px; font-weight: bold;");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setFixedHeight(50);

    QLabel *dateLabel = new QLabel(dateString);
    dateLabel->setStyleSheet("color: #ffffff; font-size: 20px; font-weight: bold;");
    dateLabel->setAlignment(Qt::AlignCenter);
    dateLabel->setFixedHeight(50);

    // Frame para las tareas
    tasksFrame = new QFrame();

    // Layout para las tareas
    QVBoxLayout *tasksLayout = new QVBoxLayout(tasksFrame);
    tasksLayout->setAlignment(Qt::AlignTop);
    tasksLayout->setMargin(50);

    QPushButton *addTask = new QPushButton("Agregar Tarea");
    addTask->setStyleSheet("background-color: #ffffff; color: #000000; font-size: 20px; font-weight: bold;");

    QObject::connect(addTask, &QPushButton::clicked, this, &MyDay::createNewTask);
    
    layout->addWidget(titleLabel, 0, 0, 1, 1);
    layout->addWidget(dateLabel, 1, 0, 1, 1);
    layout->addWidget(tasksFrame, 2, 0, 1, 1);
    layout->addWidget(addTask, 3, 0, 1, 1);
}

void MyDay::readTasksFile() {
    tasksList->clear();

    if (file->open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(file);

        while (!stream.atEnd()) {
            QString line = stream.readLine();
            QStringList data = line.split(",");

            if (data.size() == 5) {
                int id = data[0].toInt();
                QString title = data[1];
                QString description = data[2];
                QString date = data[3];
                QString time = data[4];

                QPointer<Task> task = new Task(nullptr, id, title, description, date, time);

                tasksList->append(task);
                numberTask++;
            }
        }

        file->close();
    }

    viewTasks();
}

void MyDay::viewTasks() {
    // Eliminar todas las tareas existentes del layout
    QLayoutItem *child;
    while ((child = tasksFrame->layout()->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    // Agregar las tareas copiadas al layout
    for (const auto &task : *tasksList) {
        if (task) {
            QPointer<Task> taskCopy = new Task(nullptr, task->getId(), task->getTitle(), task->getDescription(), task->getDate(), task->getTime());

            QObject::connect(taskCopy.data(), &Task::deleteTaskSignal, this, &MyDay::deleteTask);
            QObject::connect(taskCopy.data(), &Task::editTaskSignal, this, &MyDay::editTask);

            tasksFrame->layout()->addWidget(taskCopy.data());
        }
    }
}

void MyDay::createNewTask(){
    NewTask *newTask = new NewTask();
    newTask->setFixedSize(400, 400);
    newTask->setModal(true);

    newTask->disableDateEdit();

    newTask->show();

    QObject::connect(newTask, &NewTask::taskCreated, [=](QString title, QString description, QDate date, QTime time) {
        QPointer<Task> task = new Task(nullptr, numberTask, title, description, date.toString("dd MMMM yyyy"), time.toString("hh:mm"));

        tasksList->append(task);
        numberTask++;

        modifyTasksFile();
    });
}

void MyDay::deleteTask(int taskId) {
    for (const auto &task : *tasksList) {
        if (task && task->getId() == taskId) {
            tasksList->removeOne(task);

            modifyTasksFile();
            break;
        }
    }

    numberTask--;
}

void MyDay::editTask(int taskId) {
    for (const auto &task : *tasksList) {
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

                modifyTasksFile();
            });

            break;
        }
    }
}

void MyDay::modifyTasksFile() {
    if (file->open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(file);

        for (const auto &task : *tasksList) {
            if (task) {
                stream << task->getId() << "," << task->getTitle() << "," << task->getDescription() << "," << task->getDate() << "," << task->getTime() << "\n";
            }
        }

        file->close();
    }

    viewTasks();
}

MyDay::~MyDay() {
    // Liberar memoria de los elementos del layout
    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    delete layout;
    delete tasksFrame;
    delete file;
}
