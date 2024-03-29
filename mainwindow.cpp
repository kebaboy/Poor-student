#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <fstream>

MainWindow::MainWindow(DatabaseHandler* database, Student* student, QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow), _database(database), _student(student)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::enableUI() {
    ui->costs->setText(QString::fromStdString(_database->getCosts()));
    ui->costs->setVisible(true);
    ui->inst->setText(QString::fromStdString(_database->getInst()));
    ui->inst->setVisible(true);
    ui->tr->setText(QString::fromStdString(_database->getTr()));
    ui->tr->setVisible(true);
    ui->cafcin->setText(QString::fromStdString(_database->getCafcin()));
    ui->cafcin->setVisible(true);
    ui->output->setText("");
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
}

void MainWindow::allclear()
{
    ui->output->clear();
    ui->cafe_line->setEnabled(false);
    ui->cafe_line->clear();
    ui->cafe_line->setStyleSheet("");
    ui->city_line->setEnabled(false);
    ui->city_line->clear();
    ui->city_line->setStyleSheet("");
    ui->address_line->setEnabled(false);
    ui->address_line->clear();
    ui->address_line->setStyleSheet("");
    ui->institute_line->setEnabled(false);
    ui->institute_line->clear();
    ui->institute_line->setStyleSheet("");
    ui->name_line->setEnabled(false);
    ui->name_line->clear();
    ui->name_line->setStyleSheet("");
    ui->cinema_line->setEnabled(false);
    ui->cinema_line->clear();
    ui->cinema_line->setStyleSheet("");
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
    ui->spinBox_month->setValue(0);
    ui->spinBox_month->setStyleSheet("");
    ui->radioButton->setEnabled(false);
    ui->radioButton->setChecked(false);
    ui->age->setEnabled(false);
    ui->spinBox_age->setEnabled(false);
    ui->spinBox_age->setValue(0);
    ui->spinBox_age->setStyleSheet("");
    ui->clear->setEnabled(false);
    ui->tr->setVisible(false);
    ui->cafcin->setVisible(false);
    ui->costs->setVisible(false);
    ui->inst->setVisible(false);
}

