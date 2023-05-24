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
    explicit Table(const QString& path, QWidget *parent = nullptr);
    ~Table();
signals:
    void dialogClosed(const QString& path);
protected:
    void closeEvent(QCloseEvent* event) override;
private slots:
    void on_pushButton_clicked();

private:
    Ui::table *ui;
    QStandardItemModel *_table;
    const QString _path;
};

#endif // TABLE_H
