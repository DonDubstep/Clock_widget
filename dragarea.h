#pragma once
#include <QWidget>
#include <QPoint>

class DragArea : public QWidget
{
    Q_OBJECT
public:
    explicit DragArea(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QPoint m_dragPos;
};
