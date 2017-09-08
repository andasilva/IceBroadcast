/*
 * IceBroadcast
 * P2 Project He-Arc
 * André Neto Da Silva & Axel Rieben
 * 8 september 2017
 */

#include "buttonmenu.h"

int ButtonMenu::totalButtons = 0;

ButtonMenu::ButtonMenu(QWidget *parent) : QPushButton(parent)
{
    this->idButton = ++totalButtons;
    setFixedSize(90,60);
    setCheckable(true);
    connect(this,&ButtonMenu::clicked, this,&ButtonMenu::highlightIcon);
}

ButtonMenu::ButtonMenu(QString iconPath, QString iconSelectedPath, QWidget *parent) : QPushButton(parent)
{
    this->icon = new QIcon(iconPath);
    this->iconHighlighted = new QIcon(iconSelectedPath);
    this->idButton = ++totalButtons;
    setFixedSize(90,60);
    setIcon(*icon);
    setIconSize(QSize(90,60));
    connect(this,&ButtonMenu::clicked, this,&ButtonMenu::highlightIcon);
}

void ButtonMenu::unhighlightIcon()
{
    setIcon(*icon);
}

void ButtonMenu::highlightIcon()
{
    setIcon(*iconHighlighted);
    emit buttonClicked(this);
}

int ButtonMenu::getIdButton() const
{
    return idButton;
}
