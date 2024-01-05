#include "taskday.h"

TaskDay::TaskDay(QFrame *parent, int id, QString title, QString description, QString date, QString time) :
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

void TaskDay::initComponents() {
    QLabel *titleLabel = new QLabel();
    titleLabel->setText("Tarea " + QString::number(id) + ": " + title);
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

    QObject::connect(editTaskButton, &QPushButton::clicked, this, [=](){ editTask(); });

    deleteTaskButton = new QPushButton("X");
    deleteTaskButton->setStyleSheet("background-color: #D60505; color: #ffffff; font-size: 20px; font-weight: bold;");
    deleteTaskButton->setFixedSize(30, 30);

    QObject::connect(deleteTaskButton, &QPushButton::clicked, this, [=](){ deleteTask(); });

    QCheckBox *completeTask = new QCheckBox();
    completeTask->setFixedSize(30, 30);

    layout->addWidget(titleLabel, 0, 0, 1, 1);
    layout->addWidget(descriptionLabel, 1, 0, 1, 1);
    layout->addWidget(dateLabel, 2, 0, 1, 1);
    layout->addWidget(timeLabel, 3, 0, 1, 1);

    layout->addWidget(editTaskButton, 0, 1, 1, 3);
    layout->addWidget(deleteTaskButton, 1, 1, 1, 3);
    layout->addWidget(completeTask, 2, 1, 1, 3);
}

void TaskDay::deleteTask() {
    emit deleteTaskSignal(id);
}

void TaskDay::editTask() {
    emit editTaskSignal(id);
}

void TaskDay::updateDates(QString title, QString description, QString date, QString time) {
    this->title = title;
    this->description = description;
    this->date = date;
    this->time = time;
}

TaskDay::~TaskDay() {

}
