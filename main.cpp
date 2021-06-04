#include "modbustcpclient.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ModbusTCPClient w;
    w.show();
    return a.exec();
}
