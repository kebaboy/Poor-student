#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "Student.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
//    MainWindow(QWidget *parent = nullptr);
    MainWindow(DatabaseHandler* database, Student* student);
    ~MainWindow();

private slots:
    void on_directory_clicked();

    void on_radioButton_clicked();

    void allclear();
    void on_clear_clicked();

private:
    Ui::MainWindow *ui;
    DatabaseHandler* _database;
    Student* _student;
};
#endif // MAINWINDOW_H
