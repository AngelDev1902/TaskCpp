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
    QLineEdit *titleLineEdit; // Campo de texto para el título
    QTextEdit *descriptionTextEdit; // Campo de texto para la descripción
    QDateEdit *dateEdit; // Campo de texto para la fecha
    QTimeEdit *dateTimeEdit; // Campo de texto para la hora
    QPushButton *acceptButton; // Botón para aceptar

public:
    explicit NewTask(QWidget *parent = nullptr); // Constructor por defecto
    NewTask(QWidget *parent, QString title, QString description, QDate date, QTime time); // Constructor sobrecargado
    ~NewTask() override;

private slots:
    // Slot para cuando se presiona el botón de aceptar
    void onAcceptButtonClicked();

signals:
    // Se emite un metodo como señal que envia los datos de la nueva tarea
    void taskCreated(const QString &title, const QString &description, const QDate &date, const QTime &time);

};


#endif //TODOLIST_NEWTASK_H
