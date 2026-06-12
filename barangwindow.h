#ifndef BARANGWINDOW_H
#define BARANGWINDOW_H

#include <QWidget>

class QLineEdit;
class QPushButton;
class QTableWidget;

class BarangWindow : public QWidget
{
    Q_OBJECT

public:
    explicit BarangWindow(QWidget *parent = nullptr);

private slots:
    void tambahBarang();
    void updateBarang();
    void hapusBarang();
    void pilihData(int row, int column);
    void cariBarang();

private:
    QLineEdit *txtNama;
    QLineEdit *txtStok;
    QLineEdit *txtHargaBeli;
    QLineEdit *txtHargaJual;
    QLineEdit *txtCari;

    QPushButton *btnTambah;
    QPushButton *btnUpdate;
    QPushButton *btnHapus;

    QTableWidget *tableBarang;

    int selectedId;

    void loadData();
};

#endif