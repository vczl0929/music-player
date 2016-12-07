#ifndef MUSICWIDGET_H
#define MUSICWIDGET_H

#include <QWidget>
#include <musicplayer.h>
#include "settingwidget.h"
#include <QMouseEvent>
#include "songsfile.h"
#include "playlist.h"
#include "runtimeinfo.h"
#include <QScrollBar>
#include <QTimer>

namespace Ui {
class MusicWidget;
}

enum PlayMode
{
    CurrentItemInLoop = 0, //单曲循环
    Sequential,            //顺序播放
    Loop,                  //列表循环
    Random                 //随机播放
};

class MusicWidget : public QWidget
{
    Q_OBJECT

signals:
    void signalSongsNameList(QStringList *);
    void signalConnectCurrentMediaChanged();
    void signalPlayListPosition(QPoint);
    void signalMengStart();
    void signalMengStop();
    void signalHidePlayListWidget(QPoint);
    void signalHideSettingWidget(QPoint);
    void signalBluePlayList();
    void signalRedPlayList();
    void signalGreenPlayList();

public:
    explicit MusicWidget(QWidget *parent = 0);
    ~MusicWidget();

    void initWidgetUnits(void);
    void updateLyricInfo(quint64 time);
    void getCurrentSongLyricAndInitUI();
    void sliderMovedUpdateLyricInfo(int time);
    void showLyrics(quint64 time);
    void skinsChanged(QString file);
    void setRunTimeBlueSkin();
    void setRunTimeRedSkin();
    void setRunTimeGreenSkin();
    void switchSkin();

public slots:
    void slotPositionChanged(QString updateTime);
    void slotDurationChanged(qint64 duration);
    void slotCurrentMediaChanged();
    void slotImportSong();
    void slotConnectCurrentMediaChanged();
    void slotMusicIndex(int musicIndex);
    void slotPlayedColor(QColor color);
    void slotNotPlayedColor(QColor color);
    void slotLyricFont(QFont font);

private slots:

    void on_hs_position_sliderMoved(int position);

    void on_hs_volume_sliderMoved(int position);

    void on_pb_setting_clicked();

    void on_pb_prev_clicked();

    void on_pb_player_clicked();

    void on_pb_next_clicked();

    void on_pb_min_clicked();

    void on_pb_close_clicked();

    void on_pb_playMode_clicked();

    void on_pb_volume_clicked();

    void on_pb_playList_clicked();

    void on_pb_skinsChanged_clicked();

protected:
    ///
    /// \brief 界面移动效果
    /// \param event
    ///
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);


private:
    Ui::MusicWidget *ui;
    SettingWidget *m_settingWidget;
    PlayList *m_playListWidget;

    int m_lyricShowIndex;
    MusicPlayer *m_musicPlayer;

    QPoint m_dragPosition;        //定义一个QPoint的成员变量
    QPoint m_middleLayerPosition;
};

#endif // MUSICWIDGET_H
