#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), temperatureData(100), temperatureTime(100), humidityData(100), pressureData(100)
{
    ui->setupUi(this);
    ui->chartView->setRenderHint(QPainter::Antialiasing);
    chart = new Chart();
    ui->chartView->setChart(chart->chart);

    QUrl myurl;
    this->setCentralWidget(ui->horizontalFrame);
    myurl.setScheme("http");
    myurl.setHost("api.thingspeak.com");
    myurl.setPath("/channels/1057622/feeds.json");
    restclient = new QNetworkAccessManager(this);
    connect(restclient, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply *)));
    connect(&thread, SIGNAL(tick()), this, SLOT(getThinkspeakData()));

    request.setUrl(myurl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

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
      reply = restclient->get(request);
      updateChart();
}


void MainWindow::replyFinished(QNetworkReply * reply){
    humidityData.clear();
    pressureData.clear();
    temperatureData.clear();
    temperatureTime.clear();
    QJsonDocument jsdoc;
    jsdoc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject jsobj = jsdoc.object();
    jsarr = jsobj["feeds"].toArray();
    qDebug()<<jsarr.size();
    foreach (const QJsonValue &value, jsarr) {
        QJsonObject jsob = value.toObject();
        temperatureData.push_front(jsob["field1"].toString().toDouble());
        temperatureTime.push_front(jsob["created_at"].toString());
        humidityData.push_front(jsob["field2"].toString().toDouble());
        pressureData.push_front(jsob["field3"].toString().toDouble());

    }
    qDebug()<<temperatureData.size();
    reply->deleteLater();

}

void MainWindow::updateChart(){
    if(ui->actionConnect->isChecked()){
        if(ui->actionTemperature->isChecked()){
        chart->setData(temperatureTime,temperatureData,"Temperature");
        }
        if(ui->actionHumidity->isChecked()){
            chart->setData(temperatureTime,humidityData,"Humidity");
        }
        if(ui->actionPressure->isChecked()){
            chart->setData(temperatureTime,pressureData,"Pressure");
        }
        ui->chartView->repaint();
        ui->temp_label->setText(QString::number(temperatureData.at(0))+ " °C");
        ui->time_label->setText(chart->getActualTime().mid(0,10)+ QString(" ") + chart->getActualTime().mid(11,8));
        ui->hum_label->setText(QString::number(humidityData.at(0)) + "%");
        ui->pres_label->setText(QString::number(pressureData.at(0))+" kPa");
    }

}

void MainWindow::on_actionConnect_triggered()
{
    updateChart();
    if(ui->actionConnect->isChecked()){
        ui->actionconnectIcon->setIcon(QIcon(":/new/icons/icons/greenicon.png"));
        ui->actionconnectIcon->setIconVisibleInMenu(false);
    }
    else
        ui->actionconnectIcon->setIcon(QIcon(":/new/icons/icons/redicon.png"));

}

void MainWindow::on_actionTemperature_triggered()
{
    ui->actionHumidity->setChecked(false);
    ui->actionPressure->setChecked(false);
    updateChart();
}

void MainWindow::on_actionHumidity_triggered()
{
    ui->actionTemperature->setChecked(false);
    ui->actionPressure->setChecked(false);
    updateChart();
}

void MainWindow::on_actionPressure_triggered()
{
    ui->actionTemperature->setChecked(false);
    ui->actionHumidity->setChecked(false);
    updateChart();
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





//void MainWindow::on_actionConnect_triggered() // kazAdy kolejny triggered do kolejnych przycisków tylko zmiana danych co nizej
//{

//}
