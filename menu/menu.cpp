#include "menu.h"
#include "./../config.h"

Menu::Menu(QWidget *parent)
    : QWidget(parent)
{
    // Load StyleSheet
    QFile file(":/ressources/medias/qss/menu.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    setStyleSheet(styleSheet);

    //Menu customisation
    setFixedWidth(widthMenu);
    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::black);
    setAutoFillBackground(true);
    setPalette(pal);

    //Add icon of the menu
    iconMenu = new QLabel(this);
    iconMenu->setPixmap(QPixmap(":/ressources/medias/images/icon_menu.png"));
    iconMenu->move(0,20);

    //Generate buttons
    buttonDashBoard = new ButtonMenu(QString(":/ressources/medias/images/dashboard.png"),QString(":/ressources/medias/images/dashboard_selected.png"),this);
    buttonMusic = new ButtonMenu(QString(":/ressources/medias/images/music.png"),QString(":/ressources/medias/images/music_selected.png"),this);
    buttonLiveAudio = new ButtonMenu(QString(":/ressources/medias/images/live_audio.png"),QString(":/ressources/medias/images/live_audio_selected.png"),this);
    buttonLiveTV = new ButtonMenu(QString(":/ressources/medias/images/live_tv.png"),QString(":/ressources/medias/images/live_tv_selected.png"),this);
    buttonSettings = new ButtonMenu(QString(":/ressources/medias/images/settings.png"),QString(":/ressources/medias/images/settings_selected.png"),this);

    //Move button to their place
    buttonDashBoard->move(0,spaceBetweenLogoAndFirstButton);
    buttonMusic->move(0,buttonDashBoard->pos().y()+sizeHeightButton + marginBetweenButtons);
    buttonLiveAudio->move(0, buttonMusic->pos().y()+sizeHeightButton + marginBetweenButtons);
    buttonLiveTV->move(0,buttonLiveAudio->pos().y()+sizeHeightButton + marginBetweenButtons);
    buttonSettings->move(0,buttonLiveTV->pos().y()+sizeHeightButton + marginBetweenButtons);

    //Connect each button to update the state of the old button selected
    connect(buttonDashBoard,&ButtonMenu::buttonClicked, this,&Menu::updateButtonCurrentlySelected);
    connect(buttonMusic,&ButtonMenu::buttonClicked, this,&Menu::updateButtonCurrentlySelected);
    connect(buttonLiveAudio,&ButtonMenu::buttonClicked, this,&Menu::updateButtonCurrentlySelected);
    connect(buttonLiveTV,&ButtonMenu::buttonClicked, this,&Menu::updateButtonCurrentlySelected);
    connect(buttonSettings,&ButtonMenu::buttonClicked, this,&Menu::updateButtonCurrentlySelected);


    //First button activate
    buttonCurrentlySelected = buttonDashBoard;
    buttonDashBoard->highlightIcon();

}

void Menu::updateButtonCurrentlySelected(ButtonMenu *buttonMenu)
{
    //Only update if the new button clicked is different than the button selected
    if(buttonMenu->getIdButton()!=buttonCurrentlySelected->getIdButton()){
        buttonCurrentlySelected->unhighlightIcon();
        emit(hideWidgetWindow(buttonCurrentlySelected->getIdButton()));
        this->buttonCurrentlySelected = buttonMenu;
        emit(showWidgetWindow(buttonMenu->getIdButton()));

    }
}
