#include "runtimeinfo.h"

QString     RunTimeInfo::m_lyricPath;
QString     RunTimeInfo::m_songPath;
QString     RunTimeInfo::m_currentSongName;

qint32      RunTimeInfo::m_volumeMode;
qint32      RunTimeInfo::m_playMode = 2;
qint32      RunTimeInfo::m_playListFlag;
qint32      RunTimeInfo::m_skinsFlag;
qint32      RunTimeInfo::m_mengFlag;
qint32      RunTimeInfo::m_setFlag;

int         RunTimeInfo::m_previousVolumePosition;

QRect       RunTimeInfo::m_rectALL = QRect(0,0,850,550);
QRect       RunTimeInfo::m_rectTop = QRect(0,0,850,50);

QColor      RunTimeInfo::m_notPlayedColor = QColor(248, 217, 129);
QColor      RunTimeInfo::m_playedColor = QColor(255,0,0);

QFont       RunTimeInfo::m_font = QFont("楷体",20);

RunTimeInfo::RunTimeInfo(QObject *parent) : QObject(parent)
{
//    qDebug() << "frameGeometry().topLeft()" << frameGeometry().topLeft();
}

QString RunTimeInfo::getLyricPath()
{
    return m_lyricPath;
}

void RunTimeInfo::setLyricPath(const QString &lyricPath)
{
    m_lyricPath = lyricPath;
}

QString RunTimeInfo::getSongPath()
{
    return m_songPath;
}

void RunTimeInfo::setSongPath(const QString &songPath)
{
    m_songPath = songPath;
}

QString RunTimeInfo::getCurrentSongName()
{
    return m_currentSongName;
}

void RunTimeInfo::setCurrentSongName(const QString &currentSongName)
{
    m_currentSongName = currentSongName;
}

qint32 RunTimeInfo::getVolumeMode()
{
    return m_volumeMode;
}

void RunTimeInfo::setVolumeMode(const qint32 &volumeMode)
{
    m_volumeMode = volumeMode;
}

int RunTimeInfo::getPreviousVolumePosition()
{
    return m_previousVolumePosition;
}

void RunTimeInfo::setPreviousVolumePosition(int previousVolumePosition)
{
    m_previousVolumePosition = previousVolumePosition;
}

qint32 RunTimeInfo::getPlayMode()
{
    return m_playMode;
}

void RunTimeInfo::setPlayMode(const qint64 &playMode)
{
    m_playMode = playMode;
}


qint32 RunTimeInfo::getPlayListFlag()
{
    return m_playListFlag;
}

void RunTimeInfo::setPlayListFlag(const qint32 &playListFlag)
{
    m_playListFlag = playListFlag;
}

void RunTimeInfo::volumeModePlusAndUpdata()
{
    m_volumeMode++;
    m_volumeMode %= 2;
}

void RunTimeInfo::PlayModePlusAndUpdata()
{
    m_playMode++;
    m_playMode %= 4;
}

void RunTimeInfo::playListFlagPlusAndUpdata()
{
    m_playListFlag++;
    m_playListFlag %= 2;
}

qint32 RunTimeInfo::getSkinsFlag()
{
    return m_skinsFlag;
}

void RunTimeInfo::setSkinsFlag(const qint32 &skinsFlag)
{
    m_skinsFlag = skinsFlag;
}

qint32 RunTimeInfo::getMengFlag()
{
    return m_mengFlag;
}

void RunTimeInfo::setMengFlag(const qint32 &mengFlag)
{
    m_mengFlag = mengFlag;
}

QColor RunTimeInfo::getNotPlayedColor()
{
    return m_notPlayedColor;
}

void RunTimeInfo::setNotPlayedColor(const QColor &notPlayedColor)
{
    m_notPlayedColor = notPlayedColor;
}

QColor RunTimeInfo::getPlayedColor()
{
    return m_playedColor;
}

void RunTimeInfo::setPlayedColor(const QColor &playedColor)
{
    m_playedColor = playedColor;
}

qint32 RunTimeInfo::getSetFlag()
{
    return m_setFlag;
}

void RunTimeInfo::setSetFlag(const qint32 &setFlag)
{
    m_setFlag = setFlag;
}

QRect RunTimeInfo::getRectALL()
{
    return m_rectALL;
}

void RunTimeInfo::setRectALL(const QRect &rectALL)
{
    m_rectALL = rectALL;
}

QFont RunTimeInfo::getFont()
{
    return m_font;
}

void RunTimeInfo::setFont(const QFont &font)
{
    m_font = font;
}

QRect RunTimeInfo::getRectTop()
{
    return m_rectTop;
}

void RunTimeInfo::setRectTop(const QRect &rectTop)
{
    m_rectTop = rectTop;
}

void RunTimeInfo::skinsFlagPlusAndUpdata()
{
    m_skinsFlag++;
    m_skinsFlag %= 3;
}

void RunTimeInfo::mengFlagPlusAndUpdata()
{
    QTime t;

    t= QTime::currentTime();
    qsrand(t.msec()+t.second()*1000);

    m_mengFlag = qrand()% 5;
}

void RunTimeInfo::setFlagPlusAndUpdata()
{
    m_setFlag++;
    m_setFlag %= 2;
}
