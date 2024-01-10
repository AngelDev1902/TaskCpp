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
    QGridLayout *layout; // Layout de la ventana
    QString dateString; // Fecha actual
    QString timeString; // Hora actual
    QFrame *tasksFrame; // Frame para las tareas
    QList<QString> *datesList; // Lista de fechas
    QLabel *titleLabel; // Label para el titulo

    QFile *file; // Archivo de tareas

    QString userName; // Nombre del usuario

public:
    QList<QPointer<Task>> *tasksList; // Lista de tareas

    explicit AllTask(QWidget *parent = nullptr, QString userName = "User");
    ~AllTask() override;

    void initComponents();
    virtual void viewTasks(); // Mostrar las tareas
    void modifyTasksFile(); // Modificar el archivo de tareas
    void readTasksFile(); // Leer el archivo de tareas
    void getDates(); // Obtener las fechas de las tareas
    int getLastId(); // Obtener el ultimo id de las tareas

public slots:
    void createNewTask(); // Crear una nueva tarea
    void deleteTask(int taskId); // Eliminar una tarea
    void editTask(int taskId); // Editar una tarea
};


#endif //TODOLIST_ALLTASKS_H
