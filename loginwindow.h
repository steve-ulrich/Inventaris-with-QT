#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>

class QLineEdit;
class QPushButton;

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);

private:

    QLineEdit *txtUsername;
    QLineEdit *txtPassword;

    QPushButton *btnLogin;

private slots:

    void login();
};

#endif