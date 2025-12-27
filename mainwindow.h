#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTimer>
#include <QTime>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum color_enum
{
    WHITE,
    BLACK,
    CUSTOM
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    void readJson();
    void setCustomColor(QString custom_color_parse);
    void applyScale();
    void applyMainwindowSize();
    void setLabelFont();
    void rememberToJson();
    void setColor();
    void changeColor();

    bool eventFilter(QObject *watched, QEvent *event) override;
private:
    Ui::MainWindow *ui;
    QPoint m_dragPos;
    int color;
    int m_fontPt;
    QString custom_color_parse;

};
#endif // MAINWINDOW_H
