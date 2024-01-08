#include "administratorwindow.h"
#include "ui_administratorwindow.h"
#include "dialog.h"
#include"studentinfoadmin.h"
#include"student_info_query.h"
#include"dormitory_info_admin.h"
AdministratorWindow::AdministratorWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AdministratorWindow)
{
    ui->setupUi(this);
    this->setFixedSize(800,600);

    QPixmap backgroundImage(":/picture/7.JPG");
    backgroundImage = backgroundImage.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, backgroundImage);

    this->setAutoFillBackground(true);

    this->setPalette(palette);
}

AdministratorWindow::~AdministratorWindow()
{
    delete ui;
}





void AdministratorWindow::on_ReturnLoginBtn_clicked()
{
    Dialog *loginwin=new Dialog;
    loginwin->show();
    delete this;
}


void AdministratorWindow::on_StuInfoAdminBtn_clicked()
{
    Student_Info_Query *queryWin=new Student_Info_Query;
    queryWin->show();
    this->close();
}


void AdministratorWindow::on_DormitoryInfoAdminBtn_clicked()
{
    Dormitory_Info_Admin *dormitoryWin=new Dormitory_Info_Admin;
    dormitoryWin->show();
    this->close();
}


void AdministratorWindow::on_RepairProcessBtn_clicked()
{
    Repair_Process_Admin *repairWin=new Repair_Process_Admin;
    repairWin->show();
    this->close();
}

