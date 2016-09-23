#include "DrawnWidget.hpp"

void DrawnWidget::paintEvent(QPaintEvent *) {
    QRect widget(0, 0, width(), height());
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(color);
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(widget, 10, 10);
    painter.setPen(tileTextColor);
    painter.setFont(QFont(gameFont, 24));
    painter.drawText(widget, Qt::AlignCenter, text);
    painter.end();
}

void DrawnWidget::mousePressEvent(QMouseEvent *e) {
    if (e->button() == Qt::LeftButton) {
        emit clicked();
    }
}

DrawnWidget::DrawnWidget(QString text, QColor color, QWidget *p,
Qt::WindowFlags wf)
: QWidget(p, wf) {
    this->text = text;
    this->color = color;
    update();
}

QString DrawnWidget::getDrawnText() const {
    return text;
}

QColor DrawnWidget::getDrawnColor() const {
    return color;
}

void DrawnWidget::setDrawnText(QString text) {
    this->text = text;
    update();
}

void DrawnWidget::setDrawnColor(QColor color) {
    this->color = color;
    update();
}
