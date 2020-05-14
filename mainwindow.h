#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkReply>
#include <QPainter>
#include "chart.h"

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

private:
    Ui::MainWindow *ui;
    Chart *chart;
    QJsonArray jsarr;
    QVector<double> temperatureData;
     void paintEvent(QPaintEvent *event);
     bool g;
};
#endif // MAINWINDOW_H
