#include "../headers/newtask.h"

NewTask::NewTask(QWidget *parent) :
        QDialog(parent){

    setWindowTitle("Crear Nueva Tarea");

    // Inicializar los widgets
    titleLineEdit = new QLineEdit(this);
    descriptionTextEdit = new QTextEdit(this);
    dateEdit = new QDateEdit(QDate::currentDate(), this);
    dateTimeEdit = new QTimeEdit(QDateTime::currentDateTime().time(), this);
    acceptButton = new QPushButton("Aceptar", this);

    // Conectar la señal de click del botón con el slot onAcceptButtonClicked
    connect(acceptButton, SIGNAL(clicked(bool)), this, SLOT(onAcceptButtonClicked()));

    // Crear el layout y agregar los widgets
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Agregar los widgets al layout
    layout->addWidget(new QLabel("Título:", this));
    layout->addWidget(titleLineEdit);
    layout->addWidget(new QLabel("Descripción:", this));
    layout->addWidget(descriptionTextEdit);
    layout->addWidget(new QLabel("Fecha de vencimiento:", this));
    layout->addWidget(dateEdit);
    layout->addWidget(new QLabel("Hora de vencimiento:", this));
    layout->addWidget(dateTimeEdit);
    layout->addWidget(acceptButton);
}

// Misma implementación que el constructor anterior, pero con los campos ya llenos
NewTask::NewTask(QWidget *parent, QString title, QString description, QDate date, QTime time) :
        QDialog(parent){

    setWindowTitle("Editar Tarea");

    titleLineEdit = new QLineEdit(title, this);
    descriptionTextEdit = new QTextEdit(description, this);
    dateEdit = new QDateEdit(date, this);
    dateTimeEdit = new QTimeEdit(time, this);
    acceptButton = new QPushButton("Aceptar", this);

    connect(acceptButton, &QPushButton::clicked, this, &NewTask::onAcceptButtonClicked);

    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addWidget(new QLabel("Título:", this));
    layout->addWidget(titleLineEdit);
    layout->addWidget(new QLabel("Descripción:", this));
    layout->addWidget(descriptionTextEdit);
    layout->addWidget(new QLabel("Fecha de vencimiento:", this));
    layout->addWidget(dateEdit);
    layout->addWidget(new QLabel("Hora de vencimiento:", this));
    layout->addWidget(dateTimeEdit);
    layout->addWidget(acceptButton);
}


void NewTask::onAcceptButtonClicked() {
    // Emitir la señal con los datos de la nueva tarea
    emit taskCreated(titleLineEdit->text(), descriptionTextEdit->toPlainText(), dateEdit->date(), dateTimeEdit->time());

    // Cerrar el diálogo
    accept();
}

NewTask::~NewTask() {
    delete titleLineEdit;
    delete descriptionTextEdit;
    delete dateEdit;
    delete dateTimeEdit;
    delete acceptButton;
}
