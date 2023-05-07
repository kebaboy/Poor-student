#ifndef TABLE_H
#define TABLE_H

#include <QDialog>
#include <QStandardItemModel>
#include <QFile>
#include <QTextStream>

namespace Ui {
class table;
}

class table : public QDialog
{
    Q_OBJECT

public:
    explicit table(const QString& path, QWidget *parent = nullptr);
    ~table();   

private slots:
    void on_pushButton_clicked();

private:
    Ui::table *ui;
    QStandardItemModel *_table;
    const QString _path;
};

#endif // TABLE_H
