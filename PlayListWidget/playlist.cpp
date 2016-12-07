#include "playlist.h"
#include "ui_playlist.h"
#include <QDebug>

PlayList::PlayList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayList)
{
    ui->setupUi(this);

    QFile skinFile(":/css/FileDatas/playlist.css");
    if(skinFile.open(QIODevice::ReadOnly))
    {
        this->setStyleSheet(skinFile.readAll());
        skinFile.close();
    }

    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool); //去除边框; 置top；
    //子界面透明效果
    ui->lw_songsList->setAttribute(Qt::WA_TranslucentBackground, true);
}

PlayList::~PlayList()
{
    delete ui;
}

void PlayList::slotSongsNameList(QStringList *songsNameList)
{
    ui->lw_songsList->clear();
    ui->lw_songsList->addItems(*songsNameList);

    ui->lw_songsList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->lw_songsList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void PlayList::on_lw_songsList_doubleClicked(const QModelIndex &index)
{
    emit signalMusicIndex(index.row());
}

void PlayList::slotHidePlayListWidget(QPoint eventPos)
{
    if(RunTimeInfo::getRectALL().contains(eventPos))
    {
        this->hide();
        RunTimeInfo::playListFlagPlusAndUpdata();
    }
}

void PlayList::on_pb_playList_close_clicked()
{
    RunTimeInfo::playListFlagPlusAndUpdata();
    this->close();
}

void PlayList::slotBluePlayList()
{
    setStyleSheet("QWidget#wgt_playList{border-image: url(:/blue/skins/blue/bluePlayList.png);}"
                  "QListWidget#lw_songsList{border-image: url(:/blue/skins/blue/bluePlayList.png);}"
                  "QPushButton#pb_playList_close{border-image: url(:/common/skins/common/closePressed.png);}");
}

void PlayList::slotRedPlayList()
{
    setStyleSheet("QWidget#wgt_playList{border-image: url(:/red/skins/red/redPlayList.png);}"
                  "QListWidget#lw_songsList{border-image: url(:/red/skins/red/redPlayList.png);}"
                  "QPushButton#pb_playList_close{border-image: url(:/common/skins/common/closePressed.png);}");
}

void PlayList::slotGreenPlayList()
{
    setStyleSheet("QWidget#wgt_playList{border-image: url(:/green/skins/green/greenPlayList.png);}"
                  "QListWidget#lw_songsList{border-image: url(:/green/skins/green/greenPlayList.png);}"
                  "QPushButton#pb_playList_close{border-image: url(:/common/skins/common/closePressed.png);}");
}
