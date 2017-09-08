/*
 * IceBroadcast
 * P2 Project He-Arc
 * André Neto Da Silva & Axel Rieben
 * 8 september 2017
 */

#ifndef ICEBROADCAST_H
#define ICEBROADCAST_H

#include <QWidget>
#include <QtWidgets>
#include "menu/buttonmenu.h"
#include "menu/menu.h"
#include "windows/dashboardwindow.h"
#include "windows/audiowindow.h"
#include "windows/liveaudiowindow.h"
#include "windows/livetvwindow.h"
#include "windows/settingswindow.h"

class IceBroadcast : public QWidget
{
    Q_OBJECT

public:
    IceBroadcast(QWidget *parent = 0);
    ~IceBroadcast();

private:
    Menu *mainMenu;
    DashboardWindow *dashboardWindow;
    AudioWindow *audioWindow;
    LiveAudioWindow *liveAudioWindow;
    LiveTvWindow *liveTvWindow;
    SettingsWindow *settingsWindow;

public slots:
    void showWidgetWindow(int idButton);
    void hideWidgetWindow(int idButton);
};

#endif // ICEBROADCAST_H
