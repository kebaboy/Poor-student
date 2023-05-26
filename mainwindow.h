#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "table.h"
#include "Student.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(DatabaseHandler* database, Student* student, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_directory_clicked();

    void on_radioButton_clicked();

    void allclear();

    void enableUI();

    void setCompleter(const std::vector<std::string>& v, QLineEdit* line);

    void on_clear_clicked();

    void on_calculate_clicked();

    bool begincheckLines();

    bool endcheckLines();

    void on_costs_clicked();

    void on_cafcin_clicked();

    void on_inst_clicked();

    void on_tr_clicked();
public slots:
//    void onDialogClosed(const QString& path);
    void onapplyButtonClicked(const QString& path);
private:
    Ui::MainWindow *ui;
    DatabaseHandler* _database;
    Student* _student;
    Table* _tableCafcin = nullptr;
    Table* _tableInst = nullptr;
    Table* _tableTr = nullptr;
    Table* _tableCosts = nullptr;
};
#endif // MAINWINDOW_H
