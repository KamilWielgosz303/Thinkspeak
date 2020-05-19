#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), temperatureData(100), temperatureTime(100), tempTime(100)
{
    ui->setupUi(this);
    ui->chartView->setRenderHint(QPainter::Antialiasing);
    chart = new Chart();
    ui->chartView->setChart(chart->chart);
    myurl.setScheme("http");
    myurl.setHost("api.thingspeak.com");
    myurl.setPath("/channels/1057622/feeds.json");
    //qDebug() << myurl.toString();
    restclient = new QNetworkAccessManager(this);
    connect(restclient, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply *)));
    connect(&thread, SIGNAL(tick()), this, SLOT(getThinkspeakData()));
    thread.start(thread.HighestPriority);
}

MainWindow::~MainWindow()
{
    thread.terminate();
    delete chart;
    delete reply;
    delete restclient;
    delete ui;
}
void MainWindow::getThinkspeakData(){
    QNetworkRequest request;
    request.setUrl(myurl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    reply = restclient->get(request);
}


void MainWindow::replyFinished(QNetworkReply * reply){
    tempTime.clear();
    temperatureData.clear();
    temperatureTime.clear();
    qDebug()<<temperatureData.size();
    qDebug()<<tempTime.size();
    QJsonDocument jsdoc;
    jsdoc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject jsobj = jsdoc.object();
    jsarr = jsobj["feeds"].toArray();
    //qDebug()<<jsarr.size();
    foreach (const QJsonValue &value, jsarr) {
    QJsonObject jsob = value.toObject();
    //qDebug() << jsob["entry_id"].toInt();
    // qDebug() << jsob["field1"].toString();
    //qDebug() << jsob["field2"].toString();
    //qDebug() << jsob["field3"].toString();
    //qDebug() << jsob["created_at"].toString();
    temperatureData.push_front(jsob["field1"].toString().toDouble());
    temperatureTime.push_front(jsob["created_at"].toString());

    }
    for(int i=0;i<temperatureTime.size();i++){
        tempTime.append(temperatureTime.at(i).mid(11,5));   // Wyłuskanie godzin
    }

    qDebug()<<temperatureData.size();
    qDebug()<<tempTime.size();
    //qDebug()<<tempTime;
    //repaint();
    reply->deleteLater();

}

//void MainWindow::getChart(QChartView *s1){            //nieuzywane do wywalenia
//    qDebug("Odbieram cos");
//    //temperature = s1;
//    //temperature->setParent(ui->horizontalFrame);
//    update();
//    //usleep(3000000);*/
//    QLineSeries *series = new QLineSeries();
//    series->append(0,6);
//    series->append(2,1);
//    series->append(2,3);
//    series->append(5,8);
//    series->append(7,3);
//    *series << QPointF(0, 6) << QPointF(9, 4) << QPointF(15, 20) << QPointF(25, 12) << QPointF(29, 26);
//    QChart *chart = new QChart();
//    chart->legend()->hide();
//    chart->addSeries(series);
//    temperature = new QChartView(chart);

//    temperature->setParent(ui->horizontalFrame);
//    update();
//};





void MainWindow::on_actionConnect_triggered() // kazAdy kolejny triggered do kolejnych przycisków tylko zmiana danych co nizej
{
    chart->setData(tempTime,temperatureData,"Temperatura");
    ui->chartView->repaint();
    this->setCentralWidget(ui->chartView);
}
