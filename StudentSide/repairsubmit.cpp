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
    //connect(ui->LoginButton,&QPushButton::clicked,this,&RepairSubmit::slotSendId);
    //connect(ui->LoginButton,&QPushButton::clicked,this,&RepairSubmit::slotSendPassword);
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


void RepairSubmit::on_SubmitBtn_clicked()
{
        QString Renum=ui->RepairNum->text();
        QString Rephone=ui->Repairphone->text();
        QString Refault=ui->RepairFault->text();

        //if(this->connect("dormitory_manage_system.db")){//连接数据库
            model=new QSqlTableModel(this);
            model->setTable("repairinfo");
            model->setEditStrategy(QSqlTableModel::OnManualSubmit);//默认手动提交
        if(Renum!="" &&Rephone != "" && Refault!=""){
            QString sql = "INSERT INTO repairinfo VALUES (?,?,?)";
            QSqlQuery query;
            query.prepare(sql);
            query.bindValue(0, Renum);
            query.bindValue(1, Rephone);
            query.bindValue(2, Refault);

            if (!query.exec()) {
                QString dlgTitle="error";
                QString strInfo="Incorrect account or password!";
                QMessageBox::critical(this,dlgTitle,strInfo);
                qDebug() << "Failed to execute query";

            }
            else{
                QString dlgTitle="success";
                QString strInfo="提交成功!";
                QMessageBox::information(this,dlgTitle,strInfo);
            }
        }
        else{
            QString dlgTitle="error";
            QString strInfo="请输入完整信息!";
            QMessageBox::critical(this,dlgTitle,strInfo);
        }


        //}
}

void RepairSubmit::slotReadyRead(){
    QByteArray array = server->readAll();
    qDebug()<<array;
    if (array == "ok"){
        StudentWindow *stuwin=new StudentWindow;
        stuwin->show();
        this->close();
    }
    else if (array =="invalid"){
        RepairSubmit *stulogwin=new RepairSubmit;
        stulogwin->show();
        this->close();
    }
}

void RepairSubmit::slotSendNum(){
    QString id = ui->RepairNum->text();
    id.append(" "); // 在id后面添加一个空格

    server->write(id.toUtf8());

    ui->RepairNum->clear();
}

void RepairSubmit::slotSendPhone(){

    QString password = ui->Repairphone->text();

    server->write(password.toUtf8());
    ui->Repairphone->clear();
}
void RepairSubmit::slotSendFault(){

    QString password = ui->RepairFault->text();

    server->write(password.toUtf8());
    ui->RepairFault->clear();
}

