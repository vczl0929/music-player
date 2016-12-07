#include "settingwidget.h"
#include "ui_settingwidget.h"

#include <QFileDialog>
#include <QSettings>
#include <QDebug>

#include "songsfile.h"
#include "lyricsfile.h"
#include "musicwidget.h"
#include "musicplayer.h"

SettingWidget::SettingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingWidget)
{
    ui->setupUi(this);

    RunTimeInfo::getSongPath().clear();
    RunTimeInfo::getLyricPath().clear();
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool); //去除边框; 置top；

    QFile skinFile(":/css/FileDatas/set.css");
    if(skinFile.open(QIODevice::ReadOnly))
    {
        this->setStyleSheet(skinFile.readAll());
        skinFile.close();
    }
}

SettingWidget::~SettingWidget()
{
    delete ui;
}

bool SettingWidget::writeInit(QString path, QString user_key, QString user_value)
{
    //qDebug() << "path" << path;
    if(path.isEmpty() || user_key.isEmpty())
    {
        return false;
    }
    else
    {
        //创建配置文件操作对象
        QSettings *config = new QSettings(path, QSettings::IniFormat);

        //将信息写入配置文件
        config->beginGroup("config");
        config->setValue(user_key, user_value);
        config->endGroup();

        return true;
    }
}

bool SettingWidget::readInit(QString path, QString user_key)
{
    if(path.isEmpty() || user_key.isEmpty())
    {
        return false;
    }else
    {
        //创建配置文件操作对象
        QSettings *config = new QSettings(path, QSettings::IniFormat);

        if (user_key == "SONGPATH")
        {
            //读取用户配置信息
            RunTimeInfo::setSongPath(config->value(QString("config/") + user_key).toString());
        }else if(user_key == "LYRICPATH")
        {
            RunTimeInfo::setLyricPath(config->value(QString("config/") + user_key).toString());
        }
        return true;
    }
}

void SettingWidget::on_tb_songsPath_clicked()
{
    RunTimeInfo::setSongPath(QFileDialog::getExistingDirectory());

    ui->le_songsPath->setText(RunTimeInfo::getSongPath());
}

void SettingWidget::on_tb_lyricsPath_clicked()
{
    RunTimeInfo::setLyricPath(QFileDialog::getExistingDirectory());
    ui->le_lyricsPath->setText(RunTimeInfo::getLyricPath());
}

void SettingWidget::on_pb_save_clicked()
{
    writeInit(QString("../FileDatas/user.ini"), "SONGPATH", RunTimeInfo::getSongPath());
    writeInit(QString("../FileDatas/user.ini"), "LYRICPATH", RunTimeInfo::getLyricPath());

    emit signalImportSong();
    initSystemSetting();

    this->hide();

}

void SettingWidget::initSystemSetting(void)
{
    readInit(QString("../FileDatas/user.ini"), "SONGPATH");
    readInit(QString("../FileDatas/user.ini"), "LYRICPATH");

    ui->le_songsPath->setText(RunTimeInfo::getSongPath());
    ui->le_lyricsPath->setText(RunTimeInfo::getLyricPath());
}

void SettingWidget::on_pb_cancle_clicked()
{
    RunTimeInfo::setFlagPlusAndUpdata();
    this->hide();
}

void SettingWidget::on_pb_set_close_clicked()
{
    RunTimeInfo::setFlagPlusAndUpdata();
    this->close();
}

void SettingWidget::on_pb_back_clicked()
{
    RunTimeInfo::setFlagPlusAndUpdata();
    this->close();
}

void SettingWidget::on_pb_color1_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this);

    emit signalPlayedColor(color);
}

void SettingWidget::on_pb_color2_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this);

    emit signalNotPlayedColor(color);
}

void SettingWidget::on_pb_font1_clicked()
{
    bool ok;
    QFont font = QFontDialog::getFont(
                &ok, QFont("楷体", 20), this);
    if(ok)
    {
        qDebug() << "fontok" << font;
        qDebug() << "font.family()ok" << font.family();
        qDebug() << "font.pointSize()ok" << font.pointSize();
        emit signalLyricFont(font);
    }else
    {
        qDebug() << "fontno" << font;
    }

}

void SettingWidget::slotHideSettingWidget(QPoint eventPos)
{
    if(RunTimeInfo::getRectALL().contains(eventPos))
    {
        this->hide();
        RunTimeInfo::setFlagPlusAndUpdata();
    }
}
