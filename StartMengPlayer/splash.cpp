#include "splash.h"
int     Splash::i = 0;
Splash::Splash(QWidget *parent):QLabel(parent)
{
    setWindowFlags(Qt::Window |Qt::FramelessWindowHint |Qt::WindowStaysOnTopHint);

//    setAttribute(Qt::WA_TranslucentBackground);

    setMaximumSize(850, 450);
    setMinimumSize(850, 450);
    test = "";
    name = tr("M e n g M e n g M u s i c P l a y e r");
    list = name.split(" ");
    qDebug() << list;

    m_timer = new QTimer;
    m_timer->setInterval(1000);
    connect(m_timer, SIGNAL(timeout()),
            this, SLOT(slotTimeOut()));
    connect(this, SIGNAL(signalRepaintStop()),
            this, SLOT(slotRepaintStop()));

}

Splash::~Splash()
{

}

void Splash::slotTimeOut(void)
{
    i++;
    update();
}

void Splash::slotRepaintStart()
{
    m_timer->start();
}

void Splash::slotRepaintStop()
{
    m_timer->stop();
}

void Splash::paintEvent(QPaintEvent *)
{
    test.append(list.at(i));
    qDebug() << "text" << test;
    setText(test);
    QPainter painter(this);

    // 先绘制底层文字，作为阴影，这样会使显示效果更加清晰，且更有质感
    painter.setPen(QColor(0, 0, 0, 200));
    painter.drawText(1, 1, 800, 60, Qt::AlignHCenter, text());//中央对齐
    if(test == "MengMengPlayer")
    {
        emit signalRepaintStop();
    }
}
