#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QWidget>
#include <QColorDialog>
#include <QFontDialog>

namespace Ui {
class SettingWidget;
}

class SettingWidget : public QWidget
{
    Q_OBJECT

signals:
    void signalImportSong();
    void signalPlayedColor(QColor);
    void signalNotPlayedColor(QColor);
    void signalLyricFont(QFont);
public slots:
    void slotHideSettingWidget(QPoint eventPos);
public:
    explicit SettingWidget(QWidget *parent = 0);
    ~SettingWidget();

    void initSystemSetting(void);

    bool writeInit(QString path, QString user_key, QString user_value);
    bool readInit(QString path, QString user_key);

private slots:
    void on_tb_songsPath_clicked();

    void on_tb_lyricsPath_clicked();

    void on_pb_save_clicked();

    void on_pb_cancle_clicked();

    void on_pb_set_close_clicked();

    void on_pb_back_clicked();

    void on_pb_color1_clicked();

    void on_pb_color2_clicked();

    void on_pb_font1_clicked();


private:
    Ui::SettingWidget *ui;
};

#endif // SETTINGWIDGET_H
