#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QDir>
#include<QDebug>
#include<QFileDialog>
#include<QMediaPlayer>//媒体播放
#include<QMediaPlaylist>//播放列表
#include <QListWidget>
#include <QListWidgetItem>
#include<QComboBox>
#include<set>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QString name,QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_pre_clicked();
    void on_pushButton_play_clicked();
    void on_pushButton_next_clicked();
    void on_pushButton_choose_dir_clicked();
    void on_pushButton_change_user_clicked();
    void showTime(int position);
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
//    void changeMusic();
    void slot_positionChanged(qint64 position);
    void on_horizontalSlider_sliderMoved(int position);
    void slot_mediaStatusChanged(QMediaPlayer::MediaStatus status);
    void on_horizontalSlider_volume_sliderMoved(int position);
    void on_comboBox_currentIndexChanged(int index);
    void on_playlist_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    void showAllFiles(QString path);
    QStringList fileNames;
    bool isPlaying = false;
    int currentIndex = 0;
    int playPosition;
    //set容器 保存播放记录
    set<QString>historyMusics;
    //保存当前用户
    QString userName;

};
#endif // MAINWINDOW_H
