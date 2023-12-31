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
   //bool connectdatabase(const QString &dbName);

private:
    Ui::RepairView *ui;
    QSqlTableModel *model;

    QTcpSocket* server;
private slots:
           void on_ReturnwinBtn_clicked();

public slots:
    void slotReadyRead();
    void slotSendNumView();




};
#endif // REPAIRVIEW_H
