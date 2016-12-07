#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QWidget>
#include <QModelIndex>
#include <QPropertyAnimation>
#include "musicplayer.h"
#include "runtimeinfo.h"


namespace Ui {
class PlayList;
}

class PlayList : public QWidget
{
    Q_OBJECT

signals:
    void signalMusicIndex(int);

public:
    explicit PlayList(QWidget *parent = 0);
    ~PlayList();

public slots:
    void slotSongsNameList(QStringList *songsNameList);

    void slotHidePlayListWidget(QPoint eventPos);
    void slotBluePlayList();
    void slotRedPlayList();
    void slotGreenPlayList();


private slots:
    void on_lw_songsList_doubleClicked(const QModelIndex &index);

    void on_pb_playList_close_clicked();

private:
    Ui::PlayList *ui;
};

#endif // PLAYLIST_H
