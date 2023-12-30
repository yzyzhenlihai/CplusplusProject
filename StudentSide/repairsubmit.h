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
    bool connectdatabase(const QString &dbName);

private slots:
    //void on_pushButton_4_clicked();

    void on_WindowBtn_clicked();

    void on_SubmitBtn_clicked();

    void slotReadyRead();
    void slotSendNum();
    void slotSendPhone();
    void slotSendFault();
    // void on_RepairInfoBtn_clicked();
private:
    Ui::RepairSubmit *ui;
    QSqlTableModel *model;
     QTcpSocket* server;
};






#endif // REPAIRSUBMIT_H
