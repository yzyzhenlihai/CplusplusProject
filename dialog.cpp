#include "dialog.h"
#include "ui_dialog.h"
#include "administratorwindow.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

}

Dialog::~Dialog()
{
    delete ui;
}




void Dialog::on_LoginButton_clicked()
{
    QString username="";
    QString password="";
    if((ui->UserNameLineEdit->text()==username)&&ui->PasswordLineEdit->text()==password){
        AdministratorWindow *adminwin=new AdministratorWindow;
        adminwin->show();
        this->close();
    }else{
        QString dlgTitle="error";
        QString strInfo="Incorrect account or password!";
        QMessageBox::critical(this,dlgTitle,strInfo);
    }
}

