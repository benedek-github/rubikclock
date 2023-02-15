#ifndef RubikClockWIDGET_H
#define RubikClockWIDGET_H

#include <QWidget>
#include <QVector>
#include <QPushButton>
#include <QGridLayout>
#include "analogclockwidget.h"

class RubikClockWidget : public QWidget // játékot megjelenítő ablak
{
    Q_OBJECT

public:
    RubikClockWidget(QWidget *parent = 0);

private slots:
    void buttonClicked(); // táblagombra kattintás esménykezelője
    void newGameButtonClicked(); // új játék gombra kattintás eseménykezelője

private:
    void newGame();
    void generateTable(); // tábla létrehozása
    void checkGame();

    int stepCount;
    QGridLayout* _tableLayout;
    QVBoxLayout* _mainLayout;
    QPushButton* _newGameButton; // új játék gombja
    QVector<QVector<AnalogClockWidget*> > _gameTableClocks; // gombtábla
    QVector<QVector<QPushButton*> > _gameTableButtons; // gombtábla
};

#endif // RubikClockWIDGET_H
