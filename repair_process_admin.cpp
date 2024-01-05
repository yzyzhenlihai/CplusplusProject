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

void Repair_Process_Admin::on_ReturnBtn_clicked()
{
    AdministratorWindow *adminWin=new AdministratorWindow;
    adminWin->show();
    this->close();
}


void Repair_Process_Admin::on_ShowRepairBtn_clicked()
{
    model->setFilter("");
    model->select();
}

