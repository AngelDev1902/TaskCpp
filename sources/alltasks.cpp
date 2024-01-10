#include "../headers/alltasks.h"

AllTask::AllTask(QWidget *parent, QString userName) :
        QWidget(parent),
        userName(userName){

    QDateTime currentDateTime = QDateTime::currentDateTime(); // Obtener la fecha y hora actuales
    QDate currentDate = currentDateTime.date(); // Obtener la fecha actual
    dateString = currentDate.toString("dd MMMM yyyy"); // extraer con cierto formato la fecha actual
    timeString = currentDateTime.toString("hh:mm"); // extraer con cierto formato la hora actual

    layout = new QGridLayout(this); // Crear el layout de la ventana

    file = new QFile("../assets/" + userName + ".txt"); // inicializamos la variable file con el archivo de tareas del usuario
    datesList = new QList<QString>();

    tasksList = new QList<QPointer<Task>>();

    initComponents();
    readTasksFile();
}

void AllTask::initComponents() {
    titleLabel = new QLabel("¡Estas son todas tus tareas!");
    titleLabel->setStyleSheet("color: #ffffff; font-size: 30px; font-weight: bold;");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setFixedHeight(50);

    // Frame para las tareas
    tasksFrame = new QFrame();

    // Layout para el frame de las tareas
    QVBoxLayout *tasksLayout = new QVBoxLayout(tasksFrame);
    tasksLayout->setAlignment(Qt::AlignTop);
    tasksLayout->setMargin(50);

    // Boton para agregar una nueva tarea
    QPushButton *addTask = new QPushButton("Agregar Tarea");
    addTask->setStyleSheet("background-color: #ffffff; color: #000000; font-size: 20px; font-weight: bold;");

    // Conectamos el boton con la funcion para crear una nueva tarea
    QObject::connect(addTask, &QPushButton::clicked, this, &AllTask::createNewTask);

    // Agregamos los componentes al layout
    layout->addWidget(titleLabel, 0, 0, 1, 1);
    layout->addWidget(tasksFrame, 1, 0, 1, 1);
    layout->addWidget(addTask, 2, 0, 1, 1);
}

// Metodo que lee el archivo de tareas para guardar cada tarea en la lista de tareas
void AllTask::readTasksFile() {
    tasksList->clear(); // Limpiamos la lista de tareas

    // Abrimos el archivo de tareas
    if (file->open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(file); // Creamos un stream para leer el archivo

        // Mientras no lleguemos al final del archivo, leemos linea por linea
        while (!stream.atEnd()) {
            QString line = stream.readLine(); // Leemos la linea
            QStringList data = line.split(",");  // Separamos los datos en individuales cada vez que encuentre una coma

            // Si la linea contiene 5 datos, entonces creamos una nueva tarea
            if (data.size() == 5) {
                int id = data[0].toInt(); // Convertimos el id a entero
                QString title = data[1]; // Obtenemos el titulo
                QString description = data[2]; // Obtenemos la descripcion
                QString date = data[3]; // Obtenemos la fecha
                QString time = data[4]; // Obtenemos la hora

                // Creamos una nueva tarea
                QPointer<Task> task = new Task(nullptr, id, title, description, date, time);

                // Agrandamos la tarea leida a la lista de tareas
                tasksList->append(task);
            }
        }
        file->close(); // Cerramos el archivo
    }

    viewTasks();
}

