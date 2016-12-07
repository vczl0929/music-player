#ifndef SONGSFILE_H
#define SONGSFILE_H

#include <QObject>

#include <QDir>
#include <QFileInfoList>
#include "runtimeinfo.h"

//#include "musicplayer.h" 循环包含出错
#include <QMediaPlaylist>

class SongsFile : public QObject
{
    Q_OBJECT
public:
    explicit SongsFile(QObject *parent = 0);

    void initSongsListAndSongsNameList(QMediaPlaylist &musicPlayList,
                                      QStringList &songsNameList);



private:
    QDir m_songDir;

    QFileInfoList m_songFileList;

};

#endif // SONGSFILE_H
