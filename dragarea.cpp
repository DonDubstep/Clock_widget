#include "dragarea.h"

DragArea::DragArea(QWidget *parent) : QWidget(parent)
{
    // Чтобы область гарантированно ловила мышь даже при прозрачном окне,
    // делаем её чуть-чуть видимой (альфа > 0)
    setStyleSheet("background-color: rgba(0, 0, 0, 8);");
}

void DragArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_dragPos = event->globalPos() - window()->frameGeometry().topLeft();
        event->accept();
        return;
    }
    QWidget::mousePressEvent(event);
}

void DragArea::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        window()->move(event->globalPos() - m_dragPos);
        event->accept();
        return;
    }
    QWidget::mouseMoveEvent(event);
}
