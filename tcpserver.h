#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
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
#include<QSqlRecord>
#include<QVector>
namespace Ui {
class TcpServer;
}

class TcpServer : public QMainWindow
{
    Q_OBJECT

public:
    explicit TcpServer(QWidget *parent = nullptr);
    ~TcpServer();
    bool connectdatabase(const QString &dbName);
public slots:
    void newConnection();//建立TCP连接
    void readyRead();//读取客户端数据
    void clientDisconnected();//断开连接
private:
    Ui::TcpServer *ui;
    QTcpServer* m_server;//服务端
    //QTcpSocket* m_client;//与客户端数据传输，用于通信
    QSqlTableModel *model;
    //QString m_receivedId;//保存id
    QLabel* m_imageLabel;  // 用于显示图片的QLabel
    QVector<QTcpSocket*> m_clients;//用来存每个客户端发起请求的socket
};

#endif // TCPSERVER_H
