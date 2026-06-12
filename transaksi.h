#ifndef TRANSAKSI_H
#define TRANSAKSI_H

#include <QWidget>

class QComboBox;
class QLineEdit;
class QPushButton;
class QTableWidget;

class transaksi : public QWidget
{
    Q_OBJECT

public:
    explicit transaksi(QWidget *parent = nullptr);

private:

    // Input
    QComboBox *comboBarang;
    QComboBox *comboJenis;

    QLineEdit *txtJumlah;
    QLineEdit *txtTanggal;

    // Search
    QLineEdit *txtCari;

    // Button
    QPushButton *btnTambah;
    QPushButton *btnUpdate;
    QPushButton *btnHapus;

    // Table
    QTableWidget *table;

    int selectedId;

    // Function
    void loadBarang();
    void loadData();
    void resetForm();

private slots:

    void tambahData();
    void updateData();
    void hapusData();
    void pilihData();
    void cariData();
};

#endif