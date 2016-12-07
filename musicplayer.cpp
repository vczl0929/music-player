#include "musicplayer.h"
#include <QTime>

//qint64 MusicPlayer::m_playMode = 0;

MusicPlayer::MusicPlayer(QObject *parent) : QObject(parent)
{
    m_songsFile = new SongsFile;
    m_musicPlayList = new QMediaPlaylist;
    m_songsNameList = new QStringList;

    m_songsFile->initSongsListAndSongsNameList(*m_musicPlayList, *m_songsNameList);

    //m_player.setMedia(QUrl::fromLocalFile("演员 - 薛之谦.mp3"));
    m_player.setPlaylist(m_musicPlayList);
    m_player.setVolume(INIT_SYSTEM_VOLUME);

    m_player.state();
    connect(&m_player, SIGNAL(durationChanged(qint64)),//system m_player sent signal
            this, SLOT(slotDurationChanged(qint64)));//this object via slot receive signal
    connect(&m_player, SIGNAL(positionChanged(qint64)),
            this, SLOT(slotPositionChanged(qint64)));
}

//////////////get total time ////////////////////////
void MusicPlayer::slotDurationChanged(qint64 duration)
{
    m_totalPlayerTime = duration / TIME_MS_DURATION;
    emit signalDurationChanged(m_totalPlayerTime);
}

////////////get current position (ms)////////////////
void MusicPlayer::slotPositionChanged(qint64 position)
{
    m_currentPlayerTime = position / TIME_MS_DURATION;

    QTime currentTime((m_currentPlayerTime/3600)%60, (m_currentPlayerTime/60)%60,
                      m_currentPlayerTime%60, (m_currentPlayerTime*1000)%1000);
    QTime totalTime((m_totalPlayerTime/3600)%60, (m_totalPlayerTime/60)%60,
                    m_totalPlayerTime%60, (m_totalPlayerTime*1000)%1000);

    QString updateTime = currentTime.toString("mm:ss")
                        + "/"+ totalTime.toString("mm:ss");

    emit signalPositionChanged(updateTime);
}

QStringList *MusicPlayer::getSongsNameList() const
{
    return m_songsNameList;
}

void MusicPlayer::setSongsNameList(QStringList *songsNameList)
{
    m_songsNameList = songsNameList;
}

QMediaPlaylist *MusicPlayer::getMusicPlayList() const
{
    return m_musicPlayList;
}

void MusicPlayer::setMusicPlayList(QMediaPlaylist *musicPlayList)
{
    m_musicPlayList = musicPlayList;
}

SongsFile *MusicPlayer::getSongsFile() const
{
    return m_songsFile;
}

void MusicPlayer::setSongsFile(SongsFile *songsFile)
{
    m_songsFile = songsFile;
}


const qint64 MusicPlayer::getCurrentPlayerTime(void) const
{
    return m_currentPlayerTime;
}

QMediaPlayer &MusicPlayer::currentMediaPlayer(void)
{
    return m_player;
}

QMediaPlaylist *MusicPlayer::musicPlayList(void)
{
    return m_musicPlayList;
}

QStringList *MusicPlayer::songsNameList(void)
{
    return m_songsNameList;
}

QStringList &MusicPlayer::lyricList(void)
{
    return m_lyricList;
}

QMap<quint64, quint64> &MusicPlayer::mapLyricShow(void)
{
    return m_mapLyricShow;
}

void MusicPlayer::getCurrentSongLyric(void)
{
    LyricsFile lyricsFile;
    m_lyricList.clear();
    m_mapLyricShow.clear();
    lyricsFile.getCurrentSongLyric(m_lyricList, m_mapLyricShow);
}

void MusicPlayer::initMusicPlayer()
{
    m_songsFile->initSongsListAndSongsNameList(*m_musicPlayList,*m_songsNameList);
}
