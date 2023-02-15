#include "rubikclockwidget.h"
#include <QMessageBox>
#include "analogclockwidget.h"
#include <QDebug>

RubikClockWidget::RubikClockWidget(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(400, 400);
    setBaseSize(400,400);
    setWindowTitle(tr("Rubik-óra"));

    _newGameButton = new QPushButton(trUtf8("Új játék")); // új játék gomb
    connect(_newGameButton, SIGNAL(clicked()), this, SLOT(newGameButtonClicked()));

    _mainLayout = new QVBoxLayout(); // vertikális elhelyezkedés a teljes felületnek
    _mainLayout->addWidget(_newGameButton);

    _tableLayout = new QGridLayout(); // rácsos elhelyezkedés a játékmezőnek
    _mainLayout->addLayout(_tableLayout);

    generateTable();
    stepCount = 0;

    setLayout(_mainLayout);
}

void RubikClockWidget::generateTable()
{
    _gameTableClocks.resize(3);

    for (int i = 0; i < 3; ++i)
    {
        _gameTableClocks[i].resize(3);
        for (int j = 0; j < 3; ++j)
        {
            _gameTableClocks[i][j]= new AnalogClockWidget(this);
            _tableLayout->addWidget(_gameTableClocks[i][j], 2*i, 2*j); // gombok felvétele az elhelyezésbe
        }
    }
    _gameTableButtons.resize(2);
    for (int i = 0; i < 2; ++i)
    {
        _gameTableButtons[i].resize(2);
        for (int j = 0; j < 2; ++j)
        {
            _gameTableButtons[i][j]= new QPushButton(this);
            _gameTableButtons[i][j]->setFixedWidth(40);
            _tableLayout->addWidget(_gameTableButtons[i][j], 2*i+1, 2*j+1); // gombok felvétele az elhelyezésbe
            connect(_gameTableButtons[i][j], SIGNAL(clicked()), this, SLOT(buttonClicked()));
        }
    }
}


void RubikClockWidget::buttonClicked()
{
    // lekérjük az esemény küldőjét
    QPushButton* senderButton = dynamic_cast <QPushButton*> (sender());
    int location = _tableLayout->indexOf(senderButton);

    int y = (location +1)%2; // a gomb rácson belüli pozíciója megadja a koordinátákat
    int x = (location /11);

    _gameTableClocks[x+1][y+1]->add();
    _gameTableClocks[x+1][y]->add();
    _gameTableClocks[x][y+1]->add();
    _gameTableClocks[x][y]->add();

    ++stepCount;

    checkGame();
}

void RubikClockWidget::newGameButtonClicked()
{
    newGame();
}

void RubikClockWidget::newGame()
{
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            _gameTableClocks[i][j]->setH();

    stepCount = 0;
}

void RubikClockWidget::checkGame()
{
    bool won = true;

    for (int i = 0; i < 2 && won; ++i)
        for (int j = 0; j < 2 && won; ++j)
            if(_gameTableClocks[i][j]->getH() != 0)
                won = false;

    if (won)
    {
        QMessageBox::information(this, trUtf8("Játék vége!"), QString::number(stepCount) + trUtf8(" lépésben nyerte a játékot!"));
        newGame();
    }
}
