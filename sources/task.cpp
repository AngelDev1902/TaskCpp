#include "../headers/task.h"

Task::Task(QFrame *parent, int id, QString title, QString description, QString date, QString time) :
        QFrame(parent),
        id(id),
        title(title),
        description(description),
        date(date),
        time(time){
    setStyleSheet("QFrame { border-radius: 10px; border: 1px solid #000000; background-color: #202020; color: #ffffff; }");

    layout = new QGridLayout(this);

    initComponents();
}

// Método para inicializar los componentes de la tarea y darles estilo
void Task::initComponents() {
    QLabel *titleLabel = new QLabel();
    titleLabel->setText("Tarea : " + title);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold;");
    titleLabel->setFixedWidth(maximumWidth() - 30);

    QLabel *descriptionLabel = new QLabel(description);
    descriptionLabel->setStyleSheet("font-size: 14px;");
    descriptionLabel->setFixedWidth(maximumWidth() - 30);

    QLabel *dateLabel = new QLabel(date);
    dateLabel->setStyleSheet("font-size: 14px;");
    dateLabel->setFixedWidth(maximumWidth() - 30);

    QLabel *timeLabel = new QLabel(time);
    timeLabel->setStyleSheet("font-size: 14px;");
    timeLabel->setFixedWidth(maximumWidth() - 30);

    editTaskButton = new QPushButton("+");
    editTaskButton->setStyleSheet("background-color: #05A7D6; color: #ffffff; font-size: 20px; font-weight: bold;");
    editTaskButton->setFixedSize(30, 30);

    // Conexion que reacciona al click del botón y emite la señal con el id de la tarea
    QObject::connect(editTaskButton, &QPushButton::clicked, this, [=](){
        emit emitId(id);
    });

    deleteTaskButton = new QPushButton("X");
    deleteTaskButton->setStyleSheet("background-color: #D60505; color: #ffffff; font-size: 20px; font-weight: bold;");
    deleteTaskButton->setFixedSize(30, 30);

    // Conexion que reacciona al click del botón y emite la señal con el id de la tarea
    QObject::connect(deleteTaskButton, &QPushButton::clicked, this, [=](){
        emit emitId(id);
    });

    // Checkbox para marcar la tarea como completada
    QCheckBox *completeTask = new QCheckBox();
    completeTask->setFixedSize(30, 30);

    // Distribucion de los componentes en el layout
    layout->addWidget(titleLabel, 0, 0, 1, 1);
    layout->addWidget(descriptionLabel, 1, 0, 1, 1);
    layout->addWidget(dateLabel, 2, 0, 1, 1);
    layout->addWidget(timeLabel, 3, 0, 1, 1);

    layout->addWidget(editTaskButton, 0, 1, 1, 3);
    layout->addWidget(deleteTaskButton, 1, 1, 1, 3);
    layout->addWidget(completeTask, 2, 1, 1, 3);
}

// Método para actualizar los datos de la tarea a partir de los parámetros recibidos
void Task::updateDates(QString title, QString description, QString date, QString time) {
    this->title = title;
    this->description = description;
    this->date = date;
    this->time = time;
}

Task::~Task() {
    delete layout;
    delete editTaskButton;
    delete deleteTaskButton;
}
