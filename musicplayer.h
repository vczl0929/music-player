#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QObject>
#include <QMediaPlayer>     //QT       += core gui multimedia

#include <QMediaPlaylist>

#include "songsfile.h"
#include "lyricsfile.h"

#define TIME_MS_DURATION 1000
#define INIT_SYSTEM_VOLUME 50

class MusicPlayer : public QObject
{
    Q_OBJECT
public:
    explicit MusicPlayer(QObject *parent = 0);

    const qint64 getCurrentPlayerTime(void) const;

    void initMusicPlayer();

    // 歌曲播放逻辑
    QMediaPlayer &currentMediaPlayer(void);


    // 歌曲列表获取逻辑
    QMediaPlaylist *musicPlayList(void);
    QStringList *songsNameList(void);
    // 歌曲歌词获取逻辑
    void getCurrentSongLyric(void);
    QStringList &lyricList(void);
    QMap<quint64, quint64> &mapLyricShow(void);

    void setSongsFile(SongsFile *songsFile);
    SongsFile *getSongsFile() const;


    QMediaPlaylist *getMusicPlayList() const;
    void setMusicPlayList(QMediaPlaylist *musicPlayList);

    QStringList *getSongsNameList() const;
    void setSongsNameList(QStringList *songsNameList);

signals:
    void signalPositionChanged(QString updateTime);
    void signalDurationChanged(qint64 duration);
    void signalCurrentIndexChanged(qint64 position);

public slots:
    void slotPositionChanged(qint64 position);
    void slotDurationChanged(qint64 duration);



private:
    // 歌曲播放逻辑
    QMediaPlayer m_player;
    qint64 m_totalPlayerTime;
    qint64 m_currentPlayerTime;


    // 歌曲列表获取逻辑
    SongsFile *m_songsFile;
    QMediaPlaylist *m_musicPlayList;
    QStringList *m_songsNameList;

    // 歌曲歌词获取逻辑
    QStringList m_lyricList;
    QMap<quint64, quint64> m_mapLyricShow; //time, index
};

#endif // MUSICPLAYER_H
