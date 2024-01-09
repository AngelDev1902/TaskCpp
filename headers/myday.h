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

#include "taskday.h"
#include "newtask.h"

class MyDay : public QWidget {
Q_OBJECT

private:
    QGridLayout *layout;
    QString dateString;
    QString timeString;
    QFrame *tasksFrame;
    QList<QPointer<TaskDay>> tasksList;

    QString userName;

public:
    explicit MyDay(QWidget *parent = nullptr, QString userName = "User");
    ~MyDay() override;

    static int numberTask;
    void initComponents();
    void viewTasks();

private slots:
    void createNewTaskButton();
    void createNewTask(const QString &title, const QString &description, const QDate &date, const QTime &time);

    void deleteTaskFromList(int taskId);

    void editTaskFromList(int taskId);

    signals:
    void deleteTaskSignal(int id);
    void editTaskSignal(int id);

};


#endif //TODOLIST_MYDAY_H
