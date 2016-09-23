#pragma once

#include "common.hpp"

class DrawnWidget : public QWidget {
    Q_OBJECT

protected:
    QString text;
    QColor color;

    virtual void paintEvent(QPaintEvent *);
    virtual void mousePressEvent(QMouseEvent *e);

public:
    DrawnWidget(QString text, QColor color,
    QWidget *p=nullptr, Qt::WindowFlags wf=0);
    QString getDrawnText() const;
    QColor getDrawnColor() const;
    void setDrawnText(QString text);
    void setDrawnColor(QColor color);

signals:
    void clicked();
};
