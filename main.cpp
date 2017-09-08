/*
 * IceBroadcast
 * P2 Project He-Arc
 * André Neto Da Silva & Axel Rieben
 * 8 september 2017
 */

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
    w.setMinimumSize(1280,720);
    w.show();

    return a.exec();
}
