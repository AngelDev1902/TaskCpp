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

    home = new MyDay(content, userName);
    home->setMinimumSize(content->width(), content->height());

    task = new AllTask(content, userName);
    task->setMinimumSize(content->width(), content->height());

    // Agrega el widget de MyDay al stackedWidget primero
    stackedWidget->addWidget(home);
    // Luego agrega el widget de AllTask
    stackedWidget->addWidget(task);

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

    QLabel *user = new QLabel(userName);
    user->setAlignment(Qt::AlignCenter);
    user->setMinimumSize(anchoBotones, altoBotones);
    user->setMaximumSize(anchoBotones, altoBotones);

    homeButton = new QPushButton("Mi Dia");
    homeButton->setMinimumSize(anchoBotones, altoBotones);
    homeButton->setMaximumSize(anchoBotones, altoBotones);

    taskButton = new QPushButton("Tareas");
    taskButton->setMinimumSize(anchoBotones, altoBotones);
    taskButton->setMaximumSize(anchoBotones, altoBotones);

    // Inserción de los componentes
    layoutActions->addWidget(user);
    layoutActions->addWidget(homeButton);
    layoutActions->addWidget(taskButton);

    // Asignar acciones a los botones
    QObject::connect(homeButton, &QPushButton::clicked, this, [&]() {
        // Cambiar al widget MyDay en el stackedWidget
        stackedWidget->setCurrentIndex(0);
    });

    QObject::connect(taskButton, &QPushButton::clicked, this, [&]() {
        // Cambiar al widget AllTask en el stackedWidget
        stackedWidget->setCurrentIndex(1);
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
