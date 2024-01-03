#ifndef DORMITORY_INFO_ADMIN_H
#define DORMITORY_INFO_ADMIN_H

#include <QMainWindow>
#include<QtSql/QSqlDatabase>
#include<QDebug>
#include <QSqlRecord>
#include<QMessageBox>
#include<QSqlError>
#include<QSqlTableModel>
#include"mybutton.h"
#include<QVector>
namespace Ui {
class Dormitory_Info_Admin;
}

class Dormitory_Info_Admin : public QMainWindow
{
    Q_OBJECT

public:
    explicit Dormitory_Info_Admin(QWidget *parent = nullptr);
    ~Dormitory_Info_Admin();
    bool connectDatabase(const QString &dbName);
    void initButton();//为每一条记录创建一个按钮
    void addButton();
    void delButtons();

private slots:
    void on_ShowAllBtn_clicked();

    void on_ReturnBtn_clicked();

    void on_QueryBtn_clicked();

private:
    Ui::Dormitory_Info_Admin *ui;
    QSqlTableModel *model;
    QVector<Mybutton*> buttons;
};

#endif // DORMITORY_INFO_ADMIN_H
