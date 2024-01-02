#ifndef STUDENT_INFO_ADD_H
#define STUDENT_INFO_ADD_H
#include <QSqlRecord>
#include <QMainWindow>
#include "student_info_query.h"
#include<QtSql/QSqlDatabase>
#include<QDebug>
#include <QSqlRecord>
#include<QMessageBox>
#include<QSqlError>
namespace Ui {
class Student_Info_Add;
}

class Student_Info_Add : public QMainWindow
{
    Q_OBJECT

public:
    explicit Student_Info_Add(QWidget *parent = nullptr);
    ~Student_Info_Add();
    bool connect(const QString &dbName);

private slots:
    void on_returnBtn_clicked();

    void on_addCommit_clicked();
signals:
    //定义消息
    void sendRecord(QSqlRecord* record);//子窗口发送要添加的记录给主窗口

private:
    Ui::Student_Info_Add *ui;
    QSqlTableModel *model;
};

#endif // STUDENT_INFO_ADD_H
