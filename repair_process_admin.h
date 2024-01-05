#ifndef REPAIR_PROCESS_ADMIN_H
#define REPAIR_PROCESS_ADMIN_H

#include <QMainWindow>
#include<QSqlTableModel>
#include<QSqlDatabase>
#include <QSqlRecord>
#include<QMessageBox>
#include<administratorwindow.h>
namespace Ui {
class Repair_Process_Admin;
}

class Repair_Process_Admin : public QMainWindow
{
    Q_OBJECT

public:
    explicit Repair_Process_Admin(QWidget *parent = nullptr);
    ~Repair_Process_Admin();
    bool connectDatabase(const QString& dbName);

private slots:
    void on_ReturnBtn_clicked();

    void on_ShowRepairBtn_clicked();

private:
    Ui::Repair_Process_Admin *ui;
    QSqlTableModel* model;
};

#endif // REPAIR_PROCESS_ADMIN_H
