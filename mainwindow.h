#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <unistd.h>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkReply>
#include <QPainter>
#include <QObject>
#include <QMessageBox>
#include "_def.h"
#include "chart.h"
#include "thread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QNetworkAccessManager *restclient;
    QLinearGradient windowGradient;

private slots:
    void on_actionConnect_triggered();
    void replyFinished(QNetworkReply * reply);
    void getThinkspeakData();
    void updateChart();
    void on_actionTemperature_triggered();
    void on_actionHumidity_triggered();
    void on_actionPressure_triggered();

private:
    Ui::MainWindow *ui;
    Chart *chart;
    QVector<double> temperatureData;
    QVector<QString> temperatureTime;
    QVector<double> humidityData;
    QVector<double> pressureData;
    Thread thread;
    QNetworkReply *reply;
    QNetworkRequest request;
};
#endif // MAINWINDOW_H
