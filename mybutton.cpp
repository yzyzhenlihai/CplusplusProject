#include "mybutton.h"

//构造函数
Mybutton::Mybutton(){}
Mybutton::Mybutton(int i,QWidget *parent)
    : QPushButton(parent)
{
    this->index=i;
}
//析构函数
Mybutton::~Mybutton(){
    delete this;
}
void Mybutton::setName(QString name){
    this->setText(name);
}

//槽函数
void Mybutton::clickButton(){
    QPushButton *btn=(QPushButton*)sender();//获得发出信号的对象
    QString row=btn->property("row").toString();//获得按钮的row属性
    QString info="此时的按钮在第"+row+"行";
    QMessageBox::information(this,"消息",info,QMessageBox::Ok);
}
