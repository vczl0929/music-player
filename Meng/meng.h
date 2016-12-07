#ifndef MENG_H
#define MENG_H

#include <QWidget>

#include "runtimeinfo.h"

class QTimer;

namespace Ui {
class Meng;
}

class Meng : public QWidget
{
    Q_OBJECT

public:
    explicit Meng(QWidget *parent = 0);
    ~Meng();

public slots:
    void slotTimeOut(void);
    void slotMengStart();
    void slotMengStop();

protected:
    void paintEvent(QPaintEvent *);

private:
    Ui::Meng *ui;

    QTimer *m_timer;

    qreal m_angle_second;

};

#endif // MENG_H
