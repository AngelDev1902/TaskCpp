#include "../headers/login.h"

Login::Login(QWidget *parent) :
        QDialog(parent){
    setWindowTitle("Login de usuario");
    setFixedSize(300, 300);

    fileUsers = new QFile("../assets/users.txt");
    checkLogin = false;

    initComponents();
}

void Login::initComponents() {
    QGridLayout *layout = new QGridLayout(this);

    QLabel *label = new QLabel("Login de usuario", this);
    label->setFixedSize(width(), 50);
    label->setAlignment(Qt::AlignCenter);

    QLabel *userLabel = new QLabel("Usuario:", this);
    userLabel->setAlignment(Qt::AlignCenter);

    QLabel *passwordLabel = new QLabel("Contraseña:", this);
    passwordLabel->setAlignment(Qt::AlignCenter);

    userLineEdit = new QLineEdit(this);
    passwordLineEdit = new QLineEdit(this);
    passwordLineEdit->setEchoMode(QLineEdit::Password);

    loginButton = new QPushButton("Iniciar sesión", this);
    loginButton->setFixedSize(width() - 20, 50);

    registerButton = new QPushButton("Registrarse", this);
    registerButton->setFixedSize(width() - 20, 50);

    layout->addWidget(label, 0, 0, 1, 2);
    layout->addWidget(userLabel, 1, 0);
    layout->addWidget(userLineEdit, 1, 1);
    layout->addWidget(passwordLabel, 2, 0);
    layout->addWidget(passwordLineEdit, 2, 1);
    layout->addWidget(loginButton, 3, 0, 1, 2);
    layout->addWidget(registerButton, 4, 0, 1, 2);

    connect(loginButton, &QPushButton::clicked, this, &Login::onLoginButtonClicked);
    connect(registerButton, &QPushButton::clicked, this, &Login::onRegisterButtonClicked);
}

void Login::onLoginButtonClicked() {
    username = userLineEdit->text();
    password = passwordLineEdit->text();

    if (username == "" || password == "") {
        QMessageBox::warning(this, "Error", "El usuario y la contraseña no pueden estar vacios");
        return;
    }else{
        if (fileUsers->open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(fileUsers);
            while (!in.atEnd()) {
                QString line = in.readLine();
                QStringList fields = line.split(",");
                if (fields[0] == username && fields[1] == password) {
                    checkLogin = true;
                    break;
                }
            }
            fileUsers->close();
        }
    }

    if (checkLogin){
        emit loginSignal(username);
        close();
    }else{
        QMessageBox::warning(this, "Error", "Usuario o contraseña incorrectos");
    }
}

void Login::onRegisterButtonClicked() {
    username = userLineEdit->text();
    password = passwordLineEdit->text();

    if (username == "" || password == "") {
        QMessageBox::warning(this, "Error", "El usuario y la contraseña no pueden estar vacios");
        return;
    }else{
        if (checkUserExists()) {
            QMessageBox::warning(this, "Error", "El usuario ya existe");
        } else {
            registerUser();
        }
    }
}

bool Login::checkUserExists() {
    if (fileUsers->open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(fileUsers);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(",");
            if (fields[0] == username && fields[1] == password) {
                fileUsers->close();
                return true;
            }
        }
        fileUsers->close();
    }
    return false;
}

void Login::registerUser() {
    if (fileUsers->open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(fileUsers);
        out << username << "," << password << "\n";
        fileUsers->close();
        QMessageBox::information(this, "Registro", "Usuario registrado correctamente");

        checkLogin = true;
    }else{
        QMessageBox::warning(this, "Error", "No se pudo abrir el archivo de usuarios");
    }

    if (checkLogin){
        createFileUser();
        emit loginSignal(username);
        close();
    }
}

void Login::createFileUser() {
    QString path = "../assets/" + username + ".txt";
    QFile *file = new QFile(path);

    if (!file->open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "No se pudo crear el archivo de usuario: " + file->errorString());
        delete file;  // Liberar la memoria si la apertura falla
        return;
    }

    file->close();
    delete file;  // Liberar la memoria después de cerrar el archivo
}


Login::~Login() {}
