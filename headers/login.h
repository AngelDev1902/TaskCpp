#ifndef TODOLIST_LOGIN_H
#define TODOLIST_LOGIN_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

class Login : public QDialog {
Q_OBJECT

private:
    QString username; // Nombre de usuario
    QString password; // Contraseña

    bool checkLogin; // Comprobación de si el login es correcto

    QFile *fileUsers; // Archivo de usuarios

    QLineEdit *userLineEdit; // LineEdit para el usuario
    QLineEdit *passwordLineEdit; // LineEdit para la contraseña
    QPushButton *loginButton; // Botón para iniciar sesión
    QPushButton *registerButton; // Botón para registrarse

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login() override;

    void initComponents(); // Inicialización de los componentes de la ventana
    bool checkUserExists(); // Comprobación de si el usuario existe
    void registerUser(); // Registro de un nuevo usuario
    void createFileUser(); // Creación del archivo de usuarios

private slots:
    void onLoginButtonClicked(); // Slot para el botón de iniciar sesión
    void onRegisterButtonClicked(); // Slot para el botón de registrarse

signals:
    void loginSignal(QString username); // Señal que envia el nombre de usuario
};


#endif //TODOLIST_LOGIN_H
