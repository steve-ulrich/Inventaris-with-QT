#include "loginwindow.h"
#include "mainwindow.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

LoginWindow::LoginWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Login STOCKIFY");
    resize(400,300);

    QLabel *title = new QLabel("LOGIN STOCKIFY");
    title->setAlignment(Qt::AlignCenter);

    title->setStyleSheet(
        "font-size:28px;"
        "font-weight:bold;"
        "color:white;"
        );

    txtUsername = new QLineEdit;
    txtUsername->setPlaceholderText("Username");

    txtPassword = new QLineEdit;
    txtPassword->setPlaceholderText("Password");
    txtPassword->setEchoMode(QLineEdit::Password);

    btnLogin = new QPushButton("LOGIN");

    btnLogin->setStyleSheet(
        "QPushButton{"
        "background:#2563eb;"
        "color:white;"
        "font-size:16px;"
        "padding:10px;"
        "border-radius:8px;"
        "}"
        "QPushButton:hover{"
        "background:#1d4ed8;"
        "}"
        );

    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addStretch();
    layout->addWidget(title);
    layout->addSpacing(20);

    layout->addWidget(txtUsername);
    layout->addWidget(txtPassword);

    layout->addSpacing(20);
    layout->addWidget(btnLogin);

    layout->addStretch();

    setStyleSheet(
        "background-color:#111827;"
        "color:white;"
        );

    connect(btnLogin,
            &QPushButton::clicked,
            this,
            &LoginWindow::login);
}


void LoginWindow::login()
{
    QString username = txtUsername->text();
    QString password = txtPassword->text();

    QSqlQuery query;

    query.prepare(
        "SELECT * FROM user "
        "WHERE username = ? "
        "AND password = ?"
        );

    query.addBindValue(username);
    query.addBindValue(password);

    if(!query.exec())
    {
        qDebug() << "ERROR QUERY:";
        qDebug() << query.lastError().text();

        QMessageBox::warning(
            this,
            "Error",
            "Query gagal dijalankan!"
            );

        return;
    }

    if(query.next())
    {
        MainWindow *window = new MainWindow();
        window->show();

        this->close();
    }
    else
    {
        QMessageBox::warning(
            this,
            "Login Gagal",
            "Username atau password salah!"
            );
    }
}