#include "statchart.h"
#include <QtSql>

StatChart::StatChart(QWidget *parent) : QWidget(parent)
{
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    QHBoxLayout* mainLayout = new QHBoxLayout;

    series = new QLineSeries;
    chart = new QChart;
    axisX = new QDateTimeAxis;
    axisY = new QValueAxis;
    chartView = new QChartView;


    int day = 15;
    int month = 1;
    int year = 2012;


    /*Get info from server*/
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("192.168.1.42");
    db.setPort(3306);
    db.setDatabaseName("icebroadcast");
    db.setUserName("root");
    db.setPassword("pa$$w0rd"); // Don't worry, it's only a password for local test :-)
    if(db.open())
       qDebug() << "Connexion to database... Ok" ;
    else
       qDebug() << "Connexion to database... Error: " << db.lastError();



    for(int i = 0; i < 7; i++){
        QDateTime time;
        qDebug() << "2017090515"+QString::number(day);
        time.setDate(QDate::fromString("20170905", "yyyyMMdd"));
        time.setTime(QTime::fromString("14"+QString::number(day),"hhmm"));
        series->append(time.toMSecsSinceEpoch(),day);
        qDebug() << time.toMSecsSinceEpoch();
        day++;
    }

    chart->addSeries(series);
    chart->legend()->hide();
    chart->setTitle("Listeners Statistiques");

    //Put axis X
    axisX->setTickCount(7);
    axisX->setFormat("hh:mm");
    axisX->setTitleText("Date");
    chart->addAxis(axisX,Qt::AlignBottom);
    series->attachAxis(axisX);

    //Put axis Y
    axisY->setLabelFormat("%i");
    axisY->setTitleText("Listeners count");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chartView = new QChartView(chart);
    chart->setTheme(QChart::ChartThemeDark);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setFixedHeight(400);

    mainLayout->addWidget(chartView);

    setLayout(mainLayout);
}
