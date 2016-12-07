#ifndef SPLASH_H
#define SPLASH_H
#include <QLabel>
#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <QStringList>

class Splash : public QLabel
{
    Q_OBJECT

signals:
    void signalRepaintStop();
public:
    explicit Splash(QWidget *parent = 0);
    ~Splash();
    QString test;
    QString name;
    QStringList list;
    static int i;
public slots:
    void slotTimeOut(void);
    void slotRepaintStart();
    void slotRepaintStop();

protected:
    void paintEvent(QPaintEvent *);

private:
     QTimer *m_timer;

};

#endif // SPLASH_H
