#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::MainWindow(DatabaseHandler* database, Student* student) {
    _database = database;
    _student = student;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_directory_clicked()
{
    QString directory = QFileDialog::getExistingDirectory(this, "Select directory", QDir::homePath());
    _database = new DatabaseHandler();
    _database->SetPath(directory.toStdString());
    qDebug() << "Directory initialized. Path:" << directory;
//    delete [] _database;
}
