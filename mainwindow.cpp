#include "mainwindow.h"
#include "./ui_mainwindow.h"

//MainWindow::MainWindow(QWidget *parent)
//    : QMainWindow(parent)
//    , ui(new Ui::MainWindow)
//{
//    ui->setupUi(this);
//}

MainWindow::MainWindow(DatabaseHandler* database, Student* student): ui(new Ui::MainWindow), _database(database), _student(student)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::allclear()
{
    ui->cafe_line->setEnabled(false);
    ui->cafe_line->clear();
    ui->city_line->setEnabled(false);
    ui->city_line->clear();
    ui->address_line->setEnabled(false);
    ui->address_line->clear();
    ui->institute_line->setEnabled(false);
    ui->institute_line->clear();
    ui->name_line->setEnabled(false);
    ui->name_line->clear();
    ui->cinema_line->setEnabled(false);
    ui->cinema_line->clear();
    ui->spinBox_month->setEnabled(false);
    ui->spinBox_month->clear();
    ui->calculate->setEnabled(false);
    ui->cafe->setEnabled(false);
    ui->city->setEnabled(false);
    ui->address->setEnabled(false);
    ui->institute->setEnabled(false);
    ui->name->setEnabled(false);
    ui->cinema->setEnabled(false);
    ui->month->setEnabled(false);
    ui->radioButton->setEnabled(false);
    ui->radioButton->setChecked(false);
    ui->age->setEnabled(false);
    ui->spinBox_age->setEnabled(false);
    ui->spinBox_age->clear();
    ui->clear->setEnabled(false);
}

void MainWindow::on_directory_clicked()
{
    QString directory = QFileDialog::getExistingDirectory(this, "Select directory", QDir::homePath());
//    _database = new DatabaseHandler();
    _database->setPath(directory.toStdString());
    if (_database->initDatabase()) {
        ui->cafe_line->setEnabled(true);
        ui->city_line->setEnabled(true);
        ui->address_line->setEnabled(true);
        ui->institute_line->setEnabled(true);
        ui->name_line->setEnabled(true);
        ui->cinema_line->setEnabled(true);
        ui->spinBox_month->setEnabled(true);
        ui->calculate->setEnabled(true);
        ui->cafe->setEnabled(true);
        ui->city->setEnabled(true);
        ui->address->setEnabled(true);
        ui->institute->setEnabled(true);
        ui->name->setEnabled(true);
        ui->cinema->setEnabled(true);
        ui->month->setEnabled(true);
        ui->radioButton->setEnabled(true);
        ui->clear->setEnabled(true);
    } else {
        allclear();
        QMessageBox::warning(this, "warning", "Try another folder");
    }
    qDebug() << "Directory Path:" << directory;
//    delete [] _database;
    std::vector<std::string> v = _database->getCities();
    QStringList qlist;
    for(auto elem: v) {
        qlist.append(QString::fromStdString(elem));
    }
    QCompleter *completerCities = new QCompleter(qlist, this);
    completerCities->setCaseSensitivity(Qt::CaseInsensitive);
    ui->city_line->setCompleter(completerCities);

    v = _database->getAddresses();
    qlist.clear();
    for(auto elem: v) {
        qlist.append(QString::fromStdString(elem));
    }
    QCompleter *completerAddresses = new QCompleter(qlist, this);
    completerAddresses->setCaseSensitivity(Qt::CaseInsensitive);
    ui->address_line->setCompleter(completerAddresses);

    v = _database->getInstitutes();
    qlist.clear();
    for(auto elem: v) {
        qlist.append(QString::fromStdString(elem));
    }
    QCompleter *completerInstitutes = new QCompleter(qlist, this);
    completerInstitutes->setCaseSensitivity(Qt::CaseInsensitive);
    ui->institute_line->setCompleter(completerInstitutes);

    v = _database->getCafes();
    qlist.clear();
    for(auto elem: v) {
        qlist.append(QString::fromStdString(elem));
    }
    QCompleter *completerCafes = new QCompleter(qlist, this);
    completerCafes->setCaseSensitivity(Qt::CaseInsensitive);
    ui->cafe_line->setCompleter(completerCafes);

    v = _database->getCinemas();
    qlist.clear();
    for(auto elem: v) {
        qlist.append(QString::fromStdString(elem));
    }
    QCompleter *completerCinemas = new QCompleter(qlist, this);
    completerCinemas->setCaseSensitivity(Qt::CaseInsensitive);
    ui->cinema_line->setCompleter(completerCinemas);
}

void MainWindow::on_radioButton_clicked()
{
    if (ui->radioButton->isChecked()) {
        ui->age->setEnabled(true);
        ui->spinBox_age->setEnabled(true);
    } else {
        ui->age->setEnabled(false);
        ui->spinBox_age->setEnabled(false);
    }
}

void MainWindow::on_clear_clicked()
{
    ui->cafe_line->clear();
    ui->city_line->clear();
    ui->address_line->clear();
    ui->institute_line->clear();
    ui->name_line->clear();
    ui->cinema_line->clear();
    ui->spinBox_month->setValue(0);
    ui->spinBox_age->setValue(0);
}
