#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QUrl myurl;
    s = new Chart();
    myurl.setScheme("http");
    myurl.setHost("api.thingspeak.com");
    myurl.setPath("/channels/1057622/feeds.json");
    //qDebug() << myurl.toString();
    QNetworkRequest request;
    request.setUrl(myurl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    restclient = new QNetworkAccessManager(this);
    QNetworkReply *reply = restclient->get(request);
    connect(restclient, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply *)));
    g = false;
    chart = new Chart();


}

MainWindow::~MainWindow()
{
    delete s;
    delete chart;
    delete restclient;
    delete ui;
}

void MainWindow::replyFinished(QNetworkReply *reply){
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
        tempTime.append(temperatureTime.at(i).mid(11,8));   // Wyłuskanie godzin
    }

    qDebug()<<temperatureData.size();
    qDebug()<<tempTime.size();
    //qDebug()<<tempTime;
    g = true;
    //repaint();
    reply->deleteLater();

}


void MainWindow::paintEvent(QPaintEvent *event){
    /*Q_UNUSED(event)
    QPainter painter(this);
    chart->drawLinearGrid(painter, centralWidget()->geometry());
    if(g){
    chart->drawLinearData(painter, temperatureData);
    update();
    if(ui->actionConnect->isChecked()){
        s-> drawTemp(temperatureData,tempTime);
    }*/
}

void MainWindow::getChart(QChartView *s1){            //Slot do odbierania sygnału z wykresem
    qDebug("Odbieram cos");
    //temperature = s1;
    //temperature->setParent(ui->horizontalFrame);
    update();
    //usleep(3000000);*/
    QLineSeries *series = new QLineSeries();          //Druga wersja wykresu prostsza ale itak nie dziala
    series->append(0,6);
    series->append(2,1);
    series->append(2,3);
    series->append(5,8);
    series->append(7,3);
    *series << QPointF(0, 6) << QPointF(9, 4) << QPointF(15, 20) << QPointF(25, 12) << QPointF(29, 26);
    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    temperature = new QChartView(chart);
    temperature->setRenderHint(QPainter::Antialiasing);
    temperature->setParent(ui->horizontalFrame);
    update();
};





void MainWindow::on_actionConnect_triggered()
{
    //s-> drawTemp(temperatureData,tempTime);
    ui->chartView->setChart(s->chart);
    ui->chartView->show();
}
