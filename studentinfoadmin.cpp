#include "studentinfoadmin.h"
#include "ui_studentinfoadmin.h"
#include "administratorwindow.h"
#include "student_info_query.h"
#include "dialog.h"
StudentInfoAdmin::StudentInfoAdmin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StudentInfoAdmin)
{
    ui->setupUi(this);
}

StudentInfoAdmin::~StudentInfoAdmin()
{
    delete ui;
}

void StudentInfoAdmin::on_ReturnBtn_clicked()
{
    AdministratorWindow *adminWin=new AdministratorWindow;
    adminWin->show();
    delete this;
}


void StudentInfoAdmin::on_QueryBtn_clicked()
{
    Student_Info_Query *queryWin=new Student_Info_Query;
    queryWin->show();
    this->close();
}

