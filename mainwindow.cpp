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
        chart->setData(temperatureTime,temperatureData,"Temperature [°C]");
        }
        if(ui->actionHumidity->isChecked()){
            chart->setData(temperatureTime,humidityData,"Humidity [%]");
        }
        if(ui->actionPressure->isChecked()){
            chart->setData(temperatureTime,pressureData,"Pressure [kPa]");
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
    if(ui->actionConnect->isChecked()){
        ui->actionconnectIcon->setIcon(QIcon(":/new/icons/icons/greenicon.png"));
        ui->actionconnectIcon->setIconVisibleInMenu(false);
        thread.start(thread.HighestPriority);
    }
    else{
        ui->actionconnectIcon->setIcon(QIcon(":/new/icons/icons/redicon.png"));
        if (thread.isRunning()){
            thread.terminate();
        }
    }
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
