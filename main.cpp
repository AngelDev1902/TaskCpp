#include <QApplication>

#include "headers/Window.h"
#include "headers/login.h"

#include <QDialog>
#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Login *login = new Login();
    login->show();

    QObject::connect(login, &Login::loginSignal, [&](QString username){
        /*Window *window = new Window(nullptr, username);
        window->show();*/

        qDebug() << "Username: " << username << "\n";
    });

    return app.exec();
}