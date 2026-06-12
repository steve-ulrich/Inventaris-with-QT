#include "mainwindow.h"
#include "barangwindow.h"
#include "supplierwindow.h"
#include "transaksi.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

#include <QSqlQuery>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("STOCKIFY");
    resize(1000,650);

    QWidget *central = new QWidget;
    setCentralWidget(central);

    QVBoxLayout *layout = new QVBoxLayout;
    central->setLayout(layout);

    // =========================
    // TITLE
    // =========================
    titleLabel = new QLabel("STOCKIFY");
    titleLabel->setAlignment(Qt::AlignCenter);

    titleLabel->setStyleSheet(
        "font-size:32px;"
        "font-weight:bold;"
        "color:white;"
        "padding:20px;"
        );

    // =========================
    // CARD LABEL
    // =========================
    productLabel = new QLabel;
    supplierLabel = new QLabel;
    stockInLabel = new QLabel;
    stockOutLabel = new QLabel;

    QString cardStyle =
        "color:white;"
        "font-size:18px;"
        "background:#2d3748;"
        "padding:15px;"
        "border-radius:10px;";

    productLabel->setStyleSheet(cardStyle);
    supplierLabel->setStyleSheet(cardStyle);
    stockInLabel->setStyleSheet(cardStyle);
    stockOutLabel->setStyleSheet(cardStyle);

    // =========================
    // BUTTON
    // =========================
    btnProduct = new QPushButton("Kelola Barang");
    btnSupplier = new QPushButton("Supplier");
    btnTransaction = new QPushButton("Transaksi");

    QString buttonStyle =
        "QPushButton{"
        "background:#2563eb;"
        "color:white;"
        "font-size:16px;"
        "padding:12px;"
        "border-radius:8px;"
        "}"
        "QPushButton:hover{"
        "background:#1d4ed8;"
        "}";

    btnProduct->setStyleSheet(buttonStyle);
    btnSupplier->setStyleSheet(buttonStyle);
    btnTransaction->setStyleSheet(buttonStyle);

    // =========================
    // LAYOUT
    // =========================
    layout->addWidget(titleLabel);

    layout->addWidget(productLabel);
    layout->addWidget(supplierLabel);
    layout->addWidget(stockInLabel);
    layout->addWidget(stockOutLabel);

    layout->addSpacing(20);

    layout->addWidget(btnProduct);
    layout->addWidget(btnSupplier);
    layout->addWidget(btnTransaction);

    central->setStyleSheet(
        "background-color:#111827;"
        );

    // =========================
    // DASHBOARD AUTO REFRESH
    // =========================
    loadDashboard();

    timer = new QTimer(this);

    connect(timer,
            &QTimer::timeout,
            this,
            &MainWindow::loadDashboard);

    timer->start(1000);

    // =========================
    // BUTTON EVENT
    // =========================
    connect(btnProduct,
            &QPushButton::clicked,
            [=]()
            {
                BarangWindow *window = new BarangWindow;
                window->show();
            });

    connect(btnSupplier,
            &QPushButton::clicked,
            [=]()
            {
                SupplierWindow *window = new SupplierWindow;
                window->show();
            });

    connect(btnTransaction,
            &QPushButton::clicked,
            [=]()
            {
                transaksi *window = new transaksi;
                window->show();
            });
}



// ========================================
// LOAD DASHBOARD
// ========================================
void MainWindow::loadDashboard()
{
    QSqlQuery query;

    // =====================
    // TOTAL BARANG
    // =====================
    query.exec(
        "SELECT COUNT(*) FROM barang"
        );

    query.next();

    int totalBarang =
        query.value(0).toInt();


    // =====================
    // TOTAL SUPPLIER
    // =====================
    query.exec(
        "SELECT COUNT(*) FROM pemasok"
        );

    query.next();

    int totalSupplier =
        query.value(0).toInt();


    // =====================
    // STOK MASUK
    // =====================
    query.exec(
        "SELECT IFNULL(SUM(jumlah),0) "
        "FROM transaksi "
        "WHERE jenis='MASUK'"
        );

    query.next();

    int stokMasuk =
        query.value(0).toInt();


    // =====================
    // STOK KELUAR
    // =====================
    query.exec(
        "SELECT IFNULL(SUM(jumlah),0) "
        "FROM transaksi "
        "WHERE jenis='KELUAR'"
        );

    query.next();

    int stokKeluar =
        query.value(0).toInt();


    // =====================
    // TAMPILKAN KE LABEL
    // =====================
    productLabel->setText(
        "Total Barang : "
        + QString::number(totalBarang));

    supplierLabel->setText(
        "Total Supplier : "
        + QString::number(totalSupplier));

    stockInLabel->setText(
        "Stok Masuk : "
        + QString::number(stokMasuk));

    stockOutLabel->setText(
        "Stok Keluar : "
        + QString::number(stokKeluar));
}