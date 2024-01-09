#include "../headers/alltasks.h"

AllTask::AllTask(QWidget *parent, QString userName) :
        QWidget(parent),
        userName(userName){

    QDateTime currentDateTime = QDateTime::currentDateTime(); // Obtener la fecha y hora actuales
    QDate currentDate = currentDateTime.date(); // Obtener la fecha actual
    dateString = currentDate.toString("dd MMMM yyyy"); // extraer con cierto formato la fecha actual
    timeString = currentDateTime.toString("hh:mm"); // extraer con cierto formato la hora actual

    layout = new QGridLayout(this); // Crear el layout de la ventana

    file = new QFile("../assets/" + userName + ".txt");
    datesList = new QList<QString>();

    tasksList = new QList<QPointer<Task>>();

    initComponents();
    readTasksFile();
}

void AllTask::initComponents() {
    titleLabel = new QLabel("¡Estas son todas tus tareas!");
    titleLabel->setStyleSheet("color: #ffffff; font-size: 30px; font-weight: bold;");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setFixedHeight(50);

    // Frame para las tareas
    tasksFrame = new QFrame();

    // Layout para las tareas
    QVBoxLayout *tasksLayout = new QVBoxLayout(tasksFrame);
    tasksLayout->setAlignment(Qt::AlignTop);
    tasksLayout->setMargin(50);

    QPushButton *addTask = new QPushButton("Agregar Tarea");
    addTask->setStyleSheet("background-color: #ffffff; color: #000000; font-size: 20px; font-weight: bold;");

    QObject::connect(addTask, &QPushButton::clicked, this, &AllTask::createNewTask);

    layout->addWidget(titleLabel, 0, 0, 1, 1);
    layout->addWidget(tasksFrame, 1, 0, 1, 1);
    layout->addWidget(addTask, 2, 0, 1, 1);
}

void AllTask::readTasksFile() {
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
            }
        }

        file->close();
    }

    viewTasks();
}

void AllTask::viewTasks() {
    // Obtenemos todas las fechas de las tareas
    getDates();

    // Eliminar todas las tareas existentes del layout
    QLayoutItem *child;
    while ((child = tasksFrame->layout()->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    for (const auto &date: *datesList) {
        if (date != "") {
            QLabel *dateLabel = new QLabel(date);
            dateLabel->setStyleSheet("color: #ffffff; font-size: 20px; font-weight: bold;");
            dateLabel->setAlignment(Qt::AlignCenter);
            dateLabel->setFixedHeight(50);

            tasksFrame->layout()->addWidget(dateLabel);

            for (const auto &task: *tasksList) {
                if (task && task->getDate() == date) {
                    QPointer<Task> taskCopy = new Task(nullptr, task->getId(), task->getTitle(), task->getDescription(), task->getDate(), task->getTime());

                    QObject::connect(taskCopy.data(), &Task::deleteTaskSignal, this, &AllTask::deleteTask);
                    QObject::connect(taskCopy.data(), &Task::editTaskSignal, this, &AllTask::editTask);

                    tasksFrame->layout()->addWidget(taskCopy.data());
                }
            }
        }
    }

}

void AllTask::getDates() {
    datesList->clear();

    for (const auto &task: *tasksList) {
        if (task) {
            QString date = task->getDate();

            if (!datesList->contains(date)) {
                datesList->append(date);
            }
        }
    }

    std::sort(datesList->begin(), datesList->end(), [](const QString &a, const QString &b) {
        QDate dateA = QDate::fromString(a, "dd MMMM yyyy");
        QDate dateB = QDate::fromString(b, "dd MMMM yyyy");

        return dateA < dateB;
    });
}

void AllTask::createNewTask(){
    int id = getLastId();

    NewTask *newTask = new NewTask();
    newTask->setFixedSize(400, 400);
    newTask->setModal(true);

    newTask->show();

    QObject::connect(newTask, &NewTask::taskCreated, [=](QString title, QString description, QDate date, QTime time) {
        QPointer<Task> task = new Task(nullptr, id + 1, title, description, date.toString("dd MMMM yyyy"), time.toString("hh:mm"));

        tasksList->append(task);

        modifyTasksFile();
    });
}

void AllTask::deleteTask(int taskId) {
    for (const auto &task : *tasksList) {
        if (task && task->getId() == taskId) {
            tasksList->removeOne(task);

            modifyTasksFile();
            break;
        }
    }

}

void AllTask::editTask(int taskId) {
    for (const auto &task : *tasksList) {
        if (task && task->getId() == taskId) {
            QString title = task->getTitle();
            QString description = task->getDescription();
            QString date = task->getDate();
            QString time = task->getTime();

            NewTask *newTask = new NewTask(nullptr, title, description, QDate::fromString(date, "dd MMMM yyyy"), QTime::fromString(time, "hh:mm"));
            newTask->setFixedSize(400, 400);
            newTask->setModal(true);

            newTask->show();

            QObject::connect(newTask, &NewTask::taskCreated, [=](QString newTitle, QString newDescription, QDate newDate, QTime newTime) {
                task->updateDates(newTitle, newDescription, newDate.toString("dd MMMM yyyy") , newTime.toString("hh:mm"));

                modifyTasksFile();
            });

            break;
        }
    }
}

void AllTask::modifyTasksFile() {
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

int AllTask::getLastId() {
    int lastId = 0;

    for (const auto &task : *tasksList) {
        if (task && task->getId() > lastId) {
            lastId = task->getId();
        }
    }

    return lastId;
}

AllTask::~AllTask() {}
