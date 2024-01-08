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
    //delete this;
}
void Mybutton::setName(QString name){
    this->setText(name);
}


void Mybutton::mousePressEvent(QMouseEvent *event) {
    // Handle the mouse press event
    // Emit the click signal when the button is clicked
    emit click();//发出点击信号
    // Call the base class implementation
    QPushButton::mousePressEvent(event);
}
