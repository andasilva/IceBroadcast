#include "statchart.h"
#include <QtSql>
#include <QThread>
#include <QtConcurrent>


StatChart::StatChart(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout* mainLayout = new QHBoxLayout;

    series = new QLineSeries;
    chart = new QChart;
    axisX = new QDateTimeAxis;
    axisY = new QValueAxis;
    chartView = new QChartView;

    //connectToDatabase();
    QFuture<void> future = QtConcurrent::run(connectToDatabase);
    QSqlDatabase db =  QSqlDatabase::database();
    if(db.isOpen()){
        getStats();
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

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateDatabase()));
    timer->start(300000); // Update statistics each 5min
}

void StatChart::getStats()
{
    series->clear();
    QSqlQuery query ;
    if(query.exec("SELECT * FROM statistics ORDER BY date DESC LIMIT 7")){
        while(query.next()){
            QString date = query.value(0).toString() ;
            int number = query.value(1).toInt();

            QDateTime time;
            time.setDate(QDate::fromString(date.remove("-").left(8), "yyyyMMdd"));
            time.setTime(QTime::fromString(date.remove(":").right(6).left(4),"hhmm"));
            series->append(time.toMSecsSinceEpoch(),number);
        }
        chart->removeSeries(series);
        chart->addSeries(series);
        chart->removeAxis(axisX);
        chart->removeAxis(axisY);
        axisX = new QDateTimeAxis;
        axisY = new QValueAxis;

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
    } else
        qDebug() << "La requête a échoué";
}

bool StatChart::connectToDatabase()
{
    QSqlDatabase db =  QSqlDatabase::database();
    if(!db.isOpen()){
        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("192.168.1.42");
        db.setPort(3306);
        db.setDatabaseName("icebroadcast");
        db.setUserName("root");
        db.setPassword("pa$$w0rd"); // Don't worry, it's only a password for local test :-)
        if(db.open()){
            qDebug() << "Connexion to database... Ok" ;
            return true;
        }else{
            qDebug() << "Connexion to database... Error: " << db.lastError();
            return false;
        }
    }
}

void StatChart::updateDatabase()
{
    qDebug() << "Update stats";
    QSqlDatabase db =  QSqlDatabase::database();
    if(db.isOpen()){
        getStats();
    }else{
        qDebug() << "Database not open";
        QFuture<void> future = QtConcurrent::run(connectToDatabase);
    }
    qDebug() << "End of update";
}
