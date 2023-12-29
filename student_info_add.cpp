#include "student_info_add.h"
#include "ui_student_info_add.h"
#include "student_info_query.h""
Student_Info_Add::Student_Info_Add(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Student_Info_Add)
{
    ui->setupUi(this);
}

Student_Info_Add::~Student_Info_Add()
{
    delete ui;
}

//添加学生界面返回按钮
void Student_Info_Add::on_returnBtn_clicked()
{
    Student_Info_Query *queryWin=new Student_Info_Query;
    queryWin->show();
    delete this;
}


void Student_Info_Add::on_addCommit_clicked()
{


}

