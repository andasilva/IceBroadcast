/*
 * IceBroadcast
 * P2 Project He-Arc
 * André Neto Da Silva & Axel Rieben
 * 8 september 2017
 */

#ifndef DASHBOARDWINDOW_H
#define DASHBOARDWINDOW_H

#include <QWidget>
#include <QtWidgets>
#include "stream/statchart.h"

class DashboardWindow : public QWidget
{
    Q_OBJECT
public:
    explicit DashboardWindow(QWidget *parent = 0);

private:
    QLabel *logo, *labelMusicBeingPlayed, *labelServerStatus;
    StatChart* statChart;
    void setupUi();

signals:

public slots:
    void setLogo();
    void updateServerStatus(bool status);
    void updateMusicBeingPlayed(QString nameSong);
};

#endif // DASHBOARDWINDOW_H
