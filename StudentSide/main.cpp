#include "studentlogin.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StudentLogin w;
    w.show();
    return a.exec();
}
