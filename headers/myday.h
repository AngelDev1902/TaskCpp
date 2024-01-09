#ifndef TODOLIST_MYDAY_H
#define TODOLIST_MYDAY_H

#include <QWidget>
#include <QDate>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QFrame>
#include <QPushButton>
#include <QLabel>
#include <QPointer>
#include <QFile>
#include <QTextStream>

#include "task.h"
#include "newtask.h"

class MyDay : public QWidget {
Q_OBJECT

private:
    QGridLayout *layout;
    QString dateString;
    QString timeString;
    QFrame *tasksFrame;
    QList<QPointer<Task>> *tasksList;

    QFile *file;

    QString userName;
    int numberTask;

public:
    explicit MyDay(QWidget *parent = nullptr, QString userName = "User");
    ~MyDay() override;

    void initComponents();
    void viewTasks();
    void modifyTasksFile();
    void readTasksFile();

private slots:
    void createNewTask();
    void deleteTask(int taskId);
    void editTask(int taskId);

    signals:
    void deleteTaskSignal(int id);
    void editTaskSignal(int id);

};


#endif //TODOLIST_MYDAY_H
