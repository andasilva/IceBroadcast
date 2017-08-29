#include "IceBroadcast.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IceBroadcast w;
    w.show();

    return a.exec();
}
