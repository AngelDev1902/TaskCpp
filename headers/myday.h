#ifndef TODOLIST_MYDAY_H
#define TODOLIST_MYDAY_H

#include "alltasks.h"


// Clase que hereda de AllTask
class MyDay : public AllTask {
public:
    explicit MyDay(QWidget *parent = nullptr, QString userName = "User");
    ~MyDay() override;

    // Método que se encarga de mostrar las tareas del día actual (sobreescribe el método de la clase base)
    void viewTasks() override;
};

#endif //TODOLIST_MYDAY_H
