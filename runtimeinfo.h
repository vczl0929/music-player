#ifndef RUNTIMEINFO_H
#define RUNTIMEINFO_H

#include <QObject>
#include <QWidget>
#include <QRect>
#include <QFile>
#include <QTime>
#include <QDebug>

class RunTimeInfo : public QObject
{
    Q_OBJECT
public:
    explicit RunTimeInfo(QObject *parent = 0);

    static QString getLyricPath();
    static void setLyricPath(const QString &lyricPath);

    static QString getSongPath();
    static void setSongPath(const QString &songPath);

    static QString getCurrentSongName();
    static void setCurrentSongName(const QString &currentSongName);

    static qint32 getVolumeMode();
    static void setVolumeMode(const qint32 &volumeMode);

    static qint32 getPlayMode();
    static void setPlayMode(const qint64 &playMode);

    static qint32 getPlayListFlag();
    static void setPlayListFlag(const qint32 &playListFlag);

    static int getPreviousVolumePosition();
    static void setPreviousVolumePosition(int previousVolumePosition);

    static QRect getRectTop();
    static void setRectTop(const QRect &rectTop);

    static void volumeModePlusAndUpdata();
    static void PlayModePlusAndUpdata();
    static void playListFlagPlusAndUpdata();
    static void skinsFlagPlusAndUpdata();
    static void mengFlagPlusAndUpdata();
    static void setFlagPlusAndUpdata();

    static qint32 getSkinsFlag();
    static void setSkinsFlag(const qint32 &skinsFlag);

    static qint32 getMengFlag();
    static void setMengFlag(const qint32 &mengFlag);

    static QColor getNotPlayedColor();
    static void setNotPlayedColor(const QColor &notPlayedColor);

    static QColor getPlayedColor();
    static void setPlayedColor(const QColor &playedColor);

    static qint32 getSetFlag();
    static void setSetFlag(const qint32 &setFlag);

    static QRect getRectALL();
    static void setRectALL(const QRect &rectALL);

    static QFont getFont();
    static void setFont(const QFont &font);

signals:

public slots:

private:
    static QString m_lyricPath;
    static QString m_songPath;
    static QString m_currentSongName;

    static qint32 m_volumeMode;
    static qint32 m_playMode;
    static qint32 m_playListFlag;
    static qint32 m_skinsFlag;
    static qint32 m_mengFlag;
    static qint32 m_setFlag;

    static int m_previousVolumePosition;

    static QRect m_rectALL;
    static QRect m_rectTop;

    static QColor m_notPlayedColor;
    static QColor m_playedColor;
    static QFont m_font;

};

#endif // RUNTIMEINFO_H
