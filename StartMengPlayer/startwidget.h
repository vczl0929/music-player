#ifndef STARTWIDGET_H
#define STARTWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QMediaPlayer>
#include <QElapsedTimer>
#include <QSplashScreen>
#include <QPropertyAnimation>

class StartWidget : public QWidget
{
    Q_OBJECT
signals:
    void signalRepaintStart();


public:
    StartWidget(QWidget *parent = 0);
    ~StartWidget();

    void MyDelayTime();
    void Repaint(double delayTime,QPixmap &pixmap);

private:
    QMediaPlayer *m_startplayer;
    QSplashScreen *screen;
    QElapsedTimer timer;
};

#endif // STARTWIDGET_H
