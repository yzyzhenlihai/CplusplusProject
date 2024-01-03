#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QWidget>
#include<QPushButton>
#include<QMessageBox>
class Mybutton : public QPushButton
{
    Q_OBJECT
public:
    Mybutton();
    Mybutton(int i,QWidget*parent=nullptr);
    ~Mybutton();
    int index;//按钮的标号
    void setName(QString name);
    int getIndex();


private slots:
    void clickButton();//槽函数，
};

#endif // MYBUTTON_H
