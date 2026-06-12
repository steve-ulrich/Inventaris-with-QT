cmake_minimum_required(VERSION 3.19)
project(STOCKIFY LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Sql)

qt_standard_project_setup()

qt_add_executable(STOCKIFY
    main.cpp

    mainwindow.h
    mainwindow.cpp

    barangwindow.h
    barangwindow.cpp

    supplierwindow.h
    supplierwindow.cpp

    transaksi.h
    transaksi.cpp

    loginwindow.h
    loginwindow.cpp

    databasemanager.h
    databasemanager.cpp
)

target_link_libraries(STOCKIFY
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Sql
)