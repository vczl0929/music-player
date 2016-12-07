#include "musicwidget.h"
#include "startwidget.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartWidget z;

    MusicWidget w;
    w.setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
    w.show();



    return a.exec();
}
