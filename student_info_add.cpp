#include "student_info_add.h"
#include "dormitory_personnel_details.h"
#include "ui_student_info_add.h"
#include "student_info_query.h"
#include <QMessageBox>
Student_Info_Add::Student_Info_Add(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Student_Info_Add)
{
    ui->setupUi(this);
    if(this->connectDatabase("dormitory_manage_system.db")){
        //创建模型
        model=new QSqlTableModel(this);
        model->setTable("studentinfo");
        //model->select();
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);//默认手动提交

    }

}

Student_Info_Add::~Student_Info_Add()
{
    delete ui;
}

//连接数据库
bool Student_Info_Add::connectDatabase(const QString& dbName){
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
//添加学生界面返回按钮
void Student_Info_Add::on_returnBtn_clicked()
{

    if(returnWay=="添加宿舍成员"){
        //返回宿舍信息管理的界面
        //Dormitory_Personnel_Details* detailWin=new Dormitory_Personnel_Details;
        //detailWin->show();
        this->close();
    }else{
        Student_Info_Query *queryWin=new Student_Info_Query;
        queryWin->show();
        delete this;
    }


}
//收到添加个人信息的槽
void Student_Info_Add::receive_add_info(QString returnWay){
    this->returnWay=returnWay;
}
//信息提交按钮
void Student_Info_Add::on_addCommit_clicked()
{
    QString id=ui->idEdit->text();
    QString name=ui->nameEdit->text();
    QString sex=ui->sexEdit->text();
    QString age=ui->ageEdit->text();
    QString major=ui->majorEdit->text();
    QString cla=ui->classEdit->text();
    QString phonenumber=ui->phonenumberEdit->text();
    QString roomnumber=ui->roomnumberEdit->text();
    QString bednumber=ui->roomnumberEdit->text();
    QString password=ui->passwordEdit->text();
    //获得一条空记录
    QSqlRecord rec=model->record();
    rec.setValue(model->fieldIndex("id"),id);
    rec.setValue(model->fieldIndex("name"),name);
    rec.setValue(model->fieldIndex("sex"),sex);
    rec.setValue(model->fieldIndex("age"),age);
    rec.setValue(model->fieldIndex("major"),major);
    rec.setValue(model->fieldIndex("class"),cla);
    rec.setValue(model->fieldIndex("phonenumber"),phonenumber);
    rec.setValue(model->fieldIndex("roomnumber"),roomnumber);
    rec.setValue(model->fieldIndex("bednumber"),bednumber);
    rec.setValue(model->fieldIndex("password"),password);
    //插入到模型的最后
    model->insertRecord(model->rowCount(),rec);
    //确认是否添加
    QString dlgTitle="添加信息消息框";
    QString strInfo="确认添加个人信息？！";
    QMessageBox::StandardButton result;
    result=QMessageBox::question(this,dlgTitle,strInfo,QMessageBox::Yes|QMessageBox::Cancel);
    if(result==QMessageBox::Yes){
        bool res=model->submitAll();//提交记录到数据库
        if(!res){
            QMessageBox::information(this,"消息","数据保存错误！"+model->lastError().text());
        }
        //提示添加成功
        QMessageBox::information(this,"个人信息添加","个人信息添加成功！",QMessageBox::Ok);
        //回到查询界面
        if(returnWay=="添加宿舍成员"){
            //返回宿舍信息管理的界面
            Dormitory_Personnel_Details* detailWin=new Dormitory_Personnel_Details;
            detailWin->show();
            this->close();
        }else{
            Student_Info_Add *addWin=new Student_Info_Add;
            addWin->show();
            this->close();
        }
    }else if(result==QMessageBox::Cancel){
        //取消添加
        model->revertAll();
    }



}
//接受图片字符串
void Student_Info_Add::receivePicture(QByteArray picture){
    ui->pictureEdit->textEdited(picture);
}
//添加图片按钮
void Student_Info_Add::on_addPictureBtn_clicked()
{
    //打开电脑文件选择图片
    QString fileName = QFileDialog::getOpenFileName(this, "Select Image", QDir::homePath(), "Images (*.png *.jpg)");
    QFile file(fileName);
    //打开图片
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray imageData = file.readAll();//读取二进制图片
        QImage originalImage;
        originalImage.loadFromData(imageData);
        //压缩图片
        QSize newSize(800, 600); // 指定新的大小
        QImage scaledImage = originalImage.scaled(newSize, Qt::KeepAspectRatio); // 压缩图片到指定大小，保持原始图片的宽高
        QByteArray compressedData;
        QBuffer buffer(&compressedData);
        buffer.open(QIODevice::WriteOnly);
        scaledImage.save(&buffer, "JPEG", 50);//压缩比，压缩质量
        buffer.close();
        file.close();
        //添加至数据库
        connect(this,SIGNAL(sendPicture(QByteArray)),this,SLOT(receivePicture(QByteArray)));
        emit(sendPicture(compressedData));

    }


}