// Metodo que muestra las tareas de la lista de tareas en el frame de tareas
void AllTask::viewTasks() {
    // Obtenemos todas las fechas de las tareas
    getDates();

    // Eliminar todas las tareas existentes del layout
    QLayoutItem *child;
    while ((child = tasksFrame->layout()->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    // Recorremos la lista de fechas para mostrar las tareas dependiendo de la fecha
    for (const auto &date: *datesList) {
        if (date != "") {
            QLabel *dateLabel = new QLabel(date);
            dateLabel->setStyleSheet("color: #ffffff; font-size: 20px; font-weight: bold;");
            dateLabel->setAlignment(Qt::AlignCenter);
            dateLabel->setFixedHeight(50);

            tasksFrame->layout()->addWidget(dateLabel);

            // Recorremos la lista de tareas para mostrar las tareas que coincidan con la fecha actual
            for (const auto &task: *tasksList) {
                if (task && task->getDate() == date) {
                    // Creamos una copia de la tarea para poder editarla o eliminarla
                    QPointer<Task> taskCopy = new Task(nullptr, task->getId(), task->getTitle(), task->getDescription(), task->getDate(), task->getTime());

                    // Conectamos las señales de la tarea copia con las señales de la tarea original
                    QObject::connect(taskCopy.data(), &Task::emitDeleteId, this, &AllTask::deleteTask);
                    QObject::connect(taskCopy.data(), &Task::emitEditId, this, &AllTask::editTask);

                    // Agregamos la tarea al layout
                    tasksFrame->layout()->addWidget(taskCopy.data());
                }
            }
        }
    }
}

// Metodo que obtiene todas las fechas de las tareas
void AllTask::getDates() {
    datesList->clear(); // Limpiamos la lista de fechas

    // Recorremos la lista de tareas
    for (const auto &task: *tasksList) {
        if (task) {
            // Guardamos la fecha de la tarea que se esta leyendo
            QString date = task->getDate();

            // Si la lista de fechas no contiene la fecha de la tarea, entonces la agregamos
            if (!datesList->contains(date)) {
                datesList->append(date);
            }
        }
    }

    // Ordenamos la lista de fechas de forma ascendente
    std::sort(datesList->begin(), datesList->end(), [](const QString &a, const QString &b) {
        // Lambda function que compara dos fechas representadas como QStrings
        QDate dateA = QDate::fromString(a, "dd MMMM yyyy");
        QDate dateB = QDate::fromString(b, "dd MMMM yyyy");
        // Se convierten las cadenas de texto en objetos QDate utilizando el formato especificado

        return dateA < dateB;
        // La lambda function devuelve true si la fecha de 'a' es menor que la fecha de 'b'
        // Esto indica que 'a' debe ir antes que 'b' en la lista ordenada
    });
}

// Metodo que crea una ventana para crear una nueva tarea
void AllTask::createNewTask(){
    int id = getLastId(); // Obtenemos el ultimo id de las tareas

    // Creamos una ventana de la clase NewTask para crear una nueva tarea
    NewTask *newTask = new NewTask();
    newTask->setFixedSize(400, 400);
    newTask->setModal(true);

    newTask->show();

    // Conectamos la señal de la ventana con la funcion para crear una nueva tarea
    QObject::connect(newTask, &NewTask::taskCreated, [=](QString title, QString description, QDate date, QTime time) {
        // Creamos una nueva tarea
        QPointer<Task> task = new Task(nullptr, id + 1, title, description, date.toString("dd MMMM yyyy"), time.toString("hh:mm"));

        // Agregamos la tarea a la lista de tareas
        tasksList->append(task);

        // Modificamos el archivo de tareas
        modifyTasksFile();
    });
}

// Metodo que elimina una tarea de la lista de tareas
void AllTask::deleteTask(int taskId) {
    // Recorremos la lista de tareas
    for (const auto &task : *tasksList) {
        // Si la tarea existe y el id de la tarea es igual al id de la tarea que se quiere eliminar, entonces eliminamos la tarea
        if (task && task->getId() == taskId) {
            tasksList->removeOne(task);

            // Modificamos el archivo de tareas
            modifyTasksFile();
            break;
        }
    }

}


// Metodo que crea una ventana para editar una tarea
void AllTask::editTask(int taskId) {
    // Recorremos la lista de tareas
    for (const auto &task : *tasksList) {
        // Si la tarea existe y el id de la tarea es igual al id de la tarea que se quiere editar, entonces creamos una ventana para editar la tarea
        if (task && task->getId() == taskId) {
            // Obtenemos los datos de la tarea y los guardamos en variables
            QString title = task->getTitle();
            QString description = task->getDescription();
            QString date = task->getDate();
            QString time = task->getTime();

            // Creamos una ventana de la clase NewTask para editar la tarea con los datos obtenidos
            NewTask *newTask = new NewTask(nullptr, title, description, QDate::fromString(date, "dd MMMM yyyy"), QTime::fromString(time, "hh:mm"));
            newTask->setFixedSize(400, 400);
            newTask->setModal(true);

            newTask->show();

            // Conectamos la señal de la ventana con la funcion para editar la tarea
            QObject::connect(newTask, &NewTask::taskCreated, [=](QString newTitle, QString newDescription, QDate newDate, QTime newTime) {
                // metodo del objeto task que actualiza los datos de la tarea
                task->updateDates(newTitle, newDescription, newDate.toString("dd MMMM yyyy") , newTime.toString("hh:mm"));

                // Modificamos el archivo de tareas
                modifyTasksFile();
            });
            break;
        }
    }
}


// Metodo que modifica el archivo de tareas con los datos de la lista de tareas
void AllTask::modifyTasksFile() {
    // Abrimos el archivo de tareas en modo escritura
    if (file->open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(file);

        // Recorremos la lista de tareas para escribir los datos de cada tarea en el archivo
        for (const auto &task : *tasksList) {
            if (task) {
                stream << task->getId() << "," << task->getTitle() << "," << task->getDescription() << "," << task->getDate() << "," << task->getTime() << "\n";
            }
        }

        file->close(); // Cerramos el archivo
    }

    // Mostramos las tareas en el frame de tareas
    viewTasks();
}

// Metodo que obtiene el ultimo id de las tareas
int AllTask::getLastId() {
    int lastId = 0;

    // Recorremos la lista de tareas para obtener el valor id del ultimo elemento
    for (const auto &task : *tasksList) {
        if (task && task->getId() > lastId) {
            lastId = task->getId();
        }
    }

    return lastId;
}

// Liberamos la memoria de los componentes
AllTask::~AllTask() {
    delete layout;
    delete titleLabel;
    delete tasksFrame;
    delete tasksList;
    delete datesList;
    delete file;
}
