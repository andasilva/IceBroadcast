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
    QLabel *logo;
signals:

public slots:
    void setLogo();
};

#endif // DASHBOARDWINDOW_H
