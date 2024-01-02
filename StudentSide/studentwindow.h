#ifndef STUDENTWINDOW_H
#define STUDENTWINDOW_H
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

#include <QMainWindow>

namespace Ui {
class StudentWindow;
}

class StudentWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StudentWindow(QWidget *parent = nullptr);
    ~StudentWindow();

private slots:


    void on_ReturnLoginBtn_clicked();//返回

    void on_RepairBtn_clicked();//报修

    void on_RepairInfoBtn_clicked();//报修查看
    void on_ViewInfoBtn_clicked();//个人信息

private:
    Ui::StudentWindow *ui;

    QSqlTableModel *model;



};



#endif // STUDENTWINDOW_H
