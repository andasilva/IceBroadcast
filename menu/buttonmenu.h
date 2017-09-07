#ifndef BUTTONMENU_H
#define BUTTONMENU_H

#include <QWidget>
#include <QtWidgets>

class ButtonMenu: public QPushButton
{

    Q_OBJECT

public:
    ButtonMenu(QWidget* parent=0);
    ButtonMenu(QString iconPath,QString iconSelectedPath,QWidget* parent=0);
    int getIdButton() const;

private:
    static int totalButtons; //define the idButton
    int idButton;
    QIcon *icon;
    QIcon *iconHighlighted;

public slots:
    void highlightIcon();
    void unhighlightIcon();

signals:
    void buttonClicked(ButtonMenu *button);

};

#endif // BUTTONMENU_H
