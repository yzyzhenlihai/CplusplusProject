#include "studentlogin.h"
#include "ui_studentlogin.h"
#include "studentwindow.h"
#include <QSqlTableModel>
#include<QtSql/QSqlDatabase>
#include<QDebug>
#include<QMessageBox>
#include <QtSql>
#include <QHostAddress>
#include<QMessageBox>
StudentLogin::StudentLogin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StudentLogin)
{
    ui->setupUi(this);
    server = new QTcpSocket(this);
    server->connectToHost(QHostAddress("127.0.0.1"),8000);
    connect(server ,&QTcpSocket::readyRead,this,&StudentLogin::slotReadyRead);
    connect(ui->LoginButton,&QPushButton::clicked,this,&StudentLogin::slotSendId);

}


StudentLogin::~StudentLogin()
{
    delete ui;
}

void StudentLogin::slotReadyRead(){
    QByteArray array = server->readAll();

    qDebug()<<array;
    if (array == "ok"){
            StudentWindow *stuwin=new StudentWindow;
            stuwin->show();
            this->close();
        }
    else if (array =="invalid"){
        StudentLogin *stulogwin=new StudentLogin;
        stulogwin->show();
        this->close();
    }
}
void StudentLogin::slotSendId(){
    QString id = ui->UserNameLineEdit->text();
    QString password = ui->PasswordLineEdit->text();

    QString data = "ID:" + id + " " + password ;
    server->write(data.toUtf8());

    ui->UserNameLineEdit->clear();
    ui->PasswordLineEdit->clear();
}

