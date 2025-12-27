#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QTime>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    ui->centralwidget->installEventFilter(this);
    installEventFilter(this);

    setFixedSize(size());
    setWindowFlags(windowFlags()
                   | Qt::FramelessWindowHint
                   | Qt::WindowStaysOnTopHint);

    setAttribute(Qt::WA_TranslucentBackground, true);
    statusBar()->setSizeGripEnabled(false);

    ui->timeLabel->setText(QTime::currentTime().toString("hh:mm"));
    setLabelFont();

    auto *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this](){
        ui->timeLabel->setText(QTime::currentTime().toString("hh:mm"));
    });
    applyMainwindowSize();
    ui->timeLabel->setStyleSheet("color: white");
    timer->start(1000);
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_dragPos = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        move(event->globalPos() - m_dragPos);
        event->accept();
    }
}

void MainWindow::applyMainwindowSize()
{
    const QSize label = ui->timeLabel->sizeHint();
    const int pad = 16; // поля вокруг текста
    setFixedSize(label.width() + pad*2, label.height() + pad*2);
}

void MainWindow::setLabelFont()
{
    QFont f = ui->timeLabel->font();
    f.setPointSize(m_fontPt);
    ui->timeLabel->setFont(f);
}

void MainWindow::applyScale()
{
    setLabelFont();
    adjustSize();
    applyMainwindowSize();
    setFixedSize(size());
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent *key_event = static_cast<QKeyEvent*>(event);
        // Нажимаем букву T
        if(key_event->key() == Qt::Key_C)
        {
            if(color == WHITE)
            {
                ui->timeLabel->setStyleSheet("color: black");
                color = BLACK;
            }
            else
            {
                ui->timeLabel->setStyleSheet("color: white");
                color = WHITE;
            }
        }
        else if(key_event->key() == Qt::Key_Plus)
        {
            m_fontPt++;
            applyScale();
        }
        else if(key_event->key() == Qt::Key_Minus)
        {
            m_fontPt--;
            applyScale();
        }
        else if(key_event->key() == Qt::Key_F7)
        {
            QApplication::quit();
        }
        return true;
    }

//    if (event->type() == QEvent::MouseButtonPress) {
//        auto *me = static_cast<QMouseEvent*>(event);
//        if (me->button() == Qt::LeftButton) {
//            auto *w = qobject_cast<QWidget*>(watched);
//            if (!w) return false;

//            const QPoint gpos = w->mapToGlobal(me->pos());
//            m_dragPos = gpos - frameGeometry().topLeft();
//            return true;
//        }
//    }

//    if (event->type() == QEvent::MouseMove) {
//        auto *me = static_cast<QMouseEvent*>(event);
//        if (me->buttons() & Qt::LeftButton) {
//            auto *w = qobject_cast<QWidget*>(watched);
//            if (!w) return false;

//            const QPoint gpos = w->mapToGlobal(me->pos());
//            move(gpos - m_dragPos);
//            return true;
//        }
//    }

    return QMainWindow::eventFilter(watched, event);
}

MainWindow::~MainWindow()
{
    delete ui;
}

