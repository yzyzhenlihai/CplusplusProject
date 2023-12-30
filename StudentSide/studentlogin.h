#ifndef STUDENTLOGIN_H
#define STUDENTLOGIN_H

#include <QWidget>
#include <QDialog>
#include <QMainWindow>
#include <QPushButton>
#include<QMessageBox>
#include <QSqlTableModel>
#include<QtSql/QSqlDatabase>
#include<QDebug>
#include <QTcpSocket>
#include <QByteArray>
QT_BEGIN_NAMESPACE
namespace Ui { class StudentLogin; }
QT_END_NAMESPACE

class StudentLogin : public QWidget
{
    Q_OBJECT

public:
    StudentLogin(QWidget *parent = nullptr);
    ~StudentLogin();
    //bool connect(const QString &dbName);

private:
    Ui::StudentLogin *ui;
    QSqlTableModel *model;

    QTcpSocket* server;


public slots:
    void slotReadyRead();
    void slotSendId();
    void slotSendPassword();



};
#endif // STUDENTLOGIN_H
