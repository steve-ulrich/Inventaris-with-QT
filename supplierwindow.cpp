#include "supplierwindow.h"

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

SupplierWindow::SupplierWindow(QWidget *parent)
    : QWidget(parent)
{
    selectedId = -1;

    setWindowTitle("Data Supplier");
    resize(950,600);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *title = new QLabel("DATA SUPPLIER");
    title->setAlignment(Qt::AlignCenter);

    title->setStyleSheet(
        "font-size:28px;"
        "font-weight:bold;"
        "color:white;"
        );

    // ================= SEARCH =================
    txtCari = new QLineEdit;
    txtCari->setPlaceholderText("Cari supplier...");

    // ================= INPUT =================
    namaInput = new QLineEdit;
    namaInput->setPlaceholderText("Nama Supplier");

    alamatInput = new QLineEdit;
    alamatInput->setPlaceholderText("Alamat");

    teleponInput = new QLineEdit;
    teleponInput->setPlaceholderText("Telepon");

    QHBoxLayout *formLayout = new QHBoxLayout;

    formLayout->addWidget(namaInput);
    formLayout->addWidget(alamatInput);
    formLayout->addWidget(teleponInput);

    // ================= BUTTON =================
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

    QHBoxLayout *buttonLayout = new QHBoxLayout;

    buttonLayout->addWidget(btnTambah);
    buttonLayout->addWidget(btnUpdate);
    buttonLayout->addWidget(btnHapus);

    // ================= TABLE =================
    table = new QTableWidget;

    table->setColumnCount(4);

    table->setHorizontalHeaderLabels(
        {"ID","Nama Supplier","Alamat","Telepon"}
        );

    table->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch
        );

    table->verticalHeader()->setVisible(false);

    table->setStyleSheet(
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

    // ================= LAYOUT =================
    mainLayout->addWidget(title);

    mainLayout->addWidget(txtCari);

    mainLayout->addLayout(formLayout);

    mainLayout->addLayout(buttonLayout);

    mainLayout->addWidget(table);

    setStyleSheet(
        "background-color:#111827;"
        "color:white;"
        );

    // ================= CONNECT =================
    connect(btnTambah,
            &QPushButton::clicked,
            this,
            &SupplierWindow::tambahSupplier);

    connect(btnUpdate,
            &QPushButton::clicked,
            this,
            &SupplierWindow::updateSupplier);

    connect(btnHapus,
            &QPushButton::clicked,
            this,
            &SupplierWindow::hapusSupplier);

    connect(txtCari,
            &QLineEdit::textChanged,
            this,
            &SupplierWindow::cariSupplier);

    connect(table,
            &QTableWidget::cellClicked,
            this,
            &SupplierWindow::pilihData);

    tampilData();
}


// ======================================
// TAMPIL DATA
// ======================================
void SupplierWindow::tampilData()
{
    table->setRowCount(0);

    QSqlQuery query;

    query.exec("SELECT * FROM pemasok");

    int row = 0;

    while(query.next())
    {
        table->insertRow(row);

        for(int col=0; col<4; col++)
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


// ======================================
// TAMBAH SUPPLIER
// ======================================
void SupplierWindow::tambahSupplier()
{
    QSqlQuery query;

    query.prepare(
        "INSERT INTO pemasok "
        "(nama,alamat,telepon) "
        "VALUES (?,?,?)"
        );

    query.addBindValue(namaInput->text());
    query.addBindValue(alamatInput->text());
    query.addBindValue(teleponInput->text());

    if(query.exec())
    {
        tampilData();

        resetForm();

        QMessageBox::information(
            this,
            "Sukses",
            "Data berhasil ditambahkan"
            );
    }
}


// ======================================
// UPDATE SUPPLIER
// ======================================
void SupplierWindow::updateSupplier()
{
    if(selectedId == -1)
        return;

    QSqlQuery query;

    query.prepare(
        "UPDATE pemasok "
        "SET nama=?, "
        "alamat=?, "
        "telepon=? "
        "WHERE id=?"
        );

    query.addBindValue(namaInput->text());
    query.addBindValue(alamatInput->text());
    query.addBindValue(teleponInput->text());
    query.addBindValue(selectedId);

    if(query.exec())
    {
        tampilData();

        resetForm();

        QMessageBox::information(
            this,
            "Sukses",
            "Data berhasil diupdate"
            );
    }
}


// ======================================
// HAPUS SUPPLIER
// ======================================
void SupplierWindow::hapusSupplier()
{
    if(selectedId == -1)
        return;

    QSqlQuery query;

    query.prepare(
        "DELETE FROM pemasok "
        "WHERE id=?"
        );

    query.addBindValue(selectedId);

    if(query.exec())
    {
        tampilData();

        resetForm();

        QMessageBox::information(
            this,
            "Sukses",
            "Data berhasil dihapus"
            );
    }
}


// ======================================
// PILIH DATA
// ======================================
void SupplierWindow::pilihData()
{
    int row = table->currentRow();

    selectedId =
        table->item(row,0)->text().toInt();

    namaInput->setText(
        table->item(row,1)->text()
        );

    alamatInput->setText(
        table->item(row,2)->text()
        );

    teleponInput->setText(
        table->item(row,3)->text()
        );
}


// ======================================
// SEARCH SUPPLIER
// ======================================
void SupplierWindow::cariSupplier()
{
    table->setRowCount(0);

    QSqlQuery query;

    query.prepare(
        "SELECT * FROM pemasok "
        "WHERE nama LIKE ?"
        );

    query.addBindValue(
        "%" + txtCari->text() + "%"
        );

    query.exec();

    int row = 0;

    while(query.next())
    {
        table->insertRow(row);

        for(int col=0; col<4; col++)
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


// ======================================
// RESET FORM
// ======================================
void SupplierWindow::resetForm()
{
    namaInput->clear();
    alamatInput->clear();
    teleponInput->clear();

    selectedId = -1;
}