#ifndef REPAIRSUBMIT_H
#define REPAIRSUBMIT_H
#include <QWidget>
#include <QDialog>
#include <QMainWindow>
#include <QPushButton>
#include<QMessageBox>
#include <QSqlTableModel>
#include<QtSql/QSqlDatabase>
#include<QDebug>
#include <QMainWindow>
#include <QTcpSocket>
#include <QByteArray>
namespace Ui {
class RepairSubmit;
}

class RepairSubmit : public QMainWindow
{
    Q_OBJECT

public:
    explicit RepairSubmit(QWidget *parent = nullptr);
    ~RepairSubmit();
    bool connectdatabase(const QString &dbName);//连接数据库

private slots:

    void on_WindowBtn_clicked();//返回


    void slotReadyRead();//读服务端来的数据
    void slotSendNum();//发送信息

private:
    Ui::RepairSubmit *ui;
    QSqlTableModel *model;
    QTcpSocket* server;
};






#endif // REPAIRSUBMIT_H
