#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QUrl myurl;
    myurl.setScheme("http");
    myurl.setHost("api.thingspeak.com");
    myurl.setPath("/channels/1057622/feeds.json");
    qDebug() << myurl.toString();
    QNetworkRequest request;
    request.setUrl(myurl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    restclient = new QNetworkAccessManager(this);
    QNetworkReply *reply = restclient->get(request);
    QObject::connect(restclient, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply *)));
    g = false;
    chart = new Chart();
}

MainWindow::~MainWindow()
{
    delete chart;
    delete restclient;
    delete ui;
}

void MainWindow::replyFinished(QNetworkReply *reply){
    QJsonDocument jsdoc;
    jsdoc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject jsobj = jsdoc.object();
    jsarr = jsobj["feeds"].toArray();
    qDebug()<<jsarr.size();
    foreach (const QJsonValue &value, jsarr) {
    QJsonObject jsob = value.toObject();
    qDebug() << jsob["entry_id"].toInt();
    qDebug() << jsob["field1"].toString();
    qDebug() << jsob["field2"].toString();
    qDebug() << jsob["field3"].toString();
    qDebug() << jsob["created_at"].toString();
    temperatureData.push_front(jsob["field1"].toString().toDouble());
    }
    qDebug()<<temperatureData.size();
    g = true;
    repaint();
    reply->deleteLater();

}

void MainWindow::paintEvent(QPaintEvent *event){
    Q_UNUSED(event)
    QPainter painter(this);
    chart->drawLinearGrid(painter, centralWidget()->geometry());
    if(g){
    chart->drawLinearData(painter, temperatureData);

    update();
    }
}
