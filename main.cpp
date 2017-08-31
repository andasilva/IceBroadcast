#include "IceBroadcast.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Define Settings Informations
    QCoreApplication::setOrganizationName("A2Society");
    QCoreApplication::setOrganizationDomain("a2society.com");
    QCoreApplication::setApplicationName("IceBroadcast");

    IceBroadcast w;
    w.setMinimumSize(1200,700);
    w.show();

    return a.exec();
}
