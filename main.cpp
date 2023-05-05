#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DatabaseHandler database;
    Student student;
    MainWindow w(&database, &student);
    w.show();
    return a.exec();
}
