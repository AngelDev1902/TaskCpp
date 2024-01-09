#ifndef TODOLIST_MYDAY_H
#define TODOLIST_MYDAY_H

#include "alltasks.h"

class MyDay : public AllTask {
public:
    explicit MyDay(QWidget *parent = nullptr, QString userName = "User");
    ~MyDay() override;

    void viewTasks() override;
};

#endif //TODOLIST_MYDAY_H
