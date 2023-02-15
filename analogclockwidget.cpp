#include "analogclockwidget.h"

#include <QPainter>
#include "stdlib.h"

AnalogClockWidget::AnalogClockWidget(QWidget *parent) : QWidget(parent)
//  : QWidget(parent, Qt::FramelessWindowHint) // ha keret nélkül szeretnénk
{
    resize(200, 200);
    qsrand(qrand());
    setH();
}

void AnalogClockWidget::paintEvent(QPaintEvent *)
{
    // mutatók geometriája:
    QPoint hourTriangle[3] = { QPoint(7, 8), QPoint(-7, 8), QPoint(0, -70) };


    // mutatók és vonások színe:
    QColor hourColor(0, 0, 128); // szín RGB alapjánm
    QColor minuteColor(128, 0, 0, 150); // szín RGB és áttetszőség alapján

    QPainter painter(this); // festő objektum
    painter.setRenderHint(QPainter::Antialiasing); // élsimítást használ
    painter.translate(width() / 2, height() / 2); // transzformációk a rajzolás előtt
    painter.scale(height() / 200.0, height() / 200.0);

    // percjelek:
    painter.setPen(minuteColor);
    for (int j = 0; j < 60; ++j)
    {
        painter.drawLine(92, 0, 96, 0); // vonal kirajzolása
        painter.rotate(6.0); // forgatás 6 fokkal
    }
    // órajelek:
    painter.setPen(hourColor);
    for (int i = 0; i < 12; ++i)
    {
        painter.drawLine(88, 0, 96, 0);
        painter.rotate(30.0);
    }

    painter.save(); // rajzolási tulajdonságok elmentése
    painter.setPen(Qt::NoPen); // nincs toll
    painter.setBrush(hourColor); // ecset színe
    painter.rotate(30.0 * h); // mutató forgatása
    painter.drawConvexPolygon(hourTriangle, 3); // poligon kirajzolása az adott forgatás mellett
    painter.restore(); // rajzolás visszaállítása

}

void AnalogClockWidget::add() {
    ++h;
    h %= 12;
    update();
}

int AnalogClockWidget::getH()
{
    return h;
}

void AnalogClockWidget::setH()
{
    h = qrand() % 12;
    update();
}
