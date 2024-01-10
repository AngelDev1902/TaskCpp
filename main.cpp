#include <QApplication>

#include "headers/Window.h"
#include "headers/login.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Crear la ventana de login
    Login *login = new Login();
    login->show();

    // Conectamos la señal que emita el login para crear la ventana principal
    QObject::connect(login, &Login::loginSignal, [&](QString username){
        Window *window = new Window(nullptr, username);
        window->show();
    });

    return app.exec();
}