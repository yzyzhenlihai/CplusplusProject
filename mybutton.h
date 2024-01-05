#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QWidget>
#include<QPushButton>
#include<QMessageBox>
#include<QDebug>
class Mybutton : public QPushButton
{
    Q_OBJECT
public:
    Mybutton();
    Mybutton(int i,QWidget*parent=nullptr);
    ~Mybutton();
    void setName(QString name);
    int getIndex();
    void mousePressEvent(QMouseEvent *event);
private:

    int index;//按钮的标号
signals:
    void click();
};

#endif // MYBUTTON_H
