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
    if(!ok){
        QMessageBox::information(this,"数据库连接","open failed!");
    }else{
        QMessageBox::information(this,"数据库连接","open successful!");
    }

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
        buttons.append(button);

    }
    // //实现信号和槽函数连接
    for(int i=0;i<row;i++){
        connect(buttons[i],SIGNAL(click()),buttons[i],SLOT(clickButton()));
    }

    // //添加按钮到model
    for(int i=0;i<row;i++){

        ui->ShowResult->setIndexWidget(model->index(i,column-1),buttons[i]);
    }
    // Mybutton* button = new Mybutton(1);
    // button->setName("查看详情");
    // ui->ShowResult->setIndexWidget(model->index(0,2),button);
    // Mybutton* button2 = new Mybutton(1);
    // button2->setName("查看详情");
    // ui->ShowResult->setIndexWidget(model->index(1,2),button2);
}

//显示全表按钮
void Dormitory_Info_Admin::on_ShowAllBtn_clicked()
{
    delButtons();
    model->setTable("dormitoryinfo");
    model->select();
    initButton();


}

//返回按钮
void Dormitory_Info_Admin::on_ReturnBtn_clicked()
{
    AdministratorWindow *adminWin=new AdministratorWindow;
    adminWin->show();
    this->close();
}


void Dormitory_Info_Admin::on_QueryBtn_clicked()
{
    delButtons();
    QString queryType=ui->QueryChoice->currentText();//获得查询类型
    QString queryEdit=ui->QueryEdit->text();
    if(queryEdit==""){
        QMessageBox::information(this,"提示","输入不能为空",QMessageBox::Ok);

    }else if(queryType=="按宿舍号"){
        model->setFilter("");
        QString sql="roomnumber="+queryEdit;
        model->setFilter(sql);
        initButton();

    }


}

