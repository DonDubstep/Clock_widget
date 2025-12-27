#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    ui->centralwidget->installEventFilter(this);
    installEventFilter(this);
    readJson();

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
    setColor();
    applyMainwindowSize();
    timer->start(1000);
}

void MainWindow::setColor()
{
    if(color == WHITE)
    {
        ui->timeLabel->setStyleSheet("color: white");
    }
    else if (color == BLACK)
    {
        ui->timeLabel->setStyleSheet("color: black");
    }
    else if(color == CUSTOM)
    {
        setCustomColor(custom_color_parse);
    }
}

void MainWindow::changeColor()
{
    if(color == WHITE)
    {
        ui->timeLabel->setStyleSheet("color: black");
        color = BLACK;
    }
    else if (color == BLACK)
    {
        setCustomColor(custom_color_parse);
        color = CUSTOM;
    }
    else if(color == CUSTOM)
    {
        ui->timeLabel->setStyleSheet("color: white");
        color = WHITE;
    }
}

void MainWindow::setCustomColor(QString custom_color_parse)
{
    QStringList rgb_list = custom_color_parse.split(',', QString::SkipEmptyParts);
    int r = rgb_list[0].toInt();
    int g = rgb_list[1].toInt();
    int b = rgb_list[2].toInt();
    QString css_str = "color: rgb(" + QString::number(r) + "," + QString::number(g) + "," + QString::number(b) + ")";
    ui->timeLabel->setStyleSheet(css_str);
}

void MainWindow::readJson()
{
    QFile file(QCoreApplication::applicationDirPath() + "/src/CONFIG.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        qWarning("Не открыть файл");
    QByteArray raw_data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(raw_data);
    QJsonObject root = doc.object();

    int color_parse = root["last_color"].toInt();
    m_fontPt = root["last_size"].toInt();
    custom_color_parse = root["custom_color"].toString();
    QString position_parse = root["last_pos"].toString();
    QStringList position_str_list = position_parse.split(',', QString::SkipEmptyParts);
    int pos_x = position_str_list[0].toInt();
    int pos_y = position_str_list[1].toInt();
    this->move(QPoint(pos_x, pos_y));
    color = color_parse;

    file.close();
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
            changeColor();
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
            rememberToJson();
            QApplication::quit();
        }
        return true;
    }

    return QMainWindow::eventFilter(watched, event);
}

#include <QDebug>
void MainWindow::rememberToJson()
{
    QFile file(QCoreApplication::applicationDirPath() + "/src/CONFIG.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        qWarning("Не открыть файл");
    QByteArray raw_data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(raw_data);
    QJsonObject root = doc.object();
    file.close();

     if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
         qWarning("Не открыть файл");

    root["last_color"] = color;
    root["last_size"] = m_fontPt;
    root["custom_color"] = custom_color_parse;

    QPoint position = this->pos();
    root["last_pos"] = QString::number(position.x()) + ", " + QString::number(position.y());

    doc.setObject(root);
    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();
}



MainWindow::~MainWindow()
{
    delete ui;
}

