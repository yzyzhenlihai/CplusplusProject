#include "dormitory_personnel_details.h"
#include "ui_dormitory_personnel_details.h"

Dormitory_Personnel_Details::Dormitory_Personnel_Details(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Dormitory_Personnel_Details)
{
    ui->setupUi(this);


    if(this->connectDatabase("dormitory_manage_system.db")){
        //创建模型
        model=new QSqlTableModel(this);
        model->setTable("studentinfo");
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);//默认手动提交
        ui->ShowDormitoryInfo->setModel(model);
    }
}

Dormitory_Personnel_Details::~Dormitory_Personnel_Details()
{
    delete ui;
}

//按宿舍号筛选出学生
void Dormitory_Personnel_Details::receiveRoomnumber(QString roomnumber){
    qDebug()<<roomnumber;
    model->setFilter("");
    QString sql="roomnumber="+roomnumber;
    model->setFilter(sql);
    model->select();
    ui->TitleLabel->setText(roomnumber);

}
//连接数据库
bool Dormitory_Personnel_Details::connectDatabase(const QString &dbName){
    qDebug() << QSqlDatabase::drivers();//打印数据库驱动
    //打开Sqlite
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);//设定数据库文件的名称
    bool ok=db.open();
    //未连接成功就报错
    // if(!ok){
    //     QMessageBox::information(this,"数据库连接","open failed!");
    // }else{
    //     QMessageBox::information(this,"数据库连接","open successful!");
    // }

    return ok;
}
//返回按钮
void Dormitory_Personnel_Details::on_ReturnBtn_clicked()
{
    Dormitory_Info_Admin *dormitoryAdminWin=new Dormitory_Info_Admin;
    dormitoryAdminWin->show();
    this->close();
}

//添加宿舍成员
void Dormitory_Personnel_Details::on_AddStudentBtn_clicked()
{
    Student_Info_Add* addWin=new Student_Info_Add;
    addWin->show();
    //建立连接
    connect(this,SIGNAL(send_dormitory_info(QString)),addWin,SLOT(receive_add_info(QString)));
    emit send_dormitory_info("添加宿舍成员");
    //this->close();
}

//显示宿舍成员信息
void Dormitory_Personnel_Details::on_ShowAllStu_clicked()
{
    QString roomnumber=ui->TitleLabel->text();
    model->setFilter("");
    QString sql="roomnumber="+roomnumber;
    model->setFilter(sql);
    model->select();
}

//确认修改按钮
void Dormitory_Personnel_Details::on_ModifyBtn_clicked()
{
    //开始事务操作
    model->database().transaction();
    QString dlgTitle="修改信息消息框";
    QString strInfo="确认修改个人信息？！";
    QMessageBox::StandardButton result;
    result=QMessageBox::information(this,dlgTitle,strInfo,QMessageBox::Ok|QMessageBox::Cancel);
    model->submitAll();
    if(result==QMessageBox::Ok){
        //提交
        model->database().commit();
        QMessageBox::information(this,"修改信息","个人信息修改成功！",QMessageBox::Ok);
    }else if(result==QMessageBox::Cancel){
        //回滚
        model->database().rollback();
    }
}


void Dormitory_Personnel_Details::on_DeleteBtn_clicked()
{
    //获得删除行所在列
    int curRow=ui->ShowDormitoryInfo->currentIndex().row();
    //删除改行
    model->removeRow(curRow);
    QString dlgTitle="删除信息消息框";
    QString strInfo="确认删除个人信息？！";
    int ok=QMessageBox::information(this,dlgTitle,strInfo,QMessageBox::Ok|QMessageBox::Cancel);
    if(ok==QMessageBox::Ok){
        //提交修改
        model->submitAll();
        QMessageBox::information(this,"删除信息","个人信息删除成功！",QMessageBox::Ok);

    }else{
        //撤销修改
        model->revertAll();
    }
}

