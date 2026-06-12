#include <QApplication>

#include "loginwindow.h"
#include "databasemanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(!DatabaseManager::connectDatabase())
    {
        return -1;
    }

    LoginWindow login;
    login.show();

    return a.exec();
}