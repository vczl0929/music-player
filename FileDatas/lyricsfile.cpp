#include "lyricsfile.h"
#include "musicwidget.h"
#include <QFile>

LyricsFile::LyricsFile(QObject *parent) : QObject(parent)
{
}

void LyricsFile::getCurrentSongLyric(QStringList &lyricList,
                           QMap<quint64, quint64> &mapLyricShow)
{
    m_lyricFormat = tr(".lrc");
    QString fileName = RunTimeInfo::getLyricPath() + "/" + RunTimeInfo::getCurrentSongName() + m_lyricFormat;
//    qDebug() << fileName;
    QFile lyricFile(fileName);
    if(!lyricFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "Error: File Opened";
    }else
    {
        qint64 index = 0;
        QString line;
        QStringList posAndLyric;
        QString lyric;
        QString pos;
        QTextStream in(&lyricFile);//bu dong

        mapLyricShow.clear();
        lyricList.clear();

        while(!in.atEnd())
        {
            line = in.readLine();
            posAndLyric = line.split("]");
            lyric = posAndLyric.at(1);
            pos = posAndLyric.at(0).mid(0,6);
            QStringList time = pos.remove("[").split(":");
            quint64 t = time[0].toInt()*60 + time[1].toInt();
            mapLyricShow.insert(t, index++);

            lyricList.append(lyric);
            posAndLyric.clear();
        }

        lyricFile.close();
    }
}
