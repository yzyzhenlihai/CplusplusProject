#include "repair_process_admin.h"
#include "ui_repair_process_admin.h"

Repair_Process_Admin::Repair_Process_Admin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Repair_Process_Admin)
{
    ui->setupUi(this);
}

Repair_Process_Admin::~Repair_Process_Admin()
{
    delete ui;
}
