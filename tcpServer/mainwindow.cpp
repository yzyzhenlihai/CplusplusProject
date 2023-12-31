#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlTableModel>
#include<QtSql/QSqlDatabase>
#include<QDebug>
#include<QMessageBox>
#include <QtSql>
#include <QHostAddress>
#include<QMessageBox>
#include <QByteArray>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    m_server(NULL),
    m_client(NULL)

{
    ui->setupUi(this);
    m_server = new QTcpServer(this);
    m_server -> listen(QHostAddress::Any,8000);
    connect(m_server,&QTcpServer::newConnection,this,&MainWindow::newConnection);

}

void MainWindow::newConnection()
{
    if(m_client == NULL){
        m_client= m_server->nextPendingConnection();
        connect(m_client, &QTcpSocket::readyRead, this, &MainWindow::readyRead);
        connect(m_client, &QTcpSocket::disconnected, this, &MainWindow::clientDisconnected);
    }
}


void MainWindow::readyRead(){

    if (m_client == NULL) {
        return;
    }
    QString tmp;
    QByteArray array = m_client->readAll();
    qDebug()<<array<<array;
    // 检查接收到的数据类型
    if (array.startsWith("ID:")) {
        // 处理学生登录信息
        QString data = QString::fromUtf8(array);
        QString data1 = data.mid(3);
        QStringList dataList = data1.split(" ");
        QString id = dataList[0];
        tmp =id;
        QString password = dataList[1];
        // 处理id的逻辑
        if (connectdatabase("dormitory_manage_system.db")) {
            qDebug() << "Received id: " << id;
            qDebug() << "Received password: " << password;
            QSqlTableModel model;
            model.setTable("studentinfo");
            model.setFilter(QString("id = '%1' AND password = '%2'").arg(id).arg(password));
            model.select();
            if (model.rowCount() > 0) {
                m_client->write("ok"); // 向客户端发送"ok"表示成功登录
                // 添加处理成功登录的代码，比如打开学生窗口
                qDebug()<<id;
            } else {
                m_client->write("invalid"); // 向客户端发送"invalid"表示登录失败
            }
        }
        //m_client->write("ID received"); // 向客户端发送确认消息
        m_client->disconnectFromHost();
    } else if (array.startsWith("NUM:")) {
        // 处理维修提交信息
        QString data = QString::fromUtf8(array);
        QString data1 = data.mid(4);
        QStringList dataList = data1.split(" ");
        QString num = dataList[0]; // 第一个空格后面是维修编号
        QString phone = dataList[1]; // 第二个空格后面是电话号码
        QString fault = dataList[2]; // 第三个空格后面是故障描述
        // 处理num、phone、fault的逻辑
        if (connectdatabase("dormitory_manage_system.db")) {
            QSqlTableModel model(this);
            model.setTable("repairinfo");
            model.setEditStrategy(QSqlTableModel::OnManualSubmit);

            // 插入新记录
            QSqlRecord record = model.record(); // 创建一个空记录
            record.setValue("num", num); // 设置num字段的值
            record.setValue("phone", phone); // 设置phone字段的值
            record.setValue("fault", fault); // 设置fault字段的值
            if (model.insertRecord(-1, record)) { // 在最后插入记录
                if (model.submitAll()) {
                    // 插入成功
                   m_client->write("insertsuccess");
                } else {
                    // 提交失败
                   m_client->write("invalid");
                }
            } else {
                m_client->write("invalid");
            }

        }

        qDebug() << "Received num: " << num;
        qDebug() << "Received phone: " << phone;
        qDebug() << "Received fault: " << fault;
        //m_client->write("NUM received"); // 向客户端发送确认消息
        m_client->disconnectFromHost();
    }
    else if (array.startsWith("DOR:")) {
        // 处理维修提交信息
        QString data = QString::fromUtf8(array);
        QString dornum = data.mid(4);

        // 处理num、phone、fault的逻辑
        if (connectdatabase("dormitory_manage_system.db")) {
            QSqlTableModel model(this);
            model.setTable("repairinfo");
            model.setFilter("num = '" + dornum + "'");
            model.select();

            // 构建要发送给客户端的查询结果
            QString resultData;
            if (model.rowCount() > 0) {
                for (int i = 0; i < model.rowCount(); ++i) {
                    QSqlRecord record = model.record(i);
                    QString num = record.value("num").toString();
                    QString phone = record.value("phone").toString();
                    QString fault = record.value("fault").toString();
                    // 将查询结果拼接为字符串
                    resultData +=  num + "," + phone + "," + fault + "$";
                }
            } else {
                resultData = "No records found" ;
            }

            // 将查询结果发送回客户端
            m_client->write(resultData.toUtf8());
        }

    }

    else if (array=="Infoview"){
        qDebug()<<tmp<<"qqq";
        if (connectdatabase("dormitory_manage_system.db")) {

            QSqlTableModel model;
            model.setTable("studentinfo");
            model.setFilter(QString("id = '%1'").arg(tmp));
            model.select();
            QString resultData;
            if (model.rowCount() > 0) {
                for (int i = 0; i < model.rowCount(); ++i) {
                    QSqlRecord record = model.record(i);
                    QString id = record.value("id").toString();
                    QString password = record.value("password").toString();

                    // 将查询结果拼接为字符串
                    resultData +=  id + "," + password ;
                    qDebug()<<resultData;
                }
            }
            // 将查询结果发送回客户端
            m_client->write(resultData.toUtf8());
        }
         m_client->disconnectFromHost();
    }

    else {
        // 如果接收到未知类型的数据
        m_client->write("invalid"); // 向客户端发送无效消息
    }

   // m_client->disconnectFromHost();  // 断开客户端连接
}


void MainWindow::clientDisconnected()
{
    m_client->deleteLater();  // 清理断开连接的客户端对象
    m_client = NULL;  // 重置客户端指针
}


bool MainWindow::connectdatabase(const QString& dbName){
    qDebug() << QSqlDatabase::drivers();//打印数据库驱动
    //打开Mysql
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);
    bool ok=db.open();
    return ok;

}



MainWindow::~MainWindow()
{
    delete ui;
}
