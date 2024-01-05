#ifndef TODOLIST_ALLTASKS_H
#define TODOLIST_ALLTASKS_H

#include <QWidget>
#include <QLabel>

class AllTask : public QWidget {
Q_OBJECT

private:

public:
    explicit AllTask(QWidget *parent = nullptr);
    ~AllTask() override;

private slots:

};


#endif //TODOLIST_ALLTASKS_H
