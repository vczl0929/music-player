#include "musicwidget.h"
#include "ui_musicwidget.h"
#include <QMediaPlayer>

MusicWidget::MusicWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MusicWidget)
{
    ui->setupUi(this);

    m_settingWidget  = new SettingWidget;
    m_settingWidget->initSystemSetting();

    m_musicPlayer    = new MusicPlayer;
    m_playListWidget = new PlayList;

    initWidgetUnits();

    //播放器与界面
    connect(m_musicPlayer, SIGNAL(signalPositionChanged(QString)),
            this, SLOT(slotPositionChanged(QString)));
    connect(m_musicPlayer, SIGNAL(signalDurationChanged(qint64)),
            this, SLOT(slotDurationChanged(qint64)));

    //连接当前音乐改变的信号与槽
    connect(this,SIGNAL(signalConnectCurrentMediaChanged()),
            this,SLOT(slotConnectCurrentMediaChanged()));

    //转盘起停
    connect(this,SIGNAL(signalMengStart()),ui->meng,SLOT(slotMengStart()));
    connect(this,SIGNAL(signalMengStop()),ui->meng,SLOT(slotMengStop()));

    //隐藏播放列表界面
    connect(this,SIGNAL(signalHidePlayListWidget(QPoint)),
            m_playListWidget,SLOT(slotHidePlayListWidget(QPoint)));

    //播放列表界面获取歌曲列表
    connect(this,SIGNAL(signalSongsNameList(QStringList *)),
            m_playListWidget,SLOT(slotSongsNameList(QStringList *)));
    connect(m_playListWidget,SIGNAL(signalMusicIndex(int)),
            this,SLOT(slotMusicIndex(int)));

    //播放列表界面同步换肤
    connect(this,SIGNAL(signalBluePlayList()),
            m_playListWidget,SLOT(slotBluePlayList()));
    connect(this,SIGNAL(signalRedPlayList()),
            m_playListWidget,SLOT(slotRedPlayList()));
    connect(this,SIGNAL(signalGreenPlayList()),
            m_playListWidget,SLOT(slotGreenPlayList()));

    //重装音乐文件
    connect(m_settingWidget,SIGNAL(signalImportSong()),
            this,SLOT(slotImportSong()));

    //改变歌词颜色
    connect(m_settingWidget,SIGNAL(signalPlayedColor(QColor)),
            this,SLOT(slotPlayedColor(QColor)));
    connect(m_settingWidget,SIGNAL(signalNotPlayedColor(QColor)),
            this,SLOT(slotNotPlayedColor(QColor)));

    //改变歌词字体
    connect(m_settingWidget,SIGNAL(signalLyricFont(QFont)),
            this,SLOT(slotLyricFont(QFont)));

    //隐藏设置界面
    connect(this,SIGNAL(signalHideSettingWidget(QPoint)),
            m_settingWidget,SLOT(slotHideSettingWidget(QPoint)));

    //歌曲自动播放至下一首
    connect(&(m_musicPlayer->currentMediaPlayer()),SIGNAL(currentMediaChanged(QMediaContent)),
            this,SLOT(slotCurrentMediaChanged()));

}

MusicWidget::~MusicWidget()
{
    delete ui;
}

void MusicWidget::initWidgetUnits(void)
{
    setWindowFlags(Qt::FramelessWindowHint); //去除边框; 置top；
    this->setWindowIcon(QIcon(":/common/skins/common/mylogo.png")); //设置图标图案
    skinsChanged(":/css/FileDatas/blueskin.css");//调用样式表初始化界面

    //子界面透明效果soga
    ui->lw_lyricShow->setAttribute(Qt::WA_TranslucentBackground, true);

    //隐藏水平方向和垂直方向的滚动条
    ui->lw_lyricShow->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->lw_lyricShow->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //初始化音量
    ui->hs_volume->setValue(INIT_SYSTEM_VOLUME);

    //初始化当前播放模式
    m_musicPlayer->musicPlayList()->setPlaybackMode(QMediaPlaylist::Loop);

    m_musicPlayer->currentMediaPlayer().stateChanged(QMediaPlayer::PausedState);
}

void MusicWidget::updateLyricInfo(quint64 time)
{
    quint64 temp = time;

    if(m_musicPlayer->mapLyricShow().contains(time))
    {
        showLyrics(temp);
    }
}

