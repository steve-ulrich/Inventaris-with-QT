#include "barangwindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QMessageBox>

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

BarangWindow::BarangWindow(QWidget *parent)
    : QWidget(parent)
{
    selectedId = -1;

    setWindowTitle("Kelola Barang");
    resize(950,600);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *title = new QLabel("DATA BARANG");
    title->setAlignment(Qt::AlignCenter);

    title->setStyleSheet(
        "font-size:28px;"
        "font-weight:bold;"
        "color:white;"
        );

    // Search
    txtCari = new QLineEdit;
    txtCari->setPlaceholderText("Cari nama barang...");

    // Input
    txtNama = new QLineEdit;
    txtNama->setPlaceholderText("Nama Barang");

    txtStok = new QLineEdit;
    txtStok->setPlaceholderText("Stok");

    txtHargaBeli = new QLineEdit;
    txtHargaBeli->setPlaceholderText("Harga Beli");

    txtHargaJual = new QLineEdit;
    txtHargaJual->setPlaceholderText("Harga Jual");

    // Tombol
    btnTambah = new QPushButton("Tambah");
    btnUpdate = new QPushButton("Update");
    btnHapus = new QPushButton("Hapus");

    btnTambah->setStyleSheet(
        "background:#16a34a;"
        "color:white;"
        "padding:10px;"
        "border-radius:8px;"
        );

    btnUpdate->setStyleSheet(
        "background:#f59e0b;"
        "color:white;"
        "padding:10px;"
        "border-radius:8px;"
        );

    btnHapus->setStyleSheet(
        "background:#dc2626;"
        "color:white;"
        "padding:10px;"
        "border-radius:8px;"
        );

    // Form
    QHBoxLayout *formLayout = new QHBoxLayout;

    formLayout->addWidget(txtNama);
    formLayout->addWidget(txtStok);
    formLayout->addWidget(txtHargaBeli);
    formLayout->addWidget(txtHargaJual);

    // Tombol
    QHBoxLayout *buttonLayout = new QHBoxLayout;

    buttonLayout->addWidget(btnTambah);
    buttonLayout->addWidget(btnUpdate);
    buttonLayout->addWidget(btnHapus);

    // Table
    tableBarang = new QTableWidget;

    tableBarang->setColumnCount(5);

    tableBarang->setHorizontalHeaderLabels(
        {"ID","Nama Barang","Stok","Harga Beli","Harga Jual"}
        );

    tableBarang->horizontalHeader()
        ->setSectionResizeMode(QHeaderView::Stretch);

    tableBarang->verticalHeader()->setVisible(false);

    tableBarang->setStyleSheet(
        "QTableWidget{"
        "background:white;"
        "color:black;"
        "gridline-color:gray;"
        "}"
        "QHeaderView::section{"
        "background:#1e3a8a;"
        "color:white;"
        "font-weight:bold;"
        "padding:6px;"
        "}"
        );

    // Layout
    mainLayout->addWidget(title);
    mainLayout->addWidget(txtCari);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(tableBarang);

    setStyleSheet(
        "background-color:#111827;"
        "color:white;"
        );

    connect(btnTambah,
            &QPushButton::clicked,
            this,
            &BarangWindow::tambahBarang);

    connect(btnUpdate,
            &QPushButton::clicked,
            this,
            &BarangWindow::updateBarang);

    connect(btnHapus,
            &QPushButton::clicked,
            this,
            &BarangWindow::hapusBarang);

    connect(tableBarang,
            &QTableWidget::cellClicked,
            this,
            &BarangWindow::pilihData);

    connect(txtCari,
            &QLineEdit::textChanged,
            this,
            &BarangWindow::cariBarang);

    loadData();
}


// =========================
// TAMBAH BARANG
// =========================
void BarangWindow::tambahBarang()
{
    if(txtNama->text().isEmpty() ||
        txtStok->text().isEmpty() ||
        txtHargaBeli->text().isEmpty() ||
        txtHargaJual->text().isEmpty())
    {
        QMessageBox::warning(
            this,
            "Peringatan",
            "Semua field harus diisi!");

        return;
    }

    QSqlQuery query;

    query.prepare(
        "INSERT INTO barang(nama,stok,harga_beli,harga_jual)"
        "VALUES(?,?,?,?)"
        );

    query.addBindValue(txtNama->text());
    query.addBindValue(txtStok->text().toInt());
    query.addBindValue(txtHargaBeli->text().toDouble());
    query.addBindValue(txtHargaJual->text().toDouble());

    if(query.exec())
    {
        loadData();

        txtNama->clear();
        txtStok->clear();
        txtHargaBeli->clear();
        txtHargaJual->clear();

        QMessageBox::information(
            this,
            "Sukses",
            "Data berhasil ditambahkan");
    }
    else
    {
        qDebug() << query.lastError().text();

        QMessageBox::critical(
            this,
            "Error SQL",
            query.lastError().text());
    }
}


