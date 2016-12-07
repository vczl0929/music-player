#include "startwidget.h"
#include <QUrl>

StartWidget::StartWidget(QWidget *parent)
    : QWidget(parent)
{
    m_startplayer = new QMediaPlayer;

    screen = new QSplashScreen;
    m_startplayer->setMedia(QUrl("../FileDatas/programmer.mp3"));
    m_startplayer->setVolume(90);
    m_startplayer->play();

    QPixmap pixmap(":/start/skins/start/start.png");
    setWindowFlags(Qt::WindowStaysOnTopHint);//置顶
    screen->setPixmap(pixmap);
    screen->show();

    MyDelayTime();
    m_startplayer->pause();
    screen->close();
}

StartWidget::~StartWidget()
{
    delete m_startplayer;
}

void  StartWidget::MyDelayTime()
{
    QPixmap pixmap1(":/start/skins/start/1.png");
    QPixmap pixmap2(":/start/skins/start/2.png");
    QPixmap pixmap3(":/start/skins/start/3.png");
    QPixmap pixmap4(":/start/skins/start/4.png");
    QPixmap pixmap5(":/start/skins/start/5.png");
    QPixmap pixmap6(":/start/skins/start/6.png");
    QPixmap pixmap7(":/start/skins/start/7.png");
    QPixmap pixmap8(":/start/skins/start/8.png");
    QPixmap pixmap9(":/start/skins/start/9.png");
    QPixmap pixmap10(":/start/skins/start/10.png");
    QPixmap pixmap11(":/start/skins/start/11.png");
    QPixmap pixmap12(":/start/skins/start/12.png");
    QPixmap pixmap13(":/start/skins/start/13.png");
    QPixmap pixmap14(":/start/skins/start/14.png");
    QPixmap pixmap15(":/start/skins/start/15.png");
    QPixmap pixmap16(":/start/skins/start/16.png");
    QPixmap pixmap17(":/start/skins/start/17.png");
    QPixmap pixmap18(":/start/skins/start/18.png");
    QPixmap pixmap19(":/start/skins/start/ALL.png");

    timer.start();

    Repaint(1.0,pixmap1);
    Repaint(1.1,pixmap2);
    Repaint(1.2,pixmap3);
    Repaint(1.3,pixmap4);
    Repaint(1.5,pixmap5);
    Repaint(1.6,pixmap6);
    Repaint(1.7,pixmap7);
    Repaint(1.8,pixmap8);
    Repaint(2.0,pixmap9);
    Repaint(2.1,pixmap10);
    Repaint(2.2,pixmap11);
    Repaint(2.3,pixmap12);
    Repaint(2.4,pixmap13);
    Repaint(2.5,pixmap14);
    Repaint(2.6,pixmap15);
    Repaint(2.7,pixmap16);
    Repaint(2.8,pixmap17);
    Repaint(2.9,pixmap18);
    Repaint(3.0,pixmap19);

    double delayTime;
    delayTime = 4.0;
    while(timer.elapsed() < (delayTime * 1000));
}

void StartWidget::Repaint(double delayTime,QPixmap &pixmap)
{
    while(timer.elapsed() < (delayTime * 1000));
    screen->setPixmap(pixmap);
    screen->repaint();
}
