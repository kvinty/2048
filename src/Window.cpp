#include "Window.hpp"

void Window::checkGameOver() {
    data[dimension].gameOver = true;
    for (long i = 0; i != dimension; ++i) {
        for (long j = 0; j != dimension; ++j) {
            if (data[dimension].values[i][j] == 0) {
                data[dimension].gameOver = false;
            }
        }
        for (long j = 0; j != dimension - 1; ++j) {
            if (data[dimension].values[i][j] == data[dimension].values[i][j + 1]) {
                data[dimension].gameOver = false;
            }
        }
        for (long j = 0; j != dimension - 1; ++j) {
            if (data[dimension].values[j][i] == data[dimension].values[j + 1][i]) {
                data[dimension].gameOver = false;
            }
        }
    }
}

void Window::addTile() {
    long temp[dimensionMax * dimensionMax];
    long count = 0;
    for (long i = 0; i != dimension; ++i) {
        for (long j = 0; j != dimension; ++j) {
            if (data[dimension].values[i][j] == 0) {
                temp[count++] = dimensionMax * i + j;
            }
        }
    }
    long tile = temp[qrand() % count];
    long val = 2;
    if (enable_tile_4 && qrand() % 100 < percentage_tile_4) {
        val = 4;
    }
    data[dimension].values[tile / dimensionMax][tile % dimensionMax] = val;
}

void Window::restart() {
    data[dimension].gameOver = false;
    data[dimension].score = 0;
    for (long i = 0; i != dimension; ++i) {
        for (long j = 0; j != dimension; ++j) {
            data[dimension].values[i][j] = 0;
        }
    }
    addTile();
    addTile();
}

void Window::drop(int key) {
    GameData temp = dataOld[dimension];
    dataOld[dimension] = data[dimension];
    bool moved = false;

    if (key == Qt::Key_Down) {
        for (long i = 0; i != dimension; ++i) {
            long last = dimension;
            long lastTile = -1;
            for (long j = dimension - 1; j >= 0; --j) {
                if (data[dimension].values[i][j]) {
                    if (data[dimension].values[i][j] == lastTile) {
                        data[dimension].values[i][last] *= 2;
                        data[dimension].score += data[dimension].values[i][last];
                        lastTile = -1;
                        data[dimension].values[i][j] = 0;
                        moved = true;
                    } else {
                        --last;
                        lastTile = data[dimension].values[i][j];
                        if (j != last) {
                            data[dimension].values[i][last] = data[dimension].values[i][j];
                            data[dimension].values[i][j] = 0;
                            moved = true;
                        }
                    }
                }
            }
        }
    } else if (key == Qt::Key_Left) {
        for (long i = 0; i != dimension; ++i) {
            long last = -1;
            long lastTile = -1;
            for (long j = 0; j != dimension; ++j) {
                if (data[dimension].values[j][i]) {
                    if (data[dimension].values[j][i] == lastTile) {
                        data[dimension].values[last][i] *= 2;
                        data[dimension].score += data[dimension].values[last][i];
                        lastTile = -1;
                        data[dimension].values[j][i] = 0;
                        moved = true;
                    } else {
                        ++last;
                        lastTile = data[dimension].values[j][i];
                        if (j != last){
                            data[dimension].values[last][i] = data[dimension].values[j][i];
                            data[dimension].values[j][i] = 0;
                            moved = true;
                        }
                    }
                }
            }
        }
    } else if (key == Qt::Key_Right) {
        for (long i = 0; i != dimension; ++i) {
            long last = dimension;
            long lastTile = -1;
            for (long j = dimension - 1; j >= 0 ; --j) {
                if (data[dimension].values[j][i]) {
                    if (data[dimension].values[j][i] == lastTile) {
                        data[dimension].values[last][i] *= 2;
                        data[dimension].score += data[dimension].values[last][i];
                        lastTile = -1;
                        data[dimension].values[j][i] = 0;
                        moved = true;
                    } else {
                        --last;
                        lastTile = data[dimension].values[j][i];
                        if (j != last) {
                            data[dimension].values[last][i] = data[dimension].values[j][i];
                            data[dimension].values[j][i] = 0;
                            moved = true;
                        }
                    }
                }
            }
        }
    } else if (key == Qt::Key_Up) {
        for (long i = 0; i != dimension; ++i) {
            long last = -1;
            long lastTile = -1;
            for (long j = 0; j != dimension; ++j) {
                if (data[dimension].values[i][j]) {
                    if (data[dimension].values[i][j] == lastTile) {
                        data[dimension].values[i][last] *= 2;
                        data[dimension].score += data[dimension].values[i][last];
                        lastTile = -1;
                        data[dimension].values[i][j] = 0;
                        moved = true;
                    } else {
                        ++last;
                        lastTile = data[dimension].values[i][j];
                        if (j != last) {
                            data[dimension].values[i][last] = data[dimension].values[i][j];
                            data[dimension].values[i][j] = 0;
                            moved = true;
                        }
                    }
                }
            }
        }
    }

    if (moved) {
        addTile();
        checkGameOver();
        scoreLabel->setDrawnText(QString::number(data[dimension].score));
        board->redraw(dimension, data[dimension]);
    } else {
        dataOld[dimension] = temp;
    }
}

