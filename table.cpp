#include "table.h"
#include "ui_table.h"
#include <set>
#include <QDebug>

Table::Table(const QString& filename, std::vector<std::vector<std::string>>& data, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::table),
    _filename(filename),
    _data(&data)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);
    setTable(data);
}

Table::~Table()
{
    delete ui;
}

//void Table::closeEvent(QCloseEvent* event) {
//    QDialog::closeEvent(event);
//    emit dialogClosed(_filename);
//}

void Table::on_applyButton_clicked()
{
    ui->label->setText("");
    QTableWidget* tableWidget = this->findChild<QTableWidget*>("tableWidget");
    _data->resize(tableWidget->rowCount());
        for (int row = 0; row < tableWidget->rowCount(); ++row) {
            (*_data)[row].resize(tableWidget->columnCount());
            for (int col = 0; col < tableWidget->columnCount(); ++col) {
                QTableWidgetItem* item = tableWidget->item(row, col);
                if (item) {
                    (*_data)[row][col] = item->text().toStdString();
                }
            }
        }
    emit applyButtonClicked(_filename);

    ui->label->setText("Changes successfully saved");
}

void Table::setTable(const std::vector<std::vector<std::string>>& data) {
    QTableWidget* tableWidget = this->findChild<QTableWidget*>("tableWidget");
    tableWidget->setRowCount(data.size());
    tableWidget->setColumnCount(data[0].size());
    for (int row = 0; row < tableWidget->rowCount(); ++row) {
        for (int col = 0; col < tableWidget->columnCount(); ++col) {
            // Преобразуем std::string в QString и устанавливаем в ячейку таблицы
            QString cellData = QString::fromStdString(data[row][col]);
            tableWidget->setItem(row, col, new QTableWidgetItem(cellData));
        }
    }
}

void Table::on_addButton_clicked()
{
    QTableWidget* tableWidget = this->findChild<QTableWidget*>("tableWidget");
    tableWidget->insertRow(tableWidget->rowCount());
}

void Table::on_deleteButton_clicked()
{
    QTableWidget* tableWidget = this->findChild<QTableWidget*>("tableWidget");
    QItemSelectionModel* selectionModel = tableWidget->selectionModel();
    QModelIndexList selectedRows = selectionModel->selectedRows();
    if (!selectedRows.isEmpty()) {
        std::set<int> rowsToDelete;
        for (const QModelIndex& index : selectedRows) {
                rowsToDelete.insert(index.row());
        }
            // Удаляем строки в обратном порядке, чтобы не нарушить индексы
        for (auto it = rowsToDelete.rbegin(); it != rowsToDelete.rend(); ++it) {
            int row = *it;
            tableWidget->removeRow(row);
        }
    } else if (tableWidget->rowCount() > 0) {
        tableWidget->removeRow(tableWidget->rowCount() - 1);
    }
}