void MusicWidget::getCurrentSongLyricAndInitUI()
{
    // 获取新歌歌词并初始化相关界面
    m_musicPlayer->getCurrentSongLyric();
    ui->lw_lyricShow->clear();
    m_lyricShowIndex = 0;
    ui->lw_lyricShow->addItems(m_musicPlayer->lyricList());

    for(int i = 0; i < m_musicPlayer->lyricList().size(); i++)
    {
        ui->lw_lyricShow->item(i)->setTextAlignment(Qt::AlignCenter);
    }
}

void MusicWidget::sliderMovedUpdateLyricInfo(int time)
{
    int temp = time;
    if(time > 0)
    {
        if(m_musicPlayer->mapLyricShow().contains(time))
        {
            showLyrics(temp);
        }else
        {
            time--;
            sliderMovedUpdateLyricInfo(time);
        }
    }
}

void MusicWidget::showLyrics(quint64 time)
{
    m_lyricShowIndex = m_musicPlayer->mapLyricShow().value(time);

    if (m_lyricShowIndex > 0)
    {
        ui->lw_lyricShow->setCurrentRow(m_lyricShowIndex);//lyric slide cause
    }else if(m_lyricShowIndex == 0)
    {
        ui->lw_lyricShow->setCurrentRow(m_lyricShowIndex);//lyric slide cause
    }

    if((ui->lw_lyricShow->currentRow()) > 4)
    {
        ui->lw_lyricShow->verticalScrollBar()->setValue(ui->lw_lyricShow->currentRow() - 5);
    }
}

void MusicWidget::skinsChanged(QString file)
{
    QFile skinFile(file);
    if(skinFile.open(QIODevice::ReadOnly))
    {
        this->setStyleSheet(skinFile.readAll());
        skinFile.close();
    }
}

void MusicWidget::setRunTimeBlueSkin()
{
//    QString msg = ("QPushButton{border-image: url(:/%1/skins/%1/playStartNormal.png);}"
//                  "QPushButton:pressed{border-image: url(:/%1/skins/%1/playStartPressed.png);}"
//                  "QPushButton:hover{border-image: url(:/%1/skins/%1/playStartHover.png);}")
//            .arg("blue");
    if(m_musicPlayer->currentMediaPlayer().state() == QMediaPlayer::PausedState ||
            m_musicPlayer->currentMediaPlayer().state() == QMediaPlayer::StoppedState )
    {
        ui->pb_player->setStyleSheet("QPushButton{border-image: url(:/blue/skins/blue/playStartNormal.png);}"
                                     "QPushButton:pressed{border-image: url(:/blue/skins/blue/playStartPressed.png);}"
                                     "QPushButton:hover{border-image: url(:/blue/skins/blue/playStartHover.png);}");
    }else if(m_musicPlayer->currentMediaPlayer().state() == QMediaPlayer::PlayingState)
    {
        ui->pb_player->setStyleSheet("QPushButton{border-image: url(:/blue/skins/blue/pauseNormal.png);}"
                                     "QPushButton:hover{border-image: url(:/blue/skins/blue/pauseHover.png);}"
                                     "QPushButton:pressed{border-image: url(:/blue/skins/blue/pauseHover.png);}");
    }

    ui->pb_next->setStyleSheet("QPushButton{border-image: url(:/blue/skins/blue/next.png);}"
                               "QPushButton:pressed{border-image: url(:/blue/skins/blue/nextPressed.png);}"
                               "QPushButton:hover{border-image: url(:/blue/skins/blue/nextHover.png);}");
    ui->pb_prev->setStyleSheet("QPushButton{border-image: url(:/blue/skins/blue/previous.png);}"
                               "QPushButton:pressed{border-image: url(:/blue/skins/blue/previousPressed.png);}"
                               "QPushButton:hover{border-image: url(:/blue/skins/blue/previousHover.png);}");
}

