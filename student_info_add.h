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
#include<QFileDialog>
#include<QBuffer>
namespace Ui {
class Student_Info_Add;
}

class Student_Info_Add : public QMainWindow
{
    Q_OBJECT

public:
    explicit Student_Info_Add(QWidget *parent = nullptr);
    ~Student_Info_Add();
    bool connectDatabase(const QString &dbName);

private slots:
    void on_returnBtn_clicked();

    void on_addCommit_clicked();
    void receive_add_info(QString);//收到添加个人信息的槽
    void on_addPictureBtn_clicked();
    void receivePicture(QByteArray);//接受图片字符串

signals:
    //定义消息
    void sendRecord(QSqlRecord* record);//子窗口发送要添加的记录给主窗口
    void sendPicture(QByteArray);//发送图片字符串

private:
    Ui::Student_Info_Add *ui;
    QSqlTableModel *model;
    QString returnWay;
};

#endif // STUDENT_INFO_ADD_H
