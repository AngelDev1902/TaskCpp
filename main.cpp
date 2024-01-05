#include <QApplication>
#include "Window.h"
#include <QDialog>
#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QDialog *login = new QDialog();
    QObject::connect(login, &QDialog::rejected, login, [&](){
        app.quit();
    });

    QGridLayout *layout = new QGridLayout(login);

    login->setWindowTitle("Login");
    login->setMinimumSize(300, 200);

    QLineEdit *user = new QLineEdit(login);
    user->setPlaceholderText("Usuario");

    QPushButton *accept = new QPushButton("Aceptar", login);

    layout->addWidget(new QLabel("Ingresa tu nombre:", login));
    layout->addWidget(user);
    layout->addWidget(accept);

    QObject::connect(accept, &QPushButton::clicked, login, [=](){
        login->close();
    });

    login->exec();

    if (user->text().isEmpty()) {
        return 0;
    }else{
        Window *window = new Window(nullptr, user->text());
        window->show();
    }

    // Ejecutamos la aplicación
    return app.exec();
}