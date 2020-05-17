#ifndef CHART_DRAW_H
#define CHART_DRAW_H
#include <QChar>
#include "ui_mainwindow.h"

class chart_draw
{
public:
    chart_draw();
    void drawTemp(QVector<double> data,QVector<QString> time,QMainWindow *wind);
};
#endif // CHART_DRAW_H
