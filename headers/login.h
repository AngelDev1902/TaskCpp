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
    QString username;
    QString password;

    bool checkLogin;

    QFile *fileUsers;

    QLineEdit *userLineEdit;
    QLineEdit *passwordLineEdit;
    QPushButton *loginButton;
    QPushButton *registerButton;

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login() override;

    void initComponents();
    bool checkUserExists();
    void registerUser();
    void createFileUser();

private slots:
    void onLoginButtonClicked();
    void onRegisterButtonClicked();

signals:
    void loginSignal(QString username);
};


#endif //TODOLIST_LOGIN_H
