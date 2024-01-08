#ifndef REPAIR_PROCESS_ADMIN_H
#define REPAIR_PROCESS_ADMIN_H

#include <QMainWindow>
#include<QSqlQuery>
#include<QSqlTableModel>
#include<QSqlDatabase>
#include <QSqlRecord>
#include<QMessageBox>
#include<administratorwindow.h>
#include"mybutton.h"
#include<QVector>
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
    void initButton();//为每一条记录创建一个按钮
    void delButtons();//析构按钮


private slots:
    void on_ReturnBtn_clicked();

    void on_ShowRepairBtn_clicked();
    void on_InquireRepairBtn_clicked();
    void clickButton();//槽函数，处理报修按钮

private:
    Ui::Repair_Process_Admin *ui;
    QSqlTableModel* model;
    QVector<Mybutton*> buttons;
};

#endif // REPAIR_PROCESS_ADMIN_H
