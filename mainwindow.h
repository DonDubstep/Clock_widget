#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum color_enum
{
    WHITE,
    BLACK
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    void applyScale();
    void applyMainwindowSize();
    void setLabelFont();

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;
private:
    Ui::MainWindow *ui;
    QPoint m_dragPos;
    int color = WHITE;
    int m_fontPt = 20;

};
#endif // MAINWINDOW_H
