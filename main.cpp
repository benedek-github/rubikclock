#include <QApplication>
#include "rubikclockwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    RubikClockWidget widget;
    widget.show();

    return a.exec();
}