void MusicWidget::setRunTimeRedSkin()
{
    if(m_musicPlayer->currentMediaPlayer().state() == QMediaPlayer::PausedState ||
            m_musicPlayer->currentMediaPlayer().state() == QMediaPlayer::StoppedState )
    {
        ui->pb_player->setStyleSheet("QPushButton{border-image: url(:/red/skins/red/playStartNormal.png);}"
                                     "QPushButton:pressed{border-image: url(:/red/skins/red/playStartPressed.png);}"
                                     "QPushButton:hover{border-image: url(:/red/skins/red/playStartHover.png);}");
    }else if(m_musicPlayer->currentMediaPlayer().state() == QMediaPlayer::PlayingState)
    {
        ui->pb_player->setStyleSheet("QPushButton{border-image: url(:/red/skins/red/pauseNormal.png);}"
                                     "QPushButton:hover{border-image: url(:/red/skins/red/pauseHover.png);}"
                                     "QPushButton:pressed{border-image: url(:/red/skins/red/pauseHover.png);}");
    }
    ui->pb_next->setStyleSheet("QPushButton{border-image: url(:/red/skins/red/nextNormal.png);}"
                               "QPushButton:pressed{border-image: url(:/red/skins/red/nextHover.png);}"
                               "QPushButton:hover{border-image: url(:/red/skins/red/nextHover.png);}");
    ui->pb_prev->setStyleSheet("QPushButton{border-image: url(:/red/skins/red/previousNormal.png);}"
                               "QPushButton:pressed{border-image: url(:/red/skins/red/previousPressed.png);}"
                               "QPushButton:hover{border-image: url(:/red/skins/red/previousHover.png);}");
}

void MusicWidget::setRunTimeGreenSkin()
{
    if(m_musicPlayer->currentMediaPlayer().state() == QMediaPlayer::PausedState ||
            m_musicPlayer->currentMediaPlayer().state() == QMediaPlayer::StoppedState )
    {
        ui->pb_player->setStyleSheet("QPushButton{border-image: url(:/green/skins/green/playStartNormal.png);}"
                                     "QPushButton:pressed{border-image: url(:/green/skins/green/playStartPressed.png);}"
                                     "QPushButton:hover{border-image: url(:/green/skins/green/playStartHover.png);}");
    }else if(m_musicPlayer->currentMediaPlayer().state() == QMediaPlayer::PlayingState)
    {
        ui->pb_player->setStyleSheet("QPushButton{border-image: url(:/green/skins/green/pauseNormal.png);}"
                                     "QPushButton:hover{border-image: url(:/green/skins/green/pauseHover.png);}"
                                     "QPushButton:pressed{border-image: url(:/green/skins/green/pauseHover.png);}");
    }
    ui->pb_next->setStyleSheet("QPushButton{border-image: url(:/green/skins/green/nextNormal.png);}"
                               "QPushButton:pressed{border-image: url(:/green/skins/green/nextHover.png);}"
                               "QPushButton:hover{border-image: url(:/green/skins/green/nextHover.png);}");
    ui->pb_prev->setStyleSheet("QPushButton{border-image: url(:/green/skins/green/previousNormal.png);}"
                               "QPushButton:pressed{border-image: url(:/green/skins/green/previousPressed.png);}"
                               "QPushButton:hover{border-image: url(:/green/skins/green/previousHover.png);}");
}

void MusicWidget::switchSkin()
{
    switch (RunTimeInfo::getSkinsFlag()) {
    case 0:
        setRunTimeBlueSkin();
        break;
    case 1:
        setRunTimeRedSkin();
        break;
    case 2:
        setRunTimeGreenSkin();
        break;
    default:
        break;
    }
}

////////set lb_timeUpdate and hs_position silde/////////
void MusicWidget::slotPositionChanged(QString updateTime)
{
    ui->lb_timeUpdate->setText(updateTime);
    if(!ui->hs_position->isSliderDown())
    {
        ui->hs_position->setValue(m_musicPlayer->getCurrentPlayerTime());//当slider不被按下时
    }

    if(m_musicPlayer->currentMediaPlayer().state() == QMediaPlayer::PlayingState)
    {
        updateLyricInfo(m_musicPlayer->getCurrentPlayerTime());
    }
}

///////set hs_position maxsize///////////////////////
void MusicWidget::slotDurationChanged(qint64 duration)
{
    if(duration > 0)
    {
        ui->hs_position->setMaximum(duration);
    }
}

void MusicWidget::slotCurrentMediaChanged()
{
    RunTimeInfo::setCurrentSongName(m_musicPlayer->songsNameList()->at(m_musicPlayer->getMusicPlayList()->currentIndex()));

    ui->lb_songName->setText(RunTimeInfo::getCurrentSongName());

    getCurrentSongLyricAndInitUI();
}

void MusicWidget::slotImportSong()
{
    ui->lw_lyricShow->clear();
    ui->lb_songName->clear();

    m_musicPlayer->currentMediaPlayer().stop();
    switchSkin();

    emit signalMengStop();

    m_musicPlayer->initMusicPlayer();
    emit signalConnectCurrentMediaChanged();
}

