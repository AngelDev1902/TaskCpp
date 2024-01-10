#include "../headers/login.h"

Login::Login(QWidget *parent) :
        QDialog(parent){
    setWindowTitle("Login de usuario");
    setFixedSize(300, 300);

    fileUsers = new QFile("../assets/users.txt");
    checkLogin = false;

    initComponents();
}

// Inicialización de los componentes de la ventana y aplicar estilos
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

    // conectar el evento click del boton iniciar sesion con el slot onLoginButtonClicked
    connect(loginButton, &QPushButton::clicked, this, &Login::onLoginButtonClicked);

    // conectar el evento click del boton registrarse con el slot onRegisterButtonClicked
    connect(registerButton, &QPushButton::clicked, this, &Login::onRegisterButtonClicked);
}


// Slot para el botón de iniciar sesión
void Login::onLoginButtonClicked() {
    username = userLineEdit->text(); // Obtener el texto del LineEdit de usuario
    password = passwordLineEdit->text(); // Obtener el texto del LineEdit de contraseña

    // Comprobar que el usuario y la contraseña no estén vacios
    if (username == "" || password == "") {
        QMessageBox::warning(this, "Error", "El usuario y la contraseña no pueden estar vacios");
        return;
    }else{
        // Abrir el archivo de usuarios en modo lectura
        if (fileUsers->open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(fileUsers);
            // Leer el archivo de usuarios linea a linea
            while (!in.atEnd()) {
                QString line = in.readLine();
                QStringList fields = line.split(",");

                // Comprobar que el usuario y la contraseña coincidan con los del archivo
                if (fields[0] == username && fields[1] == password) {
                    // Si coinciden marcamos el login como correcto y salimos del bucle
                    checkLogin = true;
                    break;
                }
            }
            fileUsers->close(); // Cerrar el archivo de usuarios
        }
    }

    // Si el login es correcto, emitimos la señal de login y cerramos la ventana
    if (checkLogin){
        emit loginSignal(username);
        close();
    }else{
        // Si el login no es correcto, mostramos un mensaje de error
        QMessageBox::warning(this, "Error", "Usuario o contraseña incorrectos");
    }
}

// Slot para el botón de registrarse
void Login::onRegisterButtonClicked() {
    username = userLineEdit->text(); // Obtener el texto del LineEdit de usuario
    password = passwordLineEdit->text(); // Obtener el texto del LineEdit de contraseña

    // Comprobar que el usuario y la contraseña no estén vacios
    if (username == "" || password == "") {
        QMessageBox::warning(this, "Error", "El usuario y la contraseña no pueden estar vacios");
        return;
    }else{
        // Comprobar que el usuario no exista
        if (checkUserExists()) {
            QMessageBox::warning(this, "Error", "El usuario ya existe");
        } else {
            registerUser();
        }
    }
}

// Comprobación de si el usuario existe
bool Login::checkUserExists() {
    // Abrir el archivo de usuarios en modo lectura
    if (fileUsers->open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(fileUsers);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(",");

            // Comprobar que el usuario y la contraseña coincidan con los del archivo
            if (fields[0] == username && fields[1] == password) {
                fileUsers->close();
                return true; // Si coinciden devolvemos true
            }
        }
        fileUsers->close(); // Cerrar el archivo de usuarios
    }
    return false; // Si no coinciden devolvemos false
}

// Registro de un nuevo usuario
void Login::registerUser() {
    // Abrir el archivo de usuarios en modo escritura
    if (fileUsers->open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(fileUsers);
        // Escribir el usuario y la contraseña en el archivo de usuarios
        out << username << "," << password << "\n";
        fileUsers->close(); // Cerrar el archivo de usuarios
        // Mostrar un mensaje de que el usuario se ha registrado correctamente
        QMessageBox::information(this, "Registro", "Usuario registrado correctamente");

        checkLogin = true; // Marcar el login como correcto
    }else{
        QMessageBox::warning(this, "Error", "No se pudo abrir el archivo de usuarios");
    }

    // Si el login es correcto, emitimos la señal de login y cerramos la ventana
    if (checkLogin){
        createFileUser(); // Crear el archivo de usuario
        emit loginSignal(username);
        close();
    }
}

// Creación del archivo de usuarios
void Login::createFileUser() {
    // Creamos el titulo del archivo basado en el nombre de usuario
    QString path = "../assets/" + username + ".txt";
    // Creamos el archivo de usuario
    QFile *file = new QFile(path);

    // Abrimos el archivo de usuario en modo escritura y verificamos que se ha creado correctamente
    if (!file->open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "No se pudo crear el archivo de usuario: " + file->errorString());
        delete file;  // Liberar la memoria si la apertura falla
        return;
    }

    file->close(); // Cerrar el archivo de usuario
    delete file;  // Liberar la memoria después de cerrar el archivo
}


Login::~Login() {
    delete fileUsers;
    delete userLineEdit;
    delete passwordLineEdit;
    delete loginButton;
    delete registerButton;
}
