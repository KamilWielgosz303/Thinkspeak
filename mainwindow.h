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
#include "chart.h"
#include "chart_draw.h"

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

public slots:
    void replyFinished(QNetworkReply *reply);
    void getChart(QChartView *s1);

private slots:
    void on_actionConnect_changed();

    void on_actionConnect_triggered();

private:
    Ui::MainWindow *ui;
    chart_draw *s;
    QChartView *temperature;
    Chart *chart;
    QJsonArray jsarr;
    QVector<double> temperatureData;
    QVector<QString> temperatureTime;
    QVector<QString> tempTime;
     void paintEvent(QPaintEvent *event);
     bool g;
};
#endif // MAINWINDOW_H
