#include "../headers/calendarPanel.h"

CalendarPanel::CalendarPanel(QWidget *parent, AllTask *allTask) :
        QWidget(parent),
        allTask(allTask) {

    layout = new QGridLayout(this);

    initComponents();
    updateCalendar();
}

void CalendarPanel::initComponents() {
    // Lista con los nombres de los días de la semana
    QStringList dayNames = {"Dom", "Lun", "Mar", "Mié", "Jue", "Vie", "Sáb"};

    // Crear etiquetas para los nombres de los días de la semana
    for (int i = 0; i < 7; ++i) {
        QLabel *dayLabel = new QLabel(dayNames.at(i));
        dayLabel->setAlignment(Qt::AlignCenter);
        dayLabel->setFixedSize(100, 50);
        layout->addWidget(dayLabel, 0, i);
    }

    // Crear botones para los días del mes
    for (int i = 1; i <= 31; ++i) {
        QPushButton *dayButton = new QPushButton(QString::number(i));
        dayButton->setFixedSize(100, 100);
        dayButtons.append(dayButton);
        layout->addWidget(dayButton, (i - 1) / 7 + 1, (i - 1) % 7);

        // Conectar la señal del botón a la ranura correspondiente
        connect(dayButton, &QPushButton::clicked, this, &CalendarPanel::onDayButtonClicked);
    }
}

// Actualizar los botones del calendario
void CalendarPanel::updateCalendar() {
    // Obtener las fechas de las tareas
    QList<QString> datesList;

    // Recorrer la lista de tareas
    for (const auto &task : *allTask->tasksList) {
        if (task) {
            // Obtener la fecha de la tarea
            QString date = task->getDate();
            // Si la fecha no está en la lista, añadirla
            if (!datesList.contains(date)) {
                datesList.append(date);
            }
        }
    }

    // Obtener el primer día del mes actual
    QDate currentDate = QDate::currentDate();
    // Establecer el día en 1
    currentDate.setDate(currentDate.year(), currentDate.month(), 1);

    // Calcular el índice de inicio del primer día en la matriz de botones
    int startIndex = currentDate.dayOfWeek() - 1;

    // Obtener el último día del mes actual
    int lastDay = currentDate.daysInMonth();

    // Actualizar los botones del calendario
    for (int i = 0; i < 31; ++i) {
        QPushButton *dayButton = dayButtons.at(i);

        // Si el índice del botón está en el rango del mes actual
        if (i >= startIndex && i < startIndex + lastDay) {
            // Obtener el día del mes
            int day = i - startIndex + 1;

            // Establecer el texto del botón
            dayButton->setText(QString::number(day));

            // Asignar el texto de la fecha como una propiedad del botón
            QString dateString = currentDate.toString("dd MMMM yyyy");

            // Establecer el estilo del botón si la fecha está en la lista
            if (datesList.contains(dateString)) {
                dayButton->setStyleSheet("background-color: #05A7D6; color: #ffffff;");
            } else {
                dayButton->setStyleSheet("");  // Restablecer el estilo predeterminado
            }
            currentDate = currentDate.addDays(1);
        } else {
            dayButton->setText("");
            dayButton->setStyleSheet("");  // Restablecer el estilo predeterminado
        }
    }
}

void CalendarPanel::onDayButtonClicked() {
    // Obtener el botón que emitió la señal
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    if (clickedButton) {
        // Obtener el día del botón
        int day = clickedButton->text().toInt();
        QDate currentDate = QDate::currentDate();
        currentDate.setDate(currentDate.year(), currentDate.month(), day);
        QString dateString = currentDate.toString("dd MMMM yyyy");

        // Filtrar las tareas para obtener solo las del día seleccionado
        QList<Task*> tasksForDay;
        for (const auto &task : *allTask->tasksList) {
            // Si la tarea no es nula y la fecha coincide, añadirla a la lista
            if (task && task->getDate() == dateString) {
                tasksForDay.append(task);
            }
        }

        // Crear un QDialog para mostrar la información de las tareas
        QDialog *taskDialog = new QDialog(this);
        taskDialog->setWindowTitle("Tareas para el día " + dateString);

        // Crear una lista para mostrar las tareas
        QListWidget *taskListWidget = new QListWidget(taskDialog);
        for (const auto &task : tasksForDay) {
            QListWidgetItem *item = new QListWidgetItem(task->getTitle() + " - " + task->getTime());
            taskListWidget->addItem(item);
        }

        // Establecer el diseño del QDialog
        QVBoxLayout *dialogLayout = new QVBoxLayout(taskDialog);
        dialogLayout->addWidget(taskListWidget);

        // Mostrar el QDialog
        taskDialog->exec();
    }
}


CalendarPanel::~CalendarPanel() {
    delete layout;
    for (auto &dayButton : dayButtons) {
        delete dayButton;
    }
}
