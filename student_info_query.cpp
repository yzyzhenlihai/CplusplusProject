#include "student_info_query.h"
#include "ui_student_info_query.h"
#include "studentinfoadmin.h"
#include "administratorwindow.h"
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
    this->setFixedSize(800,600);

    QPixmap backgroundImage(":/picture/7.JPG");
    backgroundImage = backgroundImage.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, backgroundImage);

    this->setAutoFillBackground(true);

    this->setPalette(palette);
    //在构造函数实现数据库的连接
    if(this->connectDatabase("dormitory_manage_system.db")){

        model=new QSqlTableModel(this);
        model->setTable("studentinfo");
        //model->select();
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);//默认手动提交
        ui->ShowResult->setModel(model);

    }

}
//连接数据库
bool Student_Info_Query::connectDatabase(const QString& dbName){
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
    // if(!ok){
    //     QMessageBox::information(this,"数据库连接","open failed!");
    // }else{
    //     QMessageBox::information(this,"数据库连接","open successful!");
    // }

    return ok;

}
Student_Info_Query::~Student_Info_Query()
{
    delete ui;
}
//返回按钮
void Student_Info_Query::on_ReturnBtn_clicked()
{
    AdministratorWindow *adminWin=new AdministratorWindow;
    adminWin->show();
    this->close();
}

//打印全表内容
void Student_Info_Query::on_ShowAllBtn_clicked()
{
    delButton();
    model->setTable("studentinfo");
    model->select();
    ui->ShowResult->hideColumn(11);//隐藏图片列
    initButton();

}
//析构按钮
void Student_Info_Query::delButton(){
    if(!buttons.empty()){
        for(Mybutton* button : buttons) {
            button->deleteLater();
        }
        buttons.clear();
    }
}
//初始化表格中的按钮
void Student_Info_Query::initButton(){
    int row=model->rowCount();//获得行数
    int column=model->columnCount();//获得列数
    qDebug()<<row<<" "<<column;
    //对按钮进行初始化

    for(int i=0;i<row;i++){
        Mybutton* button = new Mybutton(i);
        button->setName("查看帅照");
        button->setProperty("row",i);
        buttons.append(button);

    }
    //连接槽函数
    for(int i=0;i<row;i++){

        //添加槽函数
        bool result=connect(buttons[i],SIGNAL(click()),this,SLOT(clickButton()));
        if(!result){
            qDebug()<<"槽函数连接失败！";
        }

    }

    // //添加按钮到model
    for(int i=0;i<row;i++){

        ui->ShowResult->setIndexWidget(model->index(i,4),buttons[i]);
    }

}
//查看帅照按钮
void Student_Info_Query::clickButton(){
    Mybutton* btn=qobject_cast<Mybutton*>(sender());
    int row=(btn->property("row").toString()).toInt();
    int column=model->columnCount();
    QModelIndex idx=model->index(row,column-1);
    QString picture=model->data(idx).toString();
    QByteArray imageData = QByteArray::fromBase64(picture.toUtf8());//将图片转换为二进制
    QImage image;//定义图片
    image.loadFromData(imageData);
    QLabel* label=new QLabel;
    label->setPixmap(QPixmap::fromImage(image));
    label->show();
}
//查询按钮
void Student_Info_Query::on_QueryBtn_clicked()
{
    delButton();
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
    Student_Info_Query::dormitory_newnumber();
    initButton();
   // int curRow=ui->ShowResult->currentIndex().row();

}


void Student_Info_Query::on_AddInfoBtn_clicked()
{
    Student_Info_Add *addWin=new Student_Info_Add;
    addWin->show();
    this->close();

}

//修改个人信息
void Student_Info_Query::on_ModifyBtn_clicked()
{
    delButton();

    int curRow=ui->ShowResult->currentIndex().row();
    QVariant roomnumber = ui->ShowResult->model()->data(ui->ShowResult->model()->index(curRow, 8));

    //开始事务操作
    model->database().transaction();
    QString dlgTitle="修改信息消息框";
    QString strInfo="确认修改个人信息？！";
    QMessageBox::StandardButton result;
    result=QMessageBox::information(this,dlgTitle,strInfo,QMessageBox::Ok|QMessageBox::Cancel);

    if(result==QMessageBox::Ok){
        //提交
        if(model->submitAll()){

            bool res=model->database().commit();//提交记录到数据库
            if(!res){
                QMessageBox::information(this,"消息","数据保存错误！"+model->lastError().text());
            }else{
                Student_Info_Query::dormitory_newnumber();
               QMessageBox::information(this,"修改信息","个人信息修改成功！",QMessageBox::Ok);

            }
        }else{
            QMessageBox::information(this,"消息","宿舍已满或床号冲突！");
        }

    }else if(result==QMessageBox::Cancel){
        //回滚
        model->database().rollback();
    }
    initButton();
}

//删除个人信息
void Student_Info_Query::on_DeleteBtn_clicked()
{
    delButton();
    //获得删除行所在列
    int curRow=ui->ShowResult->currentIndex().row();
    QVariant roomnumber = ui->ShowResult->model()->data(ui->ShowResult->model()->index(curRow, 9));
    //qDebug()<<roomnumber<<"qwe";
    //删除改行
    model->removeRow(curRow);
    QString dlgTitle="删除信息消息框";
    QString strInfo="确认删除个人信息？！";
    int ok=QMessageBox::information(this,dlgTitle,strInfo,QMessageBox::Ok|QMessageBox::Cancel);
    if(ok==QMessageBox::Ok){
        //提交修改
        model->submitAll();
        dormitory_newnumber();
        QMessageBox::information(this,"删除信息","个人信息删除成功！",QMessageBox::Ok);

    }else{
        //撤销修改
        model->revertAll();
    }
    initButton();

}
/*
void Student_Info_Query::dormitory_newnumber(){//更新每个宿舍人数
    QSqlQuery query;

    query.prepare("SELECT roomnumber, COUNT(*) AS count FROM studentinfo GROUP BY roomnumber");
    if (query.exec()) {
        while (query.next()) {
            QString value = query.value(0).toString(); // 获取列中的值
            int count = query.value(1).toInt(); // 获取每种参数的数量
              QSqlQuery query1;
            query1.prepare("UPDATE dormitoryinfo SET number = :numberInt WHERE roomnumber = :roomnumber");
            query1.bindValue(":numberInt", count);
            query1.bindValue(":roomnumber", value);
            query1.exec();
            qDebug() << "Value:" << value << "Count:" << count;}
    }
}
*/
void Student_Info_Query::dormitory_newnumber() {
    QSqlQuery query;

    query.prepare("SELECT d.roomnumber, COALESCE(s.count, 0) AS count "
                  "FROM dormitoryinfo d "
                  "LEFT JOIN (SELECT roomnumber, COUNT(*) AS count FROM studentinfo GROUP BY roomnumber) s "
                  "ON d.roomnumber = s.roomnumber");

    if (query.exec()) {
        while (query.next()) {
            QString value = query.value(0).toString(); // 获取列中的值
            int count = query.value(1).toInt(); // 获取每种参数的数量

            QSqlQuery updateQuery;
            updateQuery.prepare("UPDATE dormitoryinfo SET number = :numberInt WHERE roomnumber = :roomnumber");
            updateQuery.bindValue(":numberInt", count);
            updateQuery.bindValue(":roomnumber", value);

            if (!updateQuery.exec()) {
                qDebug() << "更新宿舍信息失败，房间号：" << value;
            }
            qDebug() << "房间号：" << value << "人数：" << count;
        }
    } else {
        qDebug() << "更新宿舍信息查询失败";
    }
}
