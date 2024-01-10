#ifndef TODOLIST_CALENDARPANEL_H
#define TODOLIST_CALENDARPANEL_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QDate>
#include <QVector>
#include <QList>
#include <QListWidget>

#include "alltasks.h"

class CalendarPanel : public QWidget {
Q_OBJECT

private:
    QGridLayout *layout; // Layout del panel
    AllTask *allTask; // Objeto que contiene todas las tareas

    // Vector de botones para los días del mes
    QVector<QPushButton *> dayButtons;

public:
    explicit CalendarPanel(QWidget *parent = nullptr, AllTask *allTask = nullptr);
    ~CalendarPanel() override;

    void initComponents(); // Inicializar los componentes del panel
    void updateCalendar(); // Actualizar los botones del calendario

private slots:
    // Ranura para el evento de hacer clic en un botón de día
    void onDayButtonClicked();
};

#endif //TODOLIST_CALENDARPANEL_H
