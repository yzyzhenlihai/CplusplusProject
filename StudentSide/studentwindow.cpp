#include "studentwindow.h"
#include "ui_studentwindow.h"
#include "studentlogin.h"
#include"repairsubmit.h"
StudentWindow::StudentWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StudentWindow)
{
    ui->setupUi(this);
}

StudentWindow::~StudentWindow()
{
    delete ui;
}





void StudentWindow::on_ReturnLoginBtn_clicked()
{
    StudentLogin *loginwin=new StudentLogin;
    loginwin->show();
    delete this;
}


void StudentWindow::on_RepairBtn_clicked()
{
    RepairSubmit *repSubWin=new RepairSubmit;
    repSubWin->show();
    this->close();
}

void StudentWindow::on_RepairInfoBtn_clicked()
{
    // DormitoryInfoAdmin *DormitoryInfoWin=new DormitoryInfoAdmin;
    // DormitoryInfoWin->show();
    // this->close();
}
