#include "repairsubmit.h"
#include "studentwindow.h"
#include "ui_repairsubmit.h"
#include <QSqlTableModel>
#include<QtSql/QSqlDatabase>
#include<QDebug>
#include<QMessageBox>
#include <QtSql>
RepairSubmit::RepairSubmit(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RepairSubmit)
{
    ui->setupUi(this);
    server = new QTcpSocket(this);
    server->connectToHost(QHostAddress("127.0.0.1"),8000);
    connect(server ,&QTcpSocket::readyRead,this,&RepairSubmit::slotReadyRead);
    connect(ui->SubmitBtn,&QPushButton::clicked,this,&RepairSubmit::slotSendNum);
   // connect(ui->SubmitBtn,&QPushButton::clicked,this,&RepairSubmit::slotSendPhone);
    //connect(ui->SubmitBtn,&QPushButton::clicked,this,&RepairSubmit::slotSendFault);
}

RepairSubmit::~RepairSubmit()
{
    delete ui;
}





void RepairSubmit::on_WindowBtn_clicked()
{
    StudentWindow *windowwin=new StudentWindow;
    windowwin->show();
    delete this;
}


void RepairSubmit::slotReadyRead(){
    QByteArray array = server->readAll();
    qDebug()<<array;
    if (array == "insertsuccess"){
        QString dlgTitle="success";
        QString strInfo="提交成功!";
        QMessageBox::information(this,dlgTitle,strInfo);
        StudentWindow *stuwin=new StudentWindow;
        stuwin->show();
        this->close();
    }
    else if (array =="invalid"){
        QString dlgTitle="error";
        QString strInfo="提交失败!";
        QMessageBox::critical(this,dlgTitle,strInfo);
        RepairSubmit *stulogwin=new RepairSubmit;
        stulogwin->show();
        this->close();
    }
}

void RepairSubmit::slotSendNum(){
    QString num = ui->RepairNum->text();
    QString phone = ui->Repairphone->text();
    QString fault = ui->RepairFault->text();
    if(num!="" &&phone != "" && fault!=""){

    QString data = "NUM:" + num + " " + phone + " " + fault; // 在数据前面添加"NUM:"作为数据类型标识
    server->write(data.toUtf8());

    ui->RepairNum->clear();
    ui->Repairphone->clear();
    ui->RepairFault->clear();
    }
    else{
        QString dlgTitle="error";
        QString strInfo="请输入完整信息!";
        QMessageBox::critical(this,dlgTitle,strInfo);
    }
}
