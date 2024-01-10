#include "../headers/Window.h"

Window::Window(QWidget *parent, QString userName) :
        QMainWindow(parent),
        userName(userName) {
    setWindowTitle("TodoList App");
    setWindowState(Qt::WindowMaximized);
    setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);

    initLayout();
    initComponents();
}

void Window::initLayout() {
    // Panel de acciones
    actions = new QWidget(this);
    actions->setFixedWidth(300);
    actions->setFixedHeight(maximumHeight());
    actions->setStyleSheet("background-color: #101010;");

    // Layout del panel de acciones
    layoutActions = new QVBoxLayout(actions);
    layoutActions->setAlignment(Qt::AlignTop);

    // Panel de contenido
    content = new QWidget(this);
    content->setMinimumWidth(this->width() - actions->width());
    content->setFixedHeight(maximumHeight());
    content->setStyleSheet("background-color: #161616;");

    // QStackedWidget para almacenar los diferentes frames en el panel de contenido
    stackedWidget = new QStackedWidget(content);

    // Paneles que iran en el stackedWidget

    // Se crea el panel de MyDay
    home = new MyDay(content, userName);
    home->setMinimumSize(content->width(), content->height());

    // Se crea el panel de AllTask
    task = new AllTask(content, userName);
    task->setMinimumSize(content->width(), content->height());

    // Se crea el panel de CalendarPanel
    calendar = new CalendarPanel(content, task);
    calendar->setMinimumSize(content->width(), content->height());

    // Agrega el widget de MyDay al stackedWidget primero
    stackedWidget->addWidget(home);
    // Luego agrega el widget de AllTask
    stackedWidget->addWidget(task);
    // Luego agrega el widget de CalendarPanel
    stackedWidget->addWidget(calendar);

    // Agregar el stackedWidget al layout del contenido
    QVBoxLayout *contentLayout = new QVBoxLayout(content);
    contentLayout->addWidget(stackedWidget);

    // Splitter para dividir la ventana en dos paneles
    splitter = new QSplitter(Qt::Horizontal, this);
    splitter->addWidget(actions);
    splitter->addWidget(content);

    // Asignar el splitter como widget central de la ventana
    setCentralWidget(splitter);
}

void Window::initComponents() {
    int anchoBotones{actions->width() - 20};
    int altoBotones{80};

    QLabel *user = new QLabel("Bienvenido" + userName);
    user->setAlignment(Qt::AlignCenter);
    user->setStyleSheet("color: white; font-size: 25px; font-weight: bold;");
    user->setMinimumSize(anchoBotones, altoBotones);
    user->setMaximumSize(anchoBotones, altoBotones);

    // Boton para ir al panel de MyDay
    homeButton = new QPushButton("Mi Dia");
    homeButton->setMinimumSize(anchoBotones, altoBotones);
    homeButton->setMaximumSize(anchoBotones, altoBotones);

    // Boton para ir al panel de AllTask
    taskButton = new QPushButton("Tareas");
    taskButton->setMinimumSize(anchoBotones, altoBotones);
    taskButton->setMaximumSize(anchoBotones, altoBotones);

    // Boton para ir al panel de CalendarPanel
    calendarButton = new QPushButton("Calendario");
    calendarButton->setMinimumSize(anchoBotones, altoBotones);
    calendarButton->setMaximumSize(anchoBotones, altoBotones);

    // Inserción de los componentes
    layoutActions->addWidget(user);
    layoutActions->addWidget(homeButton);
    layoutActions->addWidget(taskButton);
    layoutActions->addWidget(calendarButton);

    // Asignar acciones a los botones
    QObject::connect(homeButton, &QPushButton::clicked, this, [&]() {
        // Cambiar al widget MyDay en el stackedWidget
        stackedWidget->setCurrentIndex(0);
    });

    QObject::connect(taskButton, &QPushButton::clicked, this, [&]() {
        // Cambiar al widget AllTask en el stackedWidget
        stackedWidget->setCurrentIndex(1);
    });

    QObject::connect(calendarButton, &QPushButton::clicked, this, [&]() {
        // Cambiar al widget CalendarPanel en el stackedWidget
        stackedWidget->setCurrentIndex(2);
    });
}

Window::~Window() {
    // Liberar la memoria de los componentes
    delete actions;
    delete content;
    delete layoutActions;
    delete taskButton;
    delete homeButton;
}
