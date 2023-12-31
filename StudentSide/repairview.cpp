#include "repairview.h"
#include "ui_repairview.h"
#include "studentwindow.h"
#include "studentlogin.h"
#include <QSqlTableModel>
#include <QTableView>
#include<QtSql/QSqlDatabase>
#include<QDebug>
#include<QMessageBox>
#include <QtSql>
#include <QHostAddress>
#include<QMessageBox>
#include <QStandardItemModel>  // 包含QStandardItemModel的头文件
#include <QStringList>
#include <QStandardItem>
RepairView::RepairView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RepairView)
{
    ui->setupUi(this);
    server = new QTcpSocket(this);
    server->connectToHost(QHostAddress("127.0.0.1"),8000);
    connect(server ,&QTcpSocket::readyRead,this,&RepairView::slotReadyRead);
    connect(ui->DornumviewBtn,&QPushButton::clicked,this,&RepairView::slotSendNumView);
}


RepairView::~RepairView()
{
    delete ui;
}

void RepairView::slotSendNumView(){

    QString dornum = ui->DorNumLineEdit->text();
    QString data = "DOR:" + dornum ;

    server->write(data.toUtf8());



}
void RepairView::slotReadyRead(){
    QByteArray array = server->readAll();
    qDebug() << array;
    QString result = QString::fromUtf8(array);
    if (result == "No records found") {
        QMessageBox::critical(this, "Query Failed", "No records found for the specified query.");
        return;
    }
    // 处理来自服务端的查询结果
    // 将结果显示在QTableView上
    QStandardItemModel *model = new QStandardItemModel();
    QStringList headers = {"Num", "Phone", "Fault"};
    model->setHorizontalHeaderLabels(headers);

    QStringList records = result.split("$");
    model->removeRows(0, model->rowCount()); // 清除之前的数据
    int row = 0;
    foreach (const QString &record, records) {
        QStringList fields = record.split(",");
        if (fields.size() == 3) {
            for (int column = 0; column < 3; ++column) {
                model->setItem(row, column, new QStandardItem(fields.at(column)));
            }
            row++;
        }
    }

    // 将model设置给QTableView
    ui->tableView->setModel(model);
}

void RepairView::on_ReturnwinBtn_clicked()
{
    StudentWindow *windowwin=new StudentWindow;
    windowwin->show();
    delete this;
}
