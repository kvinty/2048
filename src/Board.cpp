#include "Board.hpp"

void Board::paintEvent(QPaintEvent *) {
    int boardSize = qMin(width(), height());
    QRect widget((width() - boardSize) / 2, (height() - boardSize) / 2, boardSize, boardSize);
    double part = boardSize / (12 * dimension + 1.0);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(boardBackgroundColor);
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(widget, 10, 10);

    for (long i = 0; i != dimension; ++i) {
        for (long j = 0; j != dimension; ++j) {
            QRect region(round((width() - boardSize) / 2.0 + part + 12 * part * i), round((height() - boardSize) / 2.0 + part + 12 * part * j), round(11 * part), round(11 * part));
            painter.setPen(Qt::NoPen);
            if (data.values[i][j]) {
                QColor supposedColor = tileColor[data.values[i][j]];
                painter.setBrush(supposedColor != tileColor[0] ? supposedColor : tileColor[8192]);
                painter.drawRoundedRect(region, 10, 10);
                painter.setPen(tileTextColor);
                painter.setFont(QFont(gameFont, fontSize[dimension]));
                painter.drawText(region, Qt::AlignCenter, QString::number(data.values[i][j]));
            }
            else {
                painter.setBrush(emptyTileColor);
                painter.drawRoundedRect(region, 10, 10);
            }
        }
    }

    if (data.gameOver) {
        painter.setBrush(shadowColor);
        painter.setPen(Qt::NoPen);
        painter.drawRoundedRect(widget, 10, 10);
        painter.setPen(blackColor);
        painter.setFont(QFont(gameFont, 48));
        painter.drawText(widget, Qt::AlignCenter, "Game Over!");
    }

    painter.end();
}

Board::Board(QWidget *p, Qt::WindowFlags wf) : QWidget(p, wf) {
}

void Board::redraw(long dimension, GameData data) {
    this->dimension = dimension;
    this->data = data;
    update();
}
