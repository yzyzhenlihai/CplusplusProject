#include "dormitory_info_admin.h"
#include "ui_dormitory_info_admin.h"
#include "administratorwindow.h"
Dormitory_Info_Admin::Dormitory_Info_Admin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Dormitory_Info_Admin)
{
    ui->setupUi(this);
    if(this->connectDatabase("dormitory_manage_system.db")){
        //创建模型
        model=new QSqlTableModel(this);
        model->setTable("dormitoryinfo");
        //model->select();
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);//默认手动提交
        ui->ShowResult->setModel(model);


    }

}

Dormitory_Info_Admin::~Dormitory_Info_Admin()
{
    delete ui;
}
//delete已经创建的按钮
void Dormitory_Info_Admin::delButtons(){
    for(Mybutton* button : buttons) {
        button->deleteLater();
    }
    buttons.clear();
}
//连接数据库
bool Dormitory_Info_Admin::connectDatabase(const QString &dbName){
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

//每条记录创建按钮
void Dormitory_Info_Admin::initButton(){
    int row=model->rowCount();//获得行数
    int column=model->columnCount();//获得列数
    qDebug()<<row<<" "<<column;


    //对按钮进行初始化

    for(int i=0;i<row;i++){
        Mybutton* button = new Mybutton(i);
        button->setName("查看详情");
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

        ui->ShowResult->setIndexWidget(model->index(i,column-1),buttons[i]);
    }
    // Mybutton* button = new Mybutton(1);
    // button->setName("查看详情");
    // ui->ShowResult->setIndexWidget(model->index(0,2),button);
    // bool result=connect(button,SIGNAL(click()),button,SLOT(clickButton()));
    // if(!result){
    //         qDebug()<<"槽函数连接失败！";
    //     }
    // Mybutton* button2 = new Mybutton(1);
    // button2->setName("查看详情");
    // ui->ShowResult->setIndexWidget(model->index(1,2),button2);
    // connect(button2,SIGNAL(click()),button2,SLOT(clickButton()));
}

//显示全表按钮
void Dormitory_Info_Admin::on_ShowAllBtn_clicked()
{
    delButtons();
    model->setTable("dormitoryinfo");
    model->select();
    initButton();


}
//查看详情按钮槽函数
void Dormitory_Info_Admin::clickButton(){
    Mybutton *btn=qobject_cast<Mybutton*>(sender());//获得发出信号的对象
    if(btn){
        Dormitory_Personnel_Details *detailWin=new Dormitory_Personnel_Details;
        detailWin->show();
        //建立与新窗体的连接
        connect(this,SIGNAL(sendRoomnumber(QString)),detailWin,SLOT(receiveRoomnumber(QString)));
        QString row=btn->property("row").toString();
        //获得行记录
        QString rowData=(model->data(model->index(row.toInt(),0))).toString();//获得宿舍号

        //向子窗口传递数据
        emit sendRoomnumber(rowData);
        this->close();

    }
}

//返回按钮
void Dormitory_Info_Admin::on_ReturnBtn_clicked()
{
    AdministratorWindow *adminWin=new AdministratorWindow;
    adminWin->show();
    this->close();
}

//查询按钮
void Dormitory_Info_Admin::on_QueryBtn_clicked()
{
    delButtons();

    QString queryType=ui->QueryChoice->currentText();//获得查询类型
    QString queryEdit=ui->QueryEdit->text();
    if(queryEdit==""){
        initButton();
        QMessageBox::information(this,"提示","输入不能为空",QMessageBox::Ok);


    }else if(queryType=="按宿舍号"){
        model->select();
        model->setFilter("");
        QString sql="roomnumber="+queryEdit;
        model->setFilter(sql);
        initButton();

    }


}

