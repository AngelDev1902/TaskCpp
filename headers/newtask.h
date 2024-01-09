#ifndef TODOLIST_NEWTASK_H
#define TODOLIST_NEWTASK_H

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QDateEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>

class NewTask : public QDialog {
Q_OBJECT

private:
    QLineEdit *titleLineEdit;
    QTextEdit *descriptionTextEdit;
    QDateEdit *dateEdit;
    QTimeEdit *dateTimeEdit;
    QPushButton *acceptButton;

public:
    explicit NewTask(QWidget *parent = nullptr);
    NewTask(QWidget *parent, QString title, QString description, QDate date, QTime time);
    ~NewTask() override;

    void disableDateEdit();

private slots:
    void onAcceptButtonClicked();

signals:
    void taskCreated(const QString &title, const QString &description, const QDate &date, const QTime &time);

};


#endif //TODOLIST_NEWTASK_H
