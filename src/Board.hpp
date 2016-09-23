#pragma once

#include "common.hpp"

class Board : public QWidget {
protected:
    long dimension;
    GameData data;

    virtual void paintEvent(QPaintEvent *);

public:
    Board(QWidget *p=nullptr, Qt::WindowFlags wf=0);
    void redraw(long dimension, GameData data);
};
