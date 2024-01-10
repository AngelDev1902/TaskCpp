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
    QGridLayout *layout; // Layout de la tarea
    int id; // Identificador de la tarea
    QString title; // Título de la tarea
    QString description; // Descripción de la tarea
    QString date; // Fecha de la tarea
    QString time; // Hora de la tarea

    QPushButton *editTaskButton; // Botón para editar la tarea
    QPushButton *deleteTaskButton; // Botón para eliminar la tarea
public:
    // Constructor de la clase que recibe el padre, el id, el título, la descripción, la fecha y la hora
    explicit Task(QFrame *parent = nullptr, int = 0, QString title = "title", QString description = "Description", QString date = "Date", QString time = "Time");
    ~Task() override;

    void initComponents();

    // Método para actualizar los datos de la tarea
    void updateDates(QString title, QString description, QString date, QString time);

    // Getters
    inline int getId() const { return id; }
    inline QString getTitle() const { return title; }
    inline QString getDescription() const { return description; }
    inline QString getDate() const { return date; }
    inline QString getTime() const { return time; }

signals:
    void emitDeleteId(int id);
    void emitEditId(int id);
};


#endif //TODOLIST_TASK_H
