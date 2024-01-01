#ifndef STUDENTVIEW_H
#define STUDENTVIEW_H

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
namespace Ui { class StudentView; }
QT_END_NAMESPACE

class StudentView : public QWidget
{
    Q_OBJECT

public:
    StudentView(QWidget *parent = nullptr);
    ~StudentView();
    //bool connectdatabase(const QString &dbName);

private:
    Ui::StudentView *ui;
    QSqlTableModel *model;

    QTcpSocket* server;
private slots:
    void on_ReturnwinBtn_clicked();

public slots:
    void slotReadyRead();
   void slotSendInfo();
    void slotSendPass();




};


#endif // STUDENTVIEW_H
