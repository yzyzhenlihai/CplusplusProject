#include "student_info_query.h"
#include "ui_student_info_query.h"
#include "studentinfoadmin.h"
#include <QSqlTableModel>
#include<QtSql/QSqlDatabase>
#include<QDebug>
#include <QSqlError>
#include<QMessageBox>
#include "student_info_add.h"
Student_Info_Query::Student_Info_Query(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Student_Info_Query)
{
    ui->setupUi(this);
    //在构造函数实现数据库的连接
    if(this->connect("dormitory_manage_system.db")){

        model=new QSqlTableModel(this);
        model->setTable("studentinfo");
        //model->select();
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);//默认手动提交
        ui->ShowResult->setModel(model);
    }

}
//连接数据库
bool Student_Info_Query::connect(const QString& dbName){
    qDebug() << QSqlDatabase::drivers();//打印数据库驱动
    //打开Sqlite
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    //打开mysql
    // QSqlDatabase db=QSqlDatabase::addDatabase("QODBC");
    // db.setHostName("127.0.0.1");
    // db.setPort(3306);
    db.setDatabaseName(dbName);
    // db.setUserName("root");
    // db.setPassword("yu121314");
    bool ok=db.open();
    // QStringList tables = db.tables();
    // foreach(QString table, tables)
    //     qDebug()<<table;

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


void Student_Info_Query::on_QueryBtn_clicked()
{
    QString queryType=ui->QueryChoice->currentText();//获得查询类型
    QString queryContent=ui->lineEdit->text();//获得查询内容
    //查询
    if(queryType=="按学号"){
        model->setFilter("");
        QString sql="id="+queryContent;
        model->setFilter(sql);
    }else if(queryType=="按宿舍号"){
         model->setFilter("");
        QString sql="roomnumber="+queryContent;
        model->setFilter(sql);
    }
}


void Student_Info_Query::on_AddInfoBtn_clicked()
{
    Student_Info_Add *addWin=new Student_Info_Add;
    addWin->show();
}

