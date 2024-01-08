#include "dialog.h"
#include "ui_dialog.h"
#include "administratorwindow.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setFixedSize(800,600);

    QPixmap backgroundImage(":/picture/7.JPG");
    backgroundImage = backgroundImage.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, backgroundImage);

    this->setAutoFillBackground(true);

    this->setPalette(palette);
}

Dialog::~Dialog()
{
    delete ui;
}




void Dialog::on_LoginButton_clicked()
{
    QString username="admin";
    QString password="admin";
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

