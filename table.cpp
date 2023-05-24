#include "table.h"
#include "ui_table.h"
#include <QDebug>

Table::Table(const QString& path, QWidget *parent) :
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
}

Table::~Table()
{
    delete ui;
}

void Table::closeEvent(QCloseEvent* event) {
    QDialog::closeEvent(event);
    emit dialogClosed(_path);
}

void Table::on_pushButton_clicked()
{
    ui->label->setText("");
    QString textData;
    QString line;
    qDebug() << "ok";
    qDebug() << _table->rowCount();
    qDebug() << _table->columnCount();
    for (int i = 0; i < _table->rowCount(); i++) {
        line = "";
        for (int j = 0; j < _table->columnCount(); j++) {
            if (!_table->data(_table->index(i,j)).isNull()) {
                line += _table->data(_table->index(i,j)).toString();
                line += ",";
            }
        }
        while (line != "" && line.back() == ',') {
            line.chop(1);
        }
        if (line != "") {
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
