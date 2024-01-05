#include "repair_process_admin.h"
#include "ui_repair_process_admin.h"

Repair_Process_Admin::Repair_Process_Admin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Repair_Process_Admin)
{
    ui->setupUi(this);
    if(this->connectDatabase("dormitory_manage_system.db")){
        model=new QSqlTableModel(this);
        model->setTable("repairprocess");
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        ui->ShowRepairContent->setModel(model);
    }
}

Repair_Process_Admin::~Repair_Process_Admin()
{
    delete ui;
}

//连接数据库
bool Repair_Process_Admin::connectDatabase(const QString& dbName){

    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);
    bool ok=db.open();

    return ok;
}

//生成按钮,为每一条记录创建一个按钮
void Repair_Process_Admin::initButton(){
    int row=model->rowCount();//获得行数
    int column=model->columnCount();//获得列数
    //qDebug()<<row<<" "<<column;


    //对按钮进行初始化

    for(int i=0;i<row;i++){
        Mybutton* button = new Mybutton(i);
        button->setName("处理报修");
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

        ui->ShowRepairContent->setIndexWidget(model->index(i,column-1),buttons[i]);
    }
}
//析构生成的按钮
void Repair_Process_Admin::delButtons(){
    for(Mybutton* button : buttons) {
        button->deleteLater();
    }
    buttons.clear();
}
//处理报修按钮槽函数
void Repair_Process_Admin::clickButton(){
    //model->database().transaction();//开始事务
    //修改报修结果为已处理
    Mybutton *btn=qobject_cast<Mybutton*>(sender());//获得发出信号的对象
    int row=(btn->property("row").toString()).toInt();//获得行号
    int column=model->columnCount()-1;
    qDebug()<<row<<" "<<column;
    QModelIndex idx=model->index(row,column-1);
    model->setData(idx,QVariant("已处理"));
    QMessageBox::StandardButton ok=QMessageBox::information(this,"消息","真的已经处理了！？",QMessageBox::Ok|QMessageBox::Cancel);
    if(ok==QMessageBox::Ok){
        // bool flag=model->submitAll();//提交修改
        // bool flag2=model->database().commit();
        // if(!flag){
        //     qDebug()<<"提交失败";
        // }
        // if(!flag2){
        //     qDebug()<<"修改数据库失败";

        model->submitAll();
        QMessageBox::information(this,"消息","处理成功！",QMessageBox::Ok);
    }else{
        model->revertAll();
    }
    model->select();
    delButtons();
    initButton();

}
//返回按钮
void Repair_Process_Admin::on_ReturnBtn_clicked()
{
    AdministratorWindow *adminWin=new AdministratorWindow;
    adminWin->show();
    this->close();
}

//显示报修信息
void Repair_Process_Admin::on_ShowRepairBtn_clicked()
{
    delButtons();
    model->setFilter("");
    model->select();
    initButton();
}

