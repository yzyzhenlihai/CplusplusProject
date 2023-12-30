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
        m_client->write("success");
        connect(m_client, &QTcpSocket::readyRead, this, &MainWindow::readyRead);
        connect(m_client, &QTcpSocket::disconnected, this, &MainWindow::clientDisconnected);
    }
}


void MainWindow::readyRead(){
    QByteArray array = m_client->readAll();

    int passwordSeparatorIndex = QString::fromUtf8(array).indexOf(' '); // 查找密码分隔符的位置
    if (passwordSeparatorIndex != -1) { // 如果找到了分隔符
        QString id = QString::fromUtf8(array.left(passwordSeparatorIndex)); // 使用分隔符位置来分割id
        QString password = QString::fromUtf8(array.mid(passwordSeparatorIndex + 1)); // 使用分隔符位置来分割password
        if (connectdatabase("dormitory_manage_system.db")) {
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
    } else {
        // 如果没有找到密码分隔符，处理错误情况
        m_client->write("invalid"); // 向客户端发送"invalid"表示登录失败
    }
    m_client->disconnectFromHost();  // 断开客户端连接
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
