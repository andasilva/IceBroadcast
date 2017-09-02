#ifndef DASHBOARDWINDOW_H
#define DASHBOARDWINDOW_H

#include <QWidget>
#include <QtWidgets>

class DashboardWindow : public QWidget
{
    Q_OBJECT
public:
    explicit DashboardWindow(QWidget *parent = 0);

private:
    QLabel *logo, *labelMusicBeingPlayed, *labelServerStatus;
signals:

public slots:
    void setLogo();
    void updateServerStatus(bool status);
    void updateMusicBeingPlayed(QString nameSong);
};

#endif // DASHBOARDWINDOW_H