// =========================
// UPDATE BARANG
// =========================
void BarangWindow::updateBarang()
{
    if(selectedId == -1)
        return;

    QSqlQuery query;

    query.prepare(
        "UPDATE barang "
        "SET nama=?,stok=?,harga_beli=?,harga_jual=? "
        "WHERE id=?"
        );

    query.addBindValue(txtNama->text());
    query.addBindValue(txtStok->text().toInt());
    query.addBindValue(txtHargaBeli->text().toDouble());
    query.addBindValue(txtHargaJual->text().toDouble());
    query.addBindValue(selectedId);

    if(query.exec())
    {
        loadData();

        QMessageBox::information(
            this,
            "Sukses",
            "Data berhasil diupdate");
    }
}


// =========================
// HAPUS BARANG
// =========================
void BarangWindow::hapusBarang()
{
    if(selectedId == -1)
        return;

    QSqlQuery query;

    query.prepare(
        "DELETE FROM barang WHERE id=?"
        );

    query.addBindValue(selectedId);

    if(query.exec())
    {
        loadData();

        txtNama->clear();
        txtStok->clear();
        txtHargaBeli->clear();
        txtHargaJual->clear();

        selectedId = -1;

        QMessageBox::information(
            this,
            "Sukses",
            "Data berhasil dihapus");
    }
}


// =========================
// PILIH DATA
// =========================
void BarangWindow::pilihData(int row, int column)
{
    Q_UNUSED(column);

    if(tableBarang->item(row,0)==nullptr)
        return;

    selectedId =
        tableBarang->item(row,0)->text().toInt();

    txtNama->setText(
        tableBarang->item(row,1)->text());

    txtStok->setText(
        tableBarang->item(row,2)->text());

    txtHargaBeli->setText(
        tableBarang->item(row,3)->text());

    txtHargaJual->setText(
        tableBarang->item(row,4)->text());
}


// =========================
// LOAD DATA
// =========================
void BarangWindow::loadData()
{
    tableBarang->setRowCount(0);

    QSqlQuery query;

    if(!query.exec("SELECT * FROM barang"))
    {
        qDebug() << query.lastError().text();
        return;
    }

    int row = 0;

    while(query.next())
    {
        tableBarang->insertRow(row);

        tableBarang->setItem(
            row,0,
            new QTableWidgetItem(query.value("id").toString()));

        tableBarang->setItem(
            row,1,
            new QTableWidgetItem(query.value("nama").toString()));

        tableBarang->setItem(
            row,2,
            new QTableWidgetItem(query.value("stok").toString()));

        tableBarang->setItem(
            row,3,
            new QTableWidgetItem(query.value("harga_beli").toString()));

        tableBarang->setItem(
            row,4,
            new QTableWidgetItem(query.value("harga_jual").toString()));

        row++;
    }
}


// =========================
// SEARCH BARANG
// =========================
void BarangWindow::cariBarang()
{
    tableBarang->setRowCount(0);

    QSqlQuery query;

    query.prepare(
        "SELECT * FROM barang "
        "WHERE nama LIKE ?"
        );

    query.addBindValue(
        "%" + txtCari->text() + "%"
        );

    if(!query.exec())
    {
        qDebug() << query.lastError().text();
        return;
    }

    int row = 0;

    while(query.next())
    {
        tableBarang->insertRow(row);

        tableBarang->setItem(
            row,0,
            new QTableWidgetItem(query.value("id").toString()));

        tableBarang->setItem(
            row,1,
            new QTableWidgetItem(query.value("nama").toString()));

        tableBarang->setItem(
            row,2,
            new QTableWidgetItem(query.value("stok").toString()));

        tableBarang->setItem(
            row,3,
            new QTableWidgetItem(query.value("harga_beli").toString()));

        tableBarang->setItem(
            row,4,
            new QTableWidgetItem(query.value("harga_jual").toString()));

        row++;
    }
}