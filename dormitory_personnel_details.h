#ifndef DORMITORY_PERSONNEL_DETAILS_H
#define DORMITORY_PERSONNEL_DETAILS_H

#include <QMainWindow>
#include"dormitory_info_admin.h"
#include<QSqlTableModel>
#include"student_info_add.h"
namespace Ui {
class Dormitory_Personnel_Details;
}

class Dormitory_Personnel_Details : public QMainWindow
{
    Q_OBJECT

public:
    explicit Dormitory_Personnel_Details(QWidget *parent = nullptr);
    ~Dormitory_Personnel_Details();
    bool connectDatabase(const QString &dbName);

private slots:
    void on_ReturnBtn_clicked();
    void receiveRoomnumber(QString);//接受主窗体的宿舍号

    void on_AddStudentBtn_clicked();
    void on_ShowAllStu_clicked();

    void on_ModifyBtn_clicked();

    //void on_pushButton_2_clicked();

    void on_DeleteBtn_clicked();

signals:
    void send_dormitory_info(QString);//发送添加宿舍成员的信号

private:
    Ui::Dormitory_Personnel_Details *ui;
    QSqlTableModel *model;

};

#endif // DORMITORY_PERSONNEL_DETAILS_H
