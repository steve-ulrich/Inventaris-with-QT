#ifndef SUPPLIERWINDOW_H
#define SUPPLIERWINDOW_H

#include <QWidget>

class QLineEdit;
class QPushButton;
class QTableWidget;

class SupplierWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SupplierWindow(QWidget *parent = nullptr);

private:

    // Input
    QLineEdit *namaInput;
    QLineEdit *alamatInput;
    QLineEdit *teleponInput;

    // Search
    QLineEdit *txtCari;

    // Button
    QPushButton *btnTambah;
    QPushButton *btnUpdate;
    QPushButton *btnHapus;

    // Table
    QTableWidget *table;

    // ID supplier yang dipilih
    int selectedId;

    // Function
    void tampilData();
    void resetForm();

private slots:

    void tambahSupplier();

    void updateSupplier();

    void hapusSupplier();

    void cariSupplier();

    void pilihData();
};

#endif