void MusicWidget::slotConnectCurrentMediaChanged()
{
    connect(&(m_musicPlayer->currentMediaPlayer()),SIGNAL(currentMediaChanged(QMediaContent)),
            this,SLOT(slotCurrentMediaChanged()));
}

void MusicWidget::slotMusicIndex(int musicIndex)
{
    if(musicIndex < m_musicPlayer->songsNameList()->size())
    {
        // 歌曲切换初始化位置
        RunTimeInfo::setCurrentSongName(m_musicPlayer->songsNameList()->at(musicIndex));
        ui->lb_songName->setText(RunTimeInfo::getCurrentSongName());
        m_musicPlayer->musicPlayList()->setCurrentIndex(musicIndex);
    }

    getCurrentSongLyricAndInitUI();

    m_musicPlayer->currentMediaPlayer().play();

    if(m_musicPlayer->currentMediaPlayer().state() == QMediaPlayer::PlayingState)
    {
        switchSkin();
    }
}

void MusicWidget::slotPlayedColor(QColor color)
{
    RunTimeInfo::setPlayedColor(color);
    QString msg = QString("QListWidget#lw_lyricShow{color: rgb(%1, %2, %3);font: bold;font-family: %7 ;font-size: %8px;}"
                          "QListWidget#lw_lyricShow:item{color: rgb(%1, %2, %3);}"
                          "QListWidget#lw_lyricShow:item:selected{color: rgb(%4, %5, %6);}")
            .arg(QString::number(RunTimeInfo::getNotPlayedColor().red()),
                 QString::number(RunTimeInfo::getNotPlayedColor().green()),
                 QString::number(RunTimeInfo::getNotPlayedColor().blue()),
                 QString::number(RunTimeInfo::getPlayedColor().red()),
                 QString::number(RunTimeInfo::getPlayedColor().green()),
                 QString::number(RunTimeInfo::getPlayedColor().blue()),
                 RunTimeInfo::getFont().family(),
                 QString::number(RunTimeInfo::getFont().pointSize()));
    ui->lw_lyricShow->setStyleSheet(msg);
}

void MusicWidget::slotNotPlayedColor(QColor color)
{
    RunTimeInfo::setNotPlayedColor(color);
    QString msg = QString("QListWidget#lw_lyricShow{color: rgb(%1, %2, %3);font: bold;font-family: %7 ;font-size: %8px;}"
                          "QListWidget#lw_lyricShow:item{color: rgb(%1, %2, %3);}"
                          "QListWidget#lw_lyricShow:item:selected{color: rgb(%4, %5, %6);}")
            .arg(QString::number(RunTimeInfo::getNotPlayedColor().red()),
                 QString::number(RunTimeInfo::getNotPlayedColor().green()),
                 QString::number(RunTimeInfo::getNotPlayedColor().blue()),
                 QString::number(RunTimeInfo::getPlayedColor().red()),
                 QString::number(RunTimeInfo::getPlayedColor().green()),
                 QString::number(RunTimeInfo::getPlayedColor().blue()),
                 RunTimeInfo::getFont().family(),
                 QString::number(RunTimeInfo::getFont().pointSize()));
    ui->lw_lyricShow->setStyleSheet(msg);
}

void MusicWidget::slotLyricFont(QFont font)
{
    RunTimeInfo::setFont(font);
    QString msg = QString("QListWidget#lw_lyricShow{color: rgb(%1, %2, %3);font: bold;font-family: %4 ;font-size: %5px;}"
                          "QListWidget#lw_lyricShow:item:selected{color: rgb(%6, %7, %8);}")
            .arg(QString::number(RunTimeInfo::getNotPlayedColor().red()),
                 QString::number(RunTimeInfo::getNotPlayedColor().green()),
                 QString::number(RunTimeInfo::getNotPlayedColor().blue()),
                 font.family(),
                 QString::number(font.pointSize()),
                 QString::number(RunTimeInfo::getPlayedColor().red()),
                 QString::number(RunTimeInfo::getPlayedColor().green()),
                 QString::number(RunTimeInfo::getPlayedColor().blue()));
    qDebug() << "font.pointSize()()" << font.pointSize();
    qDebug() << "font.pixelSize()" << font.pixelSize();
    ui->lw_lyricShow->setStyleSheet(msg);
}

