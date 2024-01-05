#include "dialog.h"
#include "tcpserver.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TcpServer tcp;
    Dialog w;
    w.show();

    return a.exec();
}
