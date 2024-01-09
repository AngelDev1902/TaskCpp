#ifndef TODOLIST_WINDOW_H
#define TODOLIST_WINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <QStackedWidget>

#include "myday.h"
#include "alltasks.h"

class Window : public QMainWindow {
Q_OBJECT

private:
    // Nombre del usuario
    QString userName;

    // Secciones de la ventana
    QWidget *actions;
    QWidget *content;

    // Layouts de los paneles
    QSplitter *splitter;
    QVBoxLayout *layoutActions;
    QStackedWidget *stackedWidget;

    // botones
    QPushButton *taskButton;
    QPushButton *homeButton;

    // Paneles que iran en la seccion content
    MyDay *home;
    AllTask *task;
public:
    explicit Window(QWidget *parent = nullptr, QString userName = "User");
    ~Window() override;

    void initLayout(); // Crear los layouts de la ventana
    void initComponents(); // Crear los componentes y dar estilos
};


#endif //TODOLIST_WINDOW_H
