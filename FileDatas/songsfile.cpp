#include "songsfile.h"
#include "musicplayer.h"
#include "musicwidget.h"

SongsFile::SongsFile(QObject *parent) : QObject(parent)
{ 
}

void SongsFile::initSongsListAndSongsNameList(QMediaPlaylist &musicPlayList,
                             QStringList &songsNameList)
{

    m_songDir = QDir(RunTimeInfo::getSongPath());

    m_songFileList = m_songDir.entryInfoList(QStringList() << "*.mp3",
                                         QDir::Files, QDir::Name);//list file sort by name
    musicPlayList.clear();

    songsNameList.clear();

    foreach (QFileInfo fileInfo, m_songFileList)
    {
        songsNameList.append(fileInfo.fileName().remove(".mp3"));
        QUrl song = QUrl::fromLocalFile(fileInfo.absoluteFilePath());

        if(fileInfo.exists())
        {
            if (fileInfo.suffix().toLower() == QLatin1String("m3u"))
            //m3u format: music list
            //QLatin1String:convert faster,be suitable for Qstring compare
            {
                musicPlayList.load(song);
                //Load playlist from location.
                //If format is specified, it is used
            }else
            {
                musicPlayList.addMedia(song);
                //Append the media content to the playlist
            }
        }else
        {
            if (song.isValid())
            {
                musicPlayList.addMedia(song);
            }
        }
    }
//    qDebug() << "check list is empty" << musicPlayList.isEmpty();
//    qDebug() << "get cur index" << musicPlayList.currentIndex();

//    int tempLengthOfList = musicPlayList.mediaCount();
//    qDebug() << "get cur count" << tempLengthOfList;
//    for(int i = 0; i < tempLengthOfList; i++)
//    {
//        qDebug() << i << "remove media"<<musicPlayList.removeMedia(i);
//    }
//    tempLengthOfList = musicPlayList.mediaCount();
//    qDebug() << "get cur count" << tempLengthOfList;
//    musicPlayList.removeMedia(0,tempLengthOfList);
//    qDebug() <<
    musicPlayList.setCurrentIndex(0);
}
