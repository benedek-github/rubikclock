#ifndef ANALOGCLOCKWIDGET_H
#define ANALOGCLOCKWIDGET_H

#include <QWidget>

class AnalogClockWidget : public QWidget
{
    Q_OBJECT
public:
    AnalogClockWidget(QWidget *parent = 0);
    void add();
    int getH();
    void setH();
protected:
    void paintEvent(QPaintEvent *event); // kifestő esemény
    int h;
};

#endif
