#include "student_info_query.h"
#include "ui_student_info_query.h"
#include "studentinfoadmin.h"
#include "dialog.h"
Student_Info_Query::Student_Info_Query(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Student_Info_Query)
{
    ui->setupUi(this);
    if(this->connect("dormitory_manage_system.db")){
        model=new QSqlTableModel(this);
        model->setTable("studentinfo");
        model->select();
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);//默认手动提交
        ui->ShowResult->setModel(model);
    }

}
//连接数据库
bool Student_Info_Query::connect(const QString& dbName){
    qDebug() << QSqlDatabase::drivers();//打印数据库驱动
    //打开Mysql
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);
    bool ok=db.open();

    //未连接成功就报错
    if(!ok){
        QMessageBox::information(this,"数据库连接","open failed!");
    }else{
        QMessageBox::information(this,"数据库连接","open successful!");
    }
    return ok;

}
Student_Info_Query::~Student_Info_Query()
{
    delete ui;
}
//返回按钮
void Student_Info_Query::on_ReturnBtn_clicked()
{
    StudentInfoAdmin *stuAdminWin=new StudentInfoAdmin;
    stuAdminWin->show();
    delete this;
}

//打印全表内容
void Student_Info_Query::on_ShowAllBtn_clicked()
{
    model->setTable("studentinfo");
    model->select();
}