void MainWindow::setCompleter(const std::vector<std::string>& v, QLineEdit* line) {
    QStringList qlist;
    for(auto elem: v) {
        qlist.append(QString::fromStdString(elem));
    }
    delete line->completer();
    line->setCompleter(nullptr);
    QCompleter *completer = new QCompleter(qlist, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    line->setCompleter(completer);
}

void MainWindow::on_directory_clicked()
{
    QString directory = QFileDialog::getExistingDirectory(this, "Select directory", QDir::homePath());
    _database->setPath(directory.toStdString());
    try {
        _database->initDatabase();
        enableUI();
        setCompleter(_database->getCities(), ui->city_line);
        setCompleter(_database->getAddresses(), ui->address_line);
        setCompleter(_database->getInstitutes(), ui->institute_line);
        setCompleter(_database->getCafes(), ui->cafe_line);
        setCompleter(_database->getCinemas(), ui->cinema_line);
    } catch (const DatabaseHandler::FileOpenException& ex) {
        QString errorMessage = QString::fromStdString(ex.what());
        QString failedFiles = QString::fromStdString(ex.getFilename());
        allclear();
        QMessageBox::warning(this, "Error", "Failed to open the following files:\n" + failedFiles);
    }
    qDebug() << "Directory Path:" << directory;
}

void MainWindow::on_radioButton_clicked()
{
    if (ui->radioButton->isChecked()) {
        ui->age->setEnabled(true);
        ui->spinBox_age->setEnabled(true);
    } else {
        ui->age->setEnabled(false);
        ui->spinBox_age->setEnabled(false);
        ui->spinBox_age->setStyleSheet("");
    }
}

void MainWindow::on_clear_clicked()
{
    ui->output->clear();
    QList<QLineEdit*> lineEdits = this->findChildren<QLineEdit*>();
    foreach (QLineEdit *lineEdit, lineEdits) {
        lineEdit->clear();
        lineEdit->setStyleSheet("");
    }
    ui->spinBox_month->setValue(0);
    ui->spinBox_month->setStyleSheet("");
    ui->spinBox_age->setValue(0);
    ui->spinBox_age->setStyleSheet("");
}

bool MainWindow::begincheckLines()
{
    QList<QLineEdit*> lineEdits = this->findChildren<QLineEdit*>();
    bool flag = true;
    foreach (QLineEdit *lineEdit, lineEdits) {
        if (lineEdit->text() == "") {
            flag = false;
            lineEdit->setStyleSheet("QLineEdit {\nborder: 1px solid red;\n}");
        } else {
            lineEdit->setStyleSheet("");
        }
    }

    if (ui->spinBox_month->value() == 0 || ui->spinBox_month->text() == "") {
        flag = false;
        ui->spinBox_month->setStyleSheet("QSpinBox {\nborder: 1px solid red;\n}");
    } else {
        ui->spinBox_month->setStyleSheet("");
    }

    if ((ui->spinBox_age->value() == 0 || ui->spinBox_age->text() == "") && ui->spinBox_age->isEnabled()) {
        flag = false;
        ui->spinBox_age->setStyleSheet("QSpinBox {\nborder: 1px solid red;\n}");
    } else {
        ui->spinBox_age->setStyleSheet("");
    }
    return flag;
}

bool MainWindow::endcheckLines() {
    bool flag = true;
    ui->output->setStyleSheet("QLabel { color: red; font-size: 25px;}");
    bool flagcity = false;
    for (int i = 0; ui->city_line->completer()->setCurrentRow(i); i++)
        if (ui->city_line->completer()->currentCompletion() == ui->city_line->text()) {
            flagcity = true;
            break;
        }
    if (flagcity == false) {
        flag = false;
        ui->city_line->setStyleSheet("QLineEdit {\nborder: 1px solid red;\n}");
        ui->output->setText(ui->output->text() + '\n' + ui->city->text() + " \"" + ui->city_line->text() + "\" " + "not found");
    }

    bool flagaddress = false;
    for (int i = 0; ui->address_line->completer()->setCurrentRow(i); i++)
        if (ui->address_line->completer()->currentCompletion() == ui->address_line->text()) {
            flagaddress = true;
            break;
        }
    if (flagaddress == false) {
        flag = false;
        ui->address_line->setStyleSheet("QLineEdit {\nborder: 1px solid red;\n}");
        ui->output->setText(ui->output->text() + '\n' + ui->address->text() + " \"" + ui->address_line->text() + "\" " + "not found");
    }

    bool flaginstitute = false;
    for (int i = 0; ui->institute_line->completer()->setCurrentRow(i); i++)
        if (ui->institute_line->completer()->currentCompletion() == ui->institute_line->text()) {
            flaginstitute = true;
            break;
        }
    if (flaginstitute == false) {
        flag = false;
        ui->institute_line->setStyleSheet("QLineEdit {\nborder: 1px solid red;\n}");
        ui->output->setText(ui->output->text() + '\n' + ui->institute->text() + " \"" + ui->institute_line->text() + "\" " + "not found");
    }

    bool flagcafe = false;
    for (int i = 0; ui->cafe_line->completer()->setCurrentRow(i); i++)
        if (ui->cafe_line->completer()->currentCompletion() == ui->cafe_line->text()) {
            flagcafe = true;
            break;
        }
    if (flagcafe == false) {
        flag = false;
        ui->cafe_line->setStyleSheet("QLineEdit {\nborder: 1px solid red;\n}");
        ui->output->setText(ui->output->text() + '\n' + ui->cafe->text() + " \"" + ui->cafe_line->text() + "\" " + "not found");
    }

    bool flagcinema = false;
    for (int i = 0; ui->cinema_line->completer()->setCurrentRow(i); i++)
        if (ui->cinema_line->completer()->currentCompletion() == ui->cinema_line->text()) {
            flagcinema = true;
            break;
        }
    if (flagcinema == false) {
        flag = false;
        ui->cinema_line->setStyleSheet("QLineEdit {\nborder: 1px solid red;\n}");
        ui->output->setText(ui->output->text() + '\n' + ui->cinema->text() + " \"" + ui->cinema_line->text() + "\" " + "not found");
    }

    if (ui->spinBox_age->isEnabled()) {
        std::vector<unsigned int> v = _database->getAges();
        if (std::find(v.begin(), v.end(), ui->spinBox_age->value()) == v.end()) {
            flag = false;
            ui->spinBox_age->setStyleSheet("QSpinBox {\nborder: 1px solid red;\n}");
            ui->output->setText(ui->output->text() + '\n' + ui->age->text() + " \"" + ui->spinBox_age->text() + "\" " + "not found");
        }
    }

    return flag;

}

void MainWindow::on_calculate_clicked()
{
    ui->output->clear();
    if (begincheckLines()) {
        if (endcheckLines()) {
            if (ui->spinBox_age->isEnabled()) {
                _student->setAge(ui->spinBox_age->value());
            } else {
                _student->setAge(0);
            }
            _student->setCity(ui->city_line->text().toStdString());
            _student->setHomeAdress(ui->address_line->text().toStdString());
            _student->setInstitute(ui->institute_line->text().toStdString());
            unsigned int costs = _student->getCosts(ui->spinBox_month->value(), _student->getCity(), _student->getHomeAdress(), _student->getInstitute(), ui->cinema_line->text().toStdString(), ui->cafe_line->text().toStdString(), _student->getAge(), *_database);
            ui->output->setStyleSheet("QLabel { color: green; font-size: 25px;}");
            ui->output->setText("Student " + ui->name_line->text() + " spends " + QString::number(costs) + " rubles in month " + ui->spinBox_month->text());
        }
    } else {
        ui->output->setText("");
    }
}

void MainWindow::on_costs_clicked()
{
    if (_tableCosts == nullptr) {
        _tableCosts = new Table(QString::fromStdString(_database->getCosts()), _database->getcostsData(), this);
        connect(_tableCosts, &Table::applyButtonClicked, this, &MainWindow::onapplyButtonClicked);
    } else {
        _tableCosts->setTable(_database->getcostsData());
    }
//    connect(_tableCosts, &Table::dialogClosed, this, &MainWindow::onDialogClosed);
    _tableCosts->setModal(true);
    _tableCosts->exec();
}

void MainWindow::on_cafcin_clicked()
{
    if (_tableCafcin == nullptr) {
        _tableCafcin = new Table(QString::fromStdString(_database->getCafcin()), _database->getcafcinData(), this);
        connect(_tableCafcin, &Table::applyButtonClicked, this, &MainWindow::onapplyButtonClicked);
    } else {
        _tableCafcin->setTable(_database->getcafcinData());
    }
//    connect(_tableCafcin, &Table::dialogClosed, this, &MainWindow::onDialogClosed);
    _tableCafcin->setModal(true);
    _tableCafcin->exec();
}

void MainWindow::on_inst_clicked()
{
    if (_tableInst == nullptr) {
        _tableInst = new Table(QString::fromStdString(_database->getInst()), _database->getinstData(), this);
        connect(_tableInst, &Table::applyButtonClicked, this, &MainWindow::onapplyButtonClicked);
    } else {
        _tableInst->setTable(_database->getinstData());
    }
//    connect(_tableInst, &Table::dialogClosed, this, &MainWindow::onDialogClosed);
    _tableInst->setModal(true);
    _tableInst->exec();
}

void MainWindow::on_tr_clicked()
{
    if (_tableTr == nullptr) {
        _tableTr = new Table(QString::fromStdString(_database->getTr()), _database->gettrData(), this);
        connect(_tableTr, &Table::applyButtonClicked, this, &MainWindow::onapplyButtonClicked);
    } else {
        _tableTr->setTable(_database->gettrData());
    }
//    connect(_tableTr, &Table::dialogClosed, this, &MainWindow::onDialogClosed);
    _tableTr->setModal(true);
    _tableTr->exec();
}

void MainWindow::onapplyButtonClicked(const QString& filename) {
    qDebug() << filename;
    std::ofstream file(_database->getPath() + '/' + filename.toStdString());
    std::vector<std::vector<std::string>> v;
    if (filename.toStdString() == _database->getCosts()) {
        qDebug() << "OK1";
        v = _database->getcostsData();
    } else if (filename.toStdString() == _database->getTr()) {
        qDebug() << "OK2";
        v = _database->gettrData();
        setCompleter(_database->getCities(), ui->city_line);
        setCompleter(_database->getAddresses(), ui->address_line);
    } else if (filename.toStdString() == _database->getInst()) {
        qDebug() << "OK3";
        v = _database->getinstData();
        setCompleter(_database->getInstitutes(), ui->institute_line);
    } else if (filename.toStdString() == _database->getCafcin()) {
        qDebug() << "OK4";
        v = _database->getcafcinData();
        setCompleter(_database->getCafes(), ui->cafe_line);
        setCompleter(_database->getCinemas(), ui->cinema_line);
    } else {
        qDebug() << "BAD";
    }
    for (const auto& row : v) {
        for (const auto& value : row) {
            file << value << ",";
        }
        file << "\n";
    }
    file.close();
}

//void MainWindow::onDialogClosed(const QString& filename) {
//    std::vector<std::vector<std::string>> data = _database->getcostsData();
//    for (const auto& row : data) {
//            for (const auto& cell : row) {
//                qDebug() <<  QString::fromStdString(cell);
//            }
//    }
//    QFileInfo fileInfo(path);
//    QString fileName = fileInfo.fileName();
//    qDebug() << fileName;
//    std::vector<std::string> v;
//    QStringList qlist;
//    if (fileName.toStdString() == _database->getInst()) {
//        qlist.clear();
//        v = _database->getInstitutes();
//        for(auto elem: v) {
//            qlist.append(QString::fromStdString(elem));
//        }
//        delete ui->institute_line->completer();
//        QCompleter *completerInstitutes = new QCompleter(qlist, this);
//        completerInstitutes->setCaseSensitivity(Qt::CaseInsensitive);
//        ui->institute_line->setCompleter(completerInstitutes);
//    } else if (fileName.toStdString() == _database->getTr()) {
//        qlist.clear();
//        v = _database->getCities();
//        for(auto elem: v) {
//            qlist.append(QString::fromStdString(elem));
//        }
//        delete ui->city_line->completer();
//        QCompleter *completerCities = new QCompleter(qlist, this);
//        completerCities->setCaseSensitivity(Qt::CaseInsensitive);
//        ui->city_line->setCompleter(completerCities);

//        qlist.clear();
//        v = _database->getAddresses();
//        for(auto elem: v) {
//            qlist.append(QString::fromStdString(elem));
//        }
//        delete ui->address_line->completer();
//        QCompleter *completerAddresses = new QCompleter(qlist, this);
//        completerAddresses->setCaseSensitivity(Qt::CaseInsensitive);
//        ui->address_line->setCompleter(completerAddresses);
//    } else if (fileName.toStdString() == _database->getCafcin()) {
//        qlist.clear();
//        v = _database->getCafes();
//        for(auto elem: v) {
//            qlist.append(QString::fromStdString(elem));
//        }
//        delete ui->cafe_line->completer();
//        QCompleter *completerCafes = new QCompleter(qlist, this);
//        completerCafes->setCaseSensitivity(Qt::CaseInsensitive);
//        ui->cafe_line->setCompleter(completerCafes);

//        qlist.clear();
//        v = _database->getCinemas();
//        for(auto elem: v) {
//            qlist.append(QString::fromStdString(elem));
//        }
//        delete ui->cinema_line->completer();
//        QCompleter *completerCinemas = new QCompleter(qlist, this);
//        completerCinemas->setCaseSensitivity(Qt::CaseInsensitive);
//        ui->cinema_line->setCompleter(completerCinemas);
//    }
//}
