/*
 * IceBroadcast
 * P2 Project He-Arc
 * André Neto Da Silva & Axel Rieben
 * 8 september 2017
 */

#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QtWidgets>
#include "buttonmenu.h"

class Menu : public QWidget
{
    Q_OBJECT

public:
    Menu(QWidget *parent = 0);
private:
    ButtonMenu* buttonDashBoard, *buttonMusic, *buttonLiveAudio, *buttonLiveTV, *buttonSettings;
    ButtonMenu* buttonCurrentlySelected;
    QLabel* iconMenu;

public slots:
    void updateButtonCurrentlySelected(ButtonMenu *buttonMenu);

signals:
    void hideWidgetWindow(int idButton);
    void showWidgetWindow(int idButton);
};

#endif // MENU_H
