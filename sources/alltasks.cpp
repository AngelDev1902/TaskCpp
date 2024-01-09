#include "../headers/alltasks.h"

AllTask::AllTask(QWidget *parent) :
        QWidget(parent) {

    QLabel *label = new QLabel("MyTasks", this);
    label->setFixedSize(width(), 50);
}

AllTask::~AllTask() {}
