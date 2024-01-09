#ifndef TODOLIST_TASK_H
#define TODOLIST_TASK_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QDate>
#include <QCheckBox>


class Task : public QFrame{
Q_OBJECT

private:
    QGridLayout *layout;
    int id;
    QString title;
    QString description;
    QString date;
    QString time;

    QPushButton *editTaskButton;
    QPushButton *deleteTaskButton;
public:
    explicit Task(QFrame *parent = nullptr, int = 0, QString title = "title", QString description = "Description", QString date = "Date", QString time = "Time");
    ~Task() override;

    void initComponents();
    void updateDates(QString title, QString description, QString date, QString time);

    inline int getId() const { return id; }
    inline QString getTitle() const { return title; }
    inline QString getDescription() const { return description; }
    inline QString getDate() const { return date; }
    inline QString getTime() const { return time; }

private slots:
    void deleteTask();
    void editTask();

signals:
    void deleteTaskSignal(int id);
    void editTaskSignal(int id);
};


#endif //TODOLIST_TASK_H
