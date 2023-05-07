#include "table.h"
#include "ui_table.h"
#include <QDebug>

table::table(const QString& path, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::table),
    _path(path)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);
    _table = new QStandardItemModel(this);
    ui->tableView->setModel(_table);
    QFile file(_path);
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream in(&file);
    while (!in.atEnd()) {
        // ... построчно
        QString line = in.readLine();
        // Добавляем в модель по строке с элементами
        QList<QStandardItem *> standardItemsList;
        // учитываем, что строка разделяется точкой с запятой на колонки
        for (QString item : line.split(",")) {
            standardItemsList.append(new QStandardItem(item));
        }
        _table->insertRow(_table->rowCount(), standardItemsList);
    }
    file.close();
    _table->setColumnCount(100);
    _table->setRowCount(100);

//    for(int row=0; row!=_tableWidget->rowCount(); ++row){
//        for(int column=0; column!=_tableWidget->columnCount(); ++column) {
//            QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg((row+1)*(column+1)));
//            _tableWidget->setItem(row, column, newItem);
//        }
//    }
}

table::~table()
{
    delete ui;
}

void table::on_pushButton_clicked()
{
    ui->label->setText("");
    QString textData;
    QString line;
    for (int i = 0; i < _table->rowCount(); i++) {
        line = "";
        for (int j = 0; j < _table->columnCount(); j++) {
            if (!_table->data(_table->index(i,j)).isNull()) {
                line += _table->data(_table->index(i,j)).toString();
                line += ",";    // for .csv file format
            }
        }
        if (line != "") {
            while (line.back() == ',') {
                line.chop(1);
            }
            line += '\n';
            textData += line;
        }
    }

    QFile csvFile(_path);
    csvFile.open(QFile::WriteOnly | QFile::Truncate);
    QTextStream out(&csvFile);
    out << textData;
    csvFile.close();
    ui->label->setText("Changes successfully saved");
}