void MusicWidget::on_hs_position_sliderMoved(int position)
{
    m_musicPlayer->currentMediaPlayer().setPosition(
                position * TIME_MS_DURATION);
    sliderMovedUpdateLyricInfo(position);
}

void MusicWidget::on_pb_volume_clicked()
{
    RunTimeInfo::volumeModePlusAndUpdata();

    switch (RunTimeInfo::getVolumeMode()) {
    case 0:
        if(RunTimeInfo::getPreviousVolumePosition() == 0)
        {
            m_musicPlayer->currentMediaPlayer().setVolume(INIT_SYSTEM_VOLUME);
        }else
        {
            m_musicPlayer->currentMediaPlayer().setVolume(RunTimeInfo::getPreviousVolumePosition());
        }

        ui->hs_volume->setValue(m_musicPlayer->currentMediaPlayer().volume());
        ui->pb_volume->setStyleSheet("border-image: url(:/common/skins/common/volumeon.png)");
        break;
    case 1:
        m_musicPlayer->currentMediaPlayer().setVolume(0);
        ui->hs_volume->setValue(0);
        ui->pb_volume->setStyleSheet("border-image: url(:/common/skins/common/volumeoff.png)");
        break;
    default:
        break;
    }
}

void MusicWidget::on_hs_volume_sliderMoved(int position)
{
    ///可以再保存一个按下滑块时的值pressed clicked，判断如果release时等于0就恢复到那个值
    RunTimeInfo::setPreviousVolumePosition(position);
    m_musicPlayer->currentMediaPlayer().setVolume(position);
    if(position == 0)
    {
        ui->pb_volume->setStyleSheet("border-image: url(:/common/skins/common/volumeoff.png)");
    }else
    {
        ui->pb_volume->setStyleSheet("border-image: url(:/common/skins/common/volumeon.png)");
    }
}

void MusicWidget::on_pb_setting_clicked()
{
    RunTimeInfo::setFlagPlusAndUpdata();
    disconnect(&(m_musicPlayer->currentMediaPlayer()),SIGNAL(currentMediaChanged(QMediaContent)),
               this,SLOT(slotCurrentMediaChanged()));
    QPoint temp;
    temp = ui->pb_setting->mapToGlobal(QPoint(0,0));
    qDebug() << "temp" << temp;
    m_settingWidget->move(temp.x() - 712,temp.y() + 34);
    if(RunTimeInfo::getSetFlag() == 1)
    {
        m_settingWidget->show();
    }else if(RunTimeInfo::getSetFlag() == 0)
    {
        m_settingWidget->hide();
    }
}

void MusicWidget::on_pb_prev_clicked()
{
    if(m_musicPlayer->musicPlayList()->previousIndex() == -1)
    {
        m_musicPlayer->musicPlayList()->next();//always play first song
    }

    m_musicPlayer->musicPlayList()->previous();     //跳到上一首
    m_musicPlayer->currentMediaPlayer().play();
    emit signalMengStart();
    switchSkin();
    RunTimeInfo::setCurrentSongName(m_musicPlayer->songsNameList()->at(m_musicPlayer->musicPlayList()->currentIndex()));
    ui->lb_songName->setText(RunTimeInfo::getCurrentSongName());

    getCurrentSongLyricAndInitUI();
    RunTimeInfo::mengFlagPlusAndUpdata();
}

void MusicWidget::on_pb_player_clicked()
{
    RunTimeInfo::setCurrentSongName(m_musicPlayer->songsNameList()->at(m_musicPlayer->musicPlayList()->currentIndex()));

    if(m_musicPlayer->currentMediaPlayer().state() == QMediaPlayer::PausedState ||
            m_musicPlayer->currentMediaPlayer().state() == QMediaPlayer::StoppedState )
    {
        emit signalMengStart();
        m_musicPlayer->currentMediaPlayer().play();

        switchSkin();

        getCurrentSongLyricAndInitUI();
    }else if(m_musicPlayer->currentMediaPlayer().state() == QMediaPlayer::PlayingState)
    {
        emit signalMengStop();
        m_musicPlayer->currentMediaPlayer().pause();
        switchSkin();
    }
    ui->lb_songName->setText(RunTimeInfo::getCurrentSongName());
}

