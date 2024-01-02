#include "studentview.h"
#include "studentwindow.h"
#include "ui_studentview.h"
#include <QSqlTableModel>
#include<QtSql/QSqlDatabase>
#include<QDebug>
#include<QMessageBox>
#include <QtSql>
StudentView::StudentView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StudentView)
{
    ui->setupUi(this);
    server = new QTcpSocket(this);
    server->connectToHost(QHostAddress("127.0.0.1"),8000);
    connect(server ,&QTcpSocket::readyRead,this,&StudentView::slotReadyRead);
    connect(ui->StuInfoBtn,&QPushButton::clicked,this,&StudentView::slotSendInfo);//请求查看信息
    connect(ui->PasswordBtn,&QPushButton::clicked,this,&StudentView::slotSendPass);//修改密码

}

StudentView::~StudentView()
{
    delete ui;
}





void StudentView::on_ReturnwinBtn_clicked()
{
    StudentWindow *windowwin=new StudentWindow;
    windowwin->show();
    delete this;
}


void StudentView::slotReadyRead(){
    QByteArray array = server->readAll();
    qDebug()<<array;
    if (array.startsWith("ID:")){//查看信息
        qDebug()<<array;
        QMessageBox::information(this,"information",array);
    }
    else if(array=="passwordsuccess"){//修改成功
        QString dlgTitle="success";
        QString strInfo="修改成功!";
        QMessageBox::information(this,dlgTitle,strInfo);
    }
    else if (array =="passwordfail"){
        QString dlgTitle="error";
        QString strInfo="修改失败!";
        QMessageBox::critical(this,dlgTitle,strInfo);
    }

}

void StudentView::slotSendPass(){
    QString password = ui->PasswordlineEdit->text();
    if(ui->PasswordlineEdit->text()!=""){
        QString password = ui->PasswordlineEdit->text();
        QString data = "PASS:" + password;
        server->write(data.toUtf8());

        ui->PasswordlineEdit->clear();
    }
    else{
        QString dlgTitle="error";
        QString strInfo="请输入密码!";
        QMessageBox::critical(this,dlgTitle,strInfo);   
    }
}

void StudentView::slotSendInfo(){

    QString data = "Infoview" ;
    server->write(data.toUtf8());

}

