#include "../headers/calendarPanel.h"

CalendarPanel::CalendarPanel(QWidget *parent, AllTask *allTask) :
        QWidget(parent),
        allTask(allTask) {

    layout = new QGridLayout(this);

    initComponents();
    updateCalendar();
}

void CalendarPanel::initComponents() {
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

void CalendarPanel::updateCalendar() {
    // Obtener las fechas de las tareas
    QList<QString> datesList;
    for (const auto &task : *allTask->tasksList) {
        if (task) {
            QString date = task->getDate();
            if (!datesList.contains(date)) {
                datesList.append(date);
            }
        }
    }

    // Obtener el primer día del mes actual
    QDate currentDate = QDate::currentDate();
    currentDate.setDate(currentDate.year(), currentDate.month(), 1);

    // Calcular el índice de inicio del primer día en la matriz
    int startIndex = currentDate.dayOfWeek() - 1;

    // Obtener el último día del mes actual
    int lastDay = currentDate.daysInMonth();

    // Actualizar los botones del calendario
    for (int i = 0; i < 31; ++i) {
        QPushButton *dayButton = dayButtons.at(i);
        if (i >= startIndex && i < startIndex + lastDay) {
            int day = i - startIndex + 1;
            dayButton->setText(QString::number(day));
            QString dateString = currentDate.toString("dd MMMM yyyy");
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
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    if (clickedButton) {
        int day = clickedButton->text().toInt();
        QDate currentDate = QDate::currentDate();
        currentDate.setDate(currentDate.year(), currentDate.month(), day);
        QString dateString = currentDate.toString("dd MMMM yyyy");
        qDebug() << "Clicked on day:" << day << "Date:" << dateString;
        // Puedes realizar acciones adicionales al hacer clic en un día
    }
}

CalendarPanel::~CalendarPanel() {
}
