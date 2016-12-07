#ifndef LYRICSFILE_H
#define LYRICSFILE_H

#include <QObject>
#include "runtimeinfo.h"


class LyricsFile : public QObject
{
    Q_OBJECT
public:
    explicit LyricsFile(QObject *parent = 0);

    void getCurrentSongLyric(QStringList &lyricList,
                               QMap<quint64, quint64> &mapLyricShow);

private:
    QString m_lyricDir;
    QString m_lyricFormat;
};

#endif // LYRICSFILE_H
