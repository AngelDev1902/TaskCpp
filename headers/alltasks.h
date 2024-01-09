#ifndef TODOLIST_ALLTASKS_H
#define TODOLIST_ALLTASKS_H

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


class AllTask : public QWidget {
Q_OBJECT

protected:
    QGridLayout *layout;
    QString dateString;
    QString timeString;
    QFrame *tasksFrame;
    QList<QPointer<Task>> *tasksList;
    QList<QString> *datesList;
    QLabel *titleLabel;

    QFile *file;

    QString userName;

public:
    explicit AllTask(QWidget *parent = nullptr, QString userName = "User");
    ~AllTask() override;

    void initComponents();
    virtual void viewTasks();
    void modifyTasksFile();
    void readTasksFile();
    void getDates();
    int getLastId();

public slots:
    void createNewTask();
    void deleteTask(int taskId);
    void editTask(int taskId);
};


#endif //TODOLIST_ALLTASKS_H
