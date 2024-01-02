#ifndef REPAIRVIEW_H
#define REPAIRVIEW_H
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
namespace Ui { class RepairView; }
QT_END_NAMESPACE

class RepairView : public QWidget
{
    Q_OBJECT

public:
    RepairView(QWidget *parent = nullptr);
    ~RepairView();


private:
    Ui::RepairView *ui;
    QSqlTableModel *model;

    QTcpSocket* server;
private slots:
        void on_ReturnwinBtn_clicked();//返回

public slots:
    void slotReadyRead();//读服务端数据
    void slotSendNumView();//发送数据

};
#endif // REPAIRVIEW_H