void Window::keyPressEvent(QKeyEvent *e) {
    if (e->key() == Qt::Key_F11) {
        fullScreen = !fullScreen;
        setWindowState(fullScreen ? Qt::WindowFullScreen : Qt::WindowNoState);
    } else {
        drop(e->key());
    }
}

Window::Window(QWidget *p, Qt::WindowFlags wf) : QWidget(p, wf) {
    resize(470, 620);
    setMinimumSize(470, 620);
    QRect screen = QDesktopWidget().screenGeometry();
    int cornerX = (screen.width() - geometry().width()) / 2;
    int cornerY = (screen.height() - geometry().height()) / 2;
    move(cornerX, cornerY);
    setWindowTitle("2048");
    setWindowIcon(QIcon(":/icon.png"));

    restartButton = new DrawnWidget("Restart", neutralButtonColor, this);
    QObject::connect(restartButton, SIGNAL(clicked()), SLOT(slotRestart()));
    undoButton = new DrawnWidget("Undo", neutralButtonColor, this);
    QObject::connect(undoButton, SIGNAL(clicked()), SLOT(slotUndo()));
    scoreLabel = new DrawnWidget("0", neutralButtonColor, this);
    QHBoxLayout *firstRow = new QHBoxLayout;
    firstRow->addWidget(restartButton, Qt::AlignCenter);
    firstRow->addWidget(undoButton, Qt::AlignCenter);
    firstRow->addWidget(scoreLabel, Qt::AlignCenter);

    QHBoxLayout *secondRow = new QHBoxLayout;
    for (long i = dimensionMin; i <= dimensionMax; ++i) {
        sizeButton[i] = new DrawnWidget(QString::number(i), neutralButtonColor, this);
        QObject::connect(sizeButton[i], SIGNAL(clicked()), SLOT(slotSize()));
        secondRow->addWidget(sizeButton[i], Qt::AlignCenter);
    }

    board = new Board(this);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(20);
    layout->setSpacing(20);
    layout->addLayout(firstRow, 1);
    layout->addLayout(secondRow, 1);
    layout->addWidget(board, 8);
    setLayout(layout);
    qsrand(QTime(0, 0, 0).msecsTo(QTime::currentTime()));
    for (dimension = dimensionMin; dimension <= dimensionMax; ++dimension) {
        restart();
        dataOld[dimension] = data[dimension];
    }
    dimension = dimensionDefault;
    sizeButton[dimension]->setDrawnColor(brightButtonColor);
    scoreLabel->setDrawnText(QString::number(data[dimension].score));
    board->redraw(dimension, data[dimension]);
}

void Window::slotRestart() {
    restart();
    dataOld[dimension] = data[dimension];
    scoreLabel->setDrawnText(QString::number(data[dimension].score));
    board->redraw(dimension, data[dimension]);
}

void Window::slotUndo() {
    data[dimension] = dataOld[dimension];
    scoreLabel->setDrawnText(QString::number(data[dimension].score));
    board->redraw(dimension, data[dimension]);
}

void Window::slotSize() {
    DrawnWidget *newSize = static_cast<DrawnWidget *>(sender());
    newSize->setDrawnColor(brightButtonColor);
    sizeButton[dimension]->setDrawnColor(neutralButtonColor);
    dimension = newSize->getDrawnText().toInt();
    scoreLabel->setDrawnText(QString::number(data[dimension].score));
    board->redraw(dimension, data[dimension]);
}
