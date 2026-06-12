#include "transaksi.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QMessageBox>

#include <QSqlQuery>
#include <QSqlError>

transaksi::transaksi(QWidget *parent)
    : QWidget(parent)
{
    selectedId = -1;

    setWindowTitle("Data Transaksi");
    resize(950,600);

    QLabel *title = new QLabel("DATA TRANSAKSI");
    title->setAlignment(Qt::AlignCenter);

    title->setStyleSheet(
        "font-size:28px;"
        "font-weight:bold;"
        "color:white;"
        );

    // Search
    txtCari = new QLineEdit;
    txtCari->setPlaceholderText("Cari transaksi...");

    // Input
    comboBarang = new QComboBox;

    comboJenis = new QComboBox;
    comboJenis->addItem("MASUK");
    comboJenis->addItem("KELUAR");

    txtJumlah = new QLineEdit;
    txtJumlah->setPlaceholderText("Jumlah");

    txtTanggal = new QLineEdit;
    txtTanggal->setPlaceholderText("Tanggal");

    // Button
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

    // Layout input
    QHBoxLayout *inputLayout = new QHBoxLayout;

    inputLayout->addWidget(comboBarang);
    inputLayout->addWidget(comboJenis);
    inputLayout->addWidget(txtJumlah);
    inputLayout->addWidget(txtTanggal);

    // Layout button
    QHBoxLayout *buttonLayout = new QHBoxLayout;

    buttonLayout->addWidget(btnTambah);
    buttonLayout->addWidget(btnUpdate);
    buttonLayout->addWidget(btnHapus);

    // Table
    table = new QTableWidget;

    table->setColumnCount(5);

    table->setHorizontalHeaderLabels(
        {"ID","Barang","Jenis","Jumlah","Tanggal"}
        );

    table->horizontalHeader()
        ->setSectionResizeMode(QHeaderView::Stretch);

    table->verticalHeader()->setVisible(false);

    table->setStyleSheet(
        "QTableWidget{"
        "background:white;"
        "color:black;"
        "}"
        "QHeaderView::section{"
        "background:#1e3a8a;"
        "color:white;"
        "font-weight:bold;"
        "padding:6px;"
        "}"
        );

    // Main layout
    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addWidget(title);
    layout->addWidget(txtCari);

    layout->addLayout(inputLayout);
    layout->addLayout(buttonLayout);

    layout->addWidget(table);

    setStyleSheet(
        "background-color:#111827;"
        "color:white;"
        );

    connect(btnTambah,
            &QPushButton::clicked,
            this,
            &transaksi::tambahData);

    connect(btnUpdate,
            &QPushButton::clicked,
            this,
            &transaksi::updateData);

    connect(btnHapus,
            &QPushButton::clicked,
            this,
            &transaksi::hapusData);

    connect(table,
            &QTableWidget::cellClicked,
            this,
            &transaksi::pilihData);

    connect(txtCari,
            &QLineEdit::textChanged,
            this,
            &transaksi::cariData);

    loadBarang();
    loadData();
}



// ============================
// LOAD BARANG
// ============================
void transaksi::loadBarang()
{
    comboBarang->clear();

    QSqlQuery query;

    query.exec(
        "SELECT nama FROM barang"
        );

    while(query.next())
    {
        comboBarang->addItem(
            query.value("nama").toString()
            );
    }
}



// ============================
// LOAD DATA
// ============================
void transaksi::loadData()
{
    table->setRowCount(0);

    QSqlQuery query;

    query.exec(
        "SELECT id,nama_barang,jenis,jumlah,tanggal "
        "FROM transaksi"
        );

    int row = 0;

    while(query.next())
    {
        table->insertRow(row);

        for(int col=0; col<5; col++)
        {
            table->setItem(
                row,
                col,
                new QTableWidgetItem(
                    query.value(col).toString()
                    )
                );
        }

        row++;
    }
}



// ============================
// TAMBAH
// ============================
void transaksi::tambahData()
{
    QSqlQuery query;

    query.prepare(
        "INSERT INTO transaksi "
        "(nama_barang,jenis,jumlah,tanggal) "
        "VALUES(?,?,?,?)"
        );

    query.addBindValue(comboBarang->currentText());
    query.addBindValue(comboJenis->currentText());
    query.addBindValue(txtJumlah->text().toInt());
    query.addBindValue(txtTanggal->text());

    if(query.exec())
    {
        loadData();
        resetForm();

        QMessageBox::information(
            this,
            "Sukses",
            "Transaksi berhasil ditambahkan"
            );
    }
}



// ============================
// UPDATE
// ============================
void transaksi::updateData()
{
    if(selectedId==-1)
        return;

    QSqlQuery query;

    query.prepare(
        "UPDATE transaksi "
        "SET nama_barang=?,"
        "jenis=?,"
        "jumlah=?,"
        "tanggal=? "
        "WHERE id=?"
        );

    query.addBindValue(comboBarang->currentText());
    query.addBindValue(comboJenis->currentText());
    query.addBindValue(txtJumlah->text().toInt());
    query.addBindValue(txtTanggal->text());
    query.addBindValue(selectedId);

    if(query.exec())
    {
        loadData();

        QMessageBox::information(
            this,
            "Sukses",
            "Data berhasil diupdate"
            );
    }
}



// ============================
// HAPUS
// ============================
void transaksi::hapusData()
{
    if(selectedId==-1)
        return;

    QSqlQuery query;

    query.prepare(
        "DELETE FROM transaksi "
        "WHERE id=?"
        );

    query.addBindValue(selectedId);

    if(query.exec())
    {
        loadData();
        resetForm();

        QMessageBox::information(
            this,
            "Sukses",
            "Data berhasil dihapus"
            );
    }
}



// ============================
// PILIH DATA
// ============================
void transaksi::pilihData()
{
    int row = table->currentRow();

    selectedId =
        table->item(row,0)
            ->text()
            .toInt();

    comboBarang->setCurrentText(
        table->item(row,1)->text()
        );

    comboJenis->setCurrentText(
        table->item(row,2)->text()
        );

    txtJumlah->setText(
        table->item(row,3)->text()
        );

    txtTanggal->setText(
        table->item(row,4)->text()
        );
}



// ============================
// CARI DATA
// ============================
void transaksi::cariData()
{
    table->setRowCount(0);

    QSqlQuery query;

    query.prepare(
        "SELECT * FROM transaksi "
        "WHERE nama_barang LIKE ?"
        );

    query.addBindValue(
        "%" + txtCari->text() + "%"
        );

    query.exec();

    int row = 0;

    while(query.next())
    {
        table->insertRow(row);

        for(int col=0; col<5; col++)
        {
            table->setItem(
                row,
                col,
                new QTableWidgetItem(
                    query.value(col).toString()
                    )
                );
        }

        row++;
    }
}



// ============================
// RESET FORM
// ============================
void transaksi::resetForm()
{
    txtJumlah->clear();
    txtTanggal->clear();

    selectedId = -1;
}