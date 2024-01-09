#ifndef TODOLIST_CALENDARPANEL_H
#define TODOLIST_CALENDARPANEL_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QDate>
#include <QVector>

#include "alltasks.h"

class CalendarPanel : public QWidget {
Q_OBJECT

private:
    QGridLayout *layout;
    AllTask *allTask;

    QVector<QPushButton *> dayButtons;

public:
    explicit CalendarPanel(QWidget *parent = nullptr, AllTask *allTask = nullptr);
    ~CalendarPanel() override;

    void initComponents();
    void updateCalendar();

private slots:
    void onDayButtonClicked();
};

#endif //TODOLIST_CALENDARPANEL_H
