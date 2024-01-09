#include "../headers/myday.h"

MyDay::MyDay(QWidget *parent, QString userName) : AllTask(parent, userName) {
    // Llamada al constructor de la clase base (AllTask)
    titleLabel->setText("Estas son tus tareas de hoy");

    // Luego de la llamada al constructor de la clase base, realiza la lectura de las tareas
    readTasksFile();
}

void MyDay::viewTasks() {
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString currentDate = currentDateTime.date().toString("dd MMMM yyyy");

    // Eliminar todas las tareas existentes del layout
    QLayoutItem *child;
    while ((child = tasksFrame->layout()->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    QLabel *dateLabel = new QLabel(currentDate);
    dateLabel->setStyleSheet("color: #ffffff; font-size: 20px; font-weight: bold;");
    dateLabel->setAlignment(Qt::AlignCenter);
    dateLabel->setFixedHeight(50);

    tasksFrame->layout()->addWidget(dateLabel);

    for (const auto &task : *tasksList) {
        if (task && task->getDate() == currentDate) {
            QPointer<Task> taskCopy = new Task(nullptr, task->getId(), task->getTitle(), task->getDescription(), task->getDate(), task->getTime());

            QObject::connect(taskCopy.data(), &Task::deleteTaskSignal, this, &AllTask::deleteTask);
            QObject::connect(taskCopy.data(), &Task::editTaskSignal, this, &AllTask::editTask);

            tasksFrame->layout()->addWidget(taskCopy.data());
        }
    }
}

MyDay::~MyDay() {
    // Destructor (si es necesario agregar alguna limpieza específica)
}