void MusicWidget::on_pb_next_clicked()
{
    if (m_musicPlayer->musicPlayList()->nextIndex() == -1)
    {
        m_musicPlayer->musicPlayList()->previous();//always play last song
    }

    m_musicPlayer->musicPlayList()->next();        //跳到下一首
    m_musicPlayer->currentMediaPlayer().play();
    emit signalMengStart();

    switchSkin();

    RunTimeInfo::setCurrentSongName(m_musicPlayer->songsNameList()->at(m_musicPlayer->musicPlayList()->currentIndex()));
    ui->lb_songName->setText(RunTimeInfo::getCurrentSongName());

    getCurrentSongLyricAndInitUI();
    RunTimeInfo::mengFlagPlusAndUpdata();

}

void MusicWidget::on_pb_min_clicked()
{
    m_playListWidget->close();
    m_settingWidget->close();
    this->showMinimized();
}

void MusicWidget::on_pb_close_clicked()
{
    m_playListWidget->close();
    m_settingWidget->close();
    this->close();
}

void MusicWidget::on_pb_playMode_clicked()
{
    RunTimeInfo::PlayModePlusAndUpdata();
    qDebug() << "RunTimeInfo::getPlayMode()" << RunTimeInfo::getPlayMode();
    switch (RunTimeInfo::getPlayMode()) {
    case CurrentItemInLoop:
        m_musicPlayer->musicPlayList()->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        ui->pb_playMode->setStyleSheet("border-image: url(:/common/skins/common/currentItemInLoopPressed.png)");
        break;
    case Sequential:
        m_musicPlayer->musicPlayList()->setPlaybackMode(QMediaPlaylist::Sequential);
        ui->pb_playMode->setStyleSheet("border-image: url(:/common/skins/common/sequentialPressed.png)");
        break;
    case Loop:
        m_musicPlayer->musicPlayList()->setPlaybackMode(QMediaPlaylist::Loop);
        ui->pb_playMode->setStyleSheet("border-image: url(:/common/skins/common/loopPressed.png)");
        break;
    case Random:
        m_musicPlayer->musicPlayList()->setPlaybackMode(QMediaPlaylist::Random);
        ui->pb_playMode->setStyleSheet("border-image: url(:/common/skins/common/randomPressed.png)");
        break;
    default: break;
    }
}

void MusicWidget::mousePressEvent(QMouseEvent *event)
{

    if (event->button() == Qt::LeftButton) //点击左边鼠标
    {
        emit signalHidePlayListWidget(event->pos());
        emit signalHideSettingWidget(event->pos());
        m_dragPosition = event->globalPos() - frameGeometry().topLeft();
        //globalPos()获取根窗口的相对路径，frameGeometry().topLeft()获取主窗口左上角的位置
        event->accept();   //鼠标事件被系统接收
    }
}

void MusicWidget::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() == Qt::LeftButton) && (RunTimeInfo::getRectTop().contains(event->pos()))) //当满足鼠标左键被点击到顶端时。
    {
        move(event->globalPos() - m_dragPosition);//移动窗口
        event->accept();
    }
}

void MusicWidget::on_pb_playList_clicked()
{
    RunTimeInfo::playListFlagPlusAndUpdata();
    emit signalSongsNameList(m_musicPlayer->getSongsNameList());

    QPoint temp;
    temp = ui->pb_playList->mapToGlobal(QPoint(0,0));

    m_playListWidget->move(temp.x() - 490 + 46,temp.y() - 450 - 10);

    if (RunTimeInfo::getPlayListFlag() == 1)
    {
        m_playListWidget->show();
    }else
    {
        m_playListWidget->hide();
    }


}

void MusicWidget::on_pb_skinsChanged_clicked()
{
    RunTimeInfo::skinsFlagPlusAndUpdata();
    switch (RunTimeInfo::getSkinsFlag()) {
    case 0:
        skinsChanged(":/css/FileDatas/blueskin.css");
        emit signalBluePlayList();
        break;

    case 1:
        skinsChanged(":/css/FileDatas/redskin.css");
        emit signalRedPlayList();
        break;

    case 2:
        skinsChanged(":/css/FileDatas/greenskin.css");
        emit signalGreenPlayList();
        break;
    default:
        break;
    }

    if(m_musicPlayer->currentMediaPlayer().state() == QMediaPlayer::PausedState ||
            m_musicPlayer->currentMediaPlayer().state() == QMediaPlayer::StoppedState )
    {
        m_musicPlayer->currentMediaPlayer().pause();
        switchSkin();
    }else if(m_musicPlayer->currentMediaPlayer().state() == QMediaPlayer::PlayingState)
    {
        m_musicPlayer->currentMediaPlayer().play();
        switchSkin();
    }
}
