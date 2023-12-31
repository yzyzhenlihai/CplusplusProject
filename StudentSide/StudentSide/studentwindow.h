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
    //void on_pushButton_4_clicked();

    void on_ReturnLoginBtn_clicked();

    void on_RepairBtn_clicked();

    void on_RepairInfoBtn_clicked();
    void on_ViewInfoBtn_clicked();

private:
    Ui::StudentWindow *ui;

    QSqlTableModel *model;



};



#endif // STUDENTWINDOW_H