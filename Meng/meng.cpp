#include "meng.h"
#include "ui_meng.h"

#include <QPainter>
#include <QDebug>
#include <QVector>
#include <QTimer>
#include <QTime>
#include <QPoint>
#include <QRectF>
#include <QtMath>

Meng::Meng(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Meng)
{
    m_angle_second = 0;
    ui->setupUi(this);
    m_timer = new QTimer;
    m_timer->setInterval(200);
    connect(m_timer, SIGNAL(timeout()),
            this, SLOT(slotTimeOut()));
}

Meng::~Meng()
{
    delete ui;
}

void Meng::slotTimeOut(void)
{
    m_angle_second += 1;
    if (m_angle_second >= 360)
    {
        m_angle_second -= 360;
    }
    update();
}

void Meng::slotMengStart()
{
    m_timer->start();
}

void Meng::slotMengStop()
{
    m_timer->stop();
}

void Meng::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::SmoothPixmapTransform);

    QPixmap pixmap1(":/common/skins/common/meng1.png");
    QRectF target1(0,0, 300, 300);
    QRectF source1(0, 0, 300, 300);

    QPixmap pixmap2(":/common/skins/common/meng2.png");
    QRectF target2(0,0, 300, 300);
    QRectF source2(0, 0, 300, 300);

    QPixmap pixmap3(":/common/skins/common/meng3.png");
    QRectF target3(0,0, 300, 300);
    QRectF source3(0, 0, 300, 300);

    QPixmap pixmap4(":/common/skins/common/meng4.png");
    QRectF target4(0,0, 300, 300);
    QRectF source4(0, 0, 300, 300);

    QPixmap pixmap5(":/common/skins/common/meng5.png");
    QRectF target5(0,0, 300, 300);
    QRectF source5(0, 0, 300, 300);

    QRectF target(0,0, 300, 132);
    QRectF source(0, 0, 300, 132);
    QImage image(":/common/skins/common/stylus.png");

    qreal x = 0.0;
    qreal y = 0.0;
    qint64 r = 150;

    qreal k = qTan(qDegreesToRadians(m_angle_second+45));

    if((m_angle_second > 45) && (m_angle_second < 225))
    {
        x = r + r * qSqrt(2) / qSqrt(1 + qPow(k,2));
        y = r + k * r * qSqrt(2) / qSqrt(1 + qPow(k,2));
    }else if(((m_angle_second > 225) && (m_angle_second <= 360))
             || ((m_angle_second > 0) && (m_angle_second < 45)))
    {
        x = r - r * qSqrt(2) / qSqrt(1 + qPow(k,2));
        y = r - k * r * qSqrt(2) / qSqrt(1 + qPow(k,2));
    }else if(m_angle_second == 45)
    {
        x = r;
        y = (1 - qSqrt(2)) * r;
    }else if(m_angle_second == 225)
    {
        x = r;
        y = (1 + qSqrt(2)) * r;
    }

    QPoint point(x,y + 60);

    p.save();
    p.translate(point);
    p.rotate(m_angle_second);
    switch (RunTimeInfo::getMengFlag()) {
    case 0:
        p.drawPixmap(target1,pixmap1,source1);
        break;
    case 1:
        p.drawPixmap(target2,pixmap2,source2);
        break;
    case 2:
        p.drawPixmap(target3,pixmap3,source3);
        break;
    case 3:
        p.drawPixmap(target4,pixmap4,source4);
        break;
    case 4:
        p.drawPixmap(target5,pixmap5,source5);
        break;
    default:
        break;
    }

    p.restore();

    p.drawImage(target, image, source);
}
