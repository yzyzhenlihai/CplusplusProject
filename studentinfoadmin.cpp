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
    this->setFixedSize(800,600);

    QPixmap backgroundImage(":/picture/7.JPG");
    backgroundImage = backgroundImage.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, backgroundImage);

    this->setAutoFillBackground(true);

    this->setPalette(palette);
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

