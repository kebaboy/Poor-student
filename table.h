#ifndef TABLE_H
#define TABLE_H

#include <QDialog>
#include <QStandardItemModel>
#include <QFile>
#include <QTextStream>

namespace Ui {
class table;
}

class Table : public QDialog
{
    Q_OBJECT

public:
    explicit Table(const QString& filename, std::vector<std::vector<std::string>>& data, QWidget *parent);
    ~Table();
signals:
//    void dialogClosed(const QString& filename);
    void applyButtonClicked(const QString& filename);
//protected:
//    void closeEvent(QCloseEvent* event) override;
private slots:
    void on_applyButton_clicked();
    void on_addButton_clicked();

    void on_deleteButton_clicked();

public slots:
    void setTable(const std::vector<std::vector<std::string>>& data);
private:
    Ui::table *ui;
    const QString _filename;
    std::vector<std::vector<std::string>>* _data;
};

#endif // TABLE_H
