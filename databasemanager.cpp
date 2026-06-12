#include "databasemanager.h"

#include <QFileInfo>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

bool DatabaseManager::connectDatabase()
{
    QSqlDatabase db =
        QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName(
        "D:/Kuliah Steve/Semester 4/PBO/Project UAS - QT/STOCKIFY/build/Desktop_Qt_6_11_1_MinGW_64_bit-Debug/stockify.db");

    if(!db.open())
    {
        qDebug() << "DATABASE FAILED";
        return false;
    }

    qDebug() << "DATABASE CONNECTED";
    qDebug() << "PATH DATABASE:";
    qDebug() << QFileInfo(db.databaseName()).absoluteFilePath();

    QSqlQuery query;

    // ======================
    // TABEL USER
    // ======================
    query.exec(
        "CREATE TABLE IF NOT EXISTS user("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT,"
        "password TEXT)"
        );

    query.exec(
        "INSERT INTO user(username,password)"
        "SELECT 'admin','admin123'"
        " WHERE NOT EXISTS("
        "SELECT 1 FROM user WHERE username='admin')"
        );



    // ======================
    // TABEL BARANG
    // ======================
    query.exec(
        "CREATE TABLE IF NOT EXISTS barang("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "nama TEXT,"
        "stok INTEGER,"
        "harga_beli REAL,"
        "harga_jual REAL)"
        );



    // ======================
    // TABEL PEMASOK
    // ======================
    query.exec(
        "CREATE TABLE IF NOT EXISTS pemasok("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "nama TEXT,"
        "alamat TEXT,"
        "telepon TEXT)"
        );



    // ======================
    // TABEL TRANSAKSI
    // ======================
    query.exec(
        "CREATE TABLE IF NOT EXISTS transaksi("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "nama_barang TEXT,"
        "jenis TEXT,"
        "jumlah INTEGER,"
        "tanggal TEXT)"
        );



    // ======================
    // DATA CONTOH BARANG
    // ======================
    query.exec(
        "INSERT INTO barang(nama,stok,harga_beli,harga_jual)"
        "SELECT 'Laptop Asus',10,7000000,8000000 "
        "WHERE NOT EXISTS("
        "SELECT 1 FROM barang)"
        );

    query.exec(
        "INSERT INTO barang(nama,stok,harga_beli,harga_jual)"
        "SELECT 'Mouse Logitech',20,100000,150000 "
        "WHERE (SELECT COUNT(*) FROM barang)=1"
        );

    query.exec(
        "INSERT INTO barang(nama,stok,harga_beli,harga_jual)"
        "SELECT 'Keyboard Mechanical',15,300000,450000 "
        "WHERE (SELECT COUNT(*) FROM barang)=2"
        );



    // ======================
    // DATA CONTOH PEMASOK
    // ======================
    query.exec(
        "INSERT INTO pemasok(nama,alamat,telepon)"
        "SELECT 'PT Teknologi Jaya',"
        "'Surabaya',"
        "'08123456789' "
        "WHERE NOT EXISTS("
        "SELECT 1 FROM pemasok)"
        );



    // ======================
    // DATA CONTOH TRANSAKSI
    // ======================
    query.exec(
        "INSERT INTO transaksi(nama_barang,jenis,jumlah,tanggal)"
        "SELECT 'Laptop Asus','MASUK',5,'2026-06-12' "
        "WHERE NOT EXISTS("
        "SELECT 1 FROM transaksi)"
        );

    query.exec(
        "INSERT INTO transaksi(nama_barang,jenis,jumlah,tanggal)"
        "SELECT 'Mouse Logitech','KELUAR',2,'2026-06-12' "
        "WHERE (SELECT COUNT(*) FROM transaksi)=1"
        );

    return true;
}