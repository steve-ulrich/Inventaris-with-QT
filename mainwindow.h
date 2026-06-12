#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QLabel;
class QPushButton;
class QTimer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:

    QLabel *titleLabel;

    QLabel *productLabel;
    QLabel *supplierLabel;
    QLabel *stockInLabel;
    QLabel *stockOutLabel;

    QPushButton *btnProduct;
    QPushButton *btnSupplier;
    QPushButton *btnTransaction;

    QTimer *timer;

    void loadDashboard();
};

#endif