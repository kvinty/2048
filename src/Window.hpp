#pragma once

#include "DrawnWidget.hpp"
#include "Board.hpp"

class Window : public QWidget {
    Q_OBJECT

protected:
    bool fullScreen = false;
    long dimension;
    GameData dataOld[dimensionMax + 1];
    GameData data[dimensionMax + 1];
    DrawnWidget *restartButton;
    DrawnWidget *undoButton;
    DrawnWidget *scoreLabel;
    DrawnWidget *sizeButton[dimensionMax + 1];
    Board *board;

    void checkGameOver();
    void addTile();
    void restart();
    void drop(int key);

    virtual void keyPressEvent(QKeyEvent *e);

public:
    Window(QWidget *p=nullptr, Qt::WindowFlags wf=0);

public slots:
    void slotRestart();
    void slotUndo();
    void slotSize();
};
