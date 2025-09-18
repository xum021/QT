#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logindialog.h"
#include"dbmanager.h"
#include<QRandomGenerator>

MainWindow::MainWindow(QString name,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist(this);
    player->setPlaylist(playlist);
    connect(player, &QMediaPlayer::positionChanged,
                this, &MainWindow::slot_positionChanged);
//    connect(player, &QMediaPlayer::mediaStatusChanged,
//                this, &MainWindow::slot_mediaStatusChanged);
//    connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(slot_positionChanged(qint64)));
//    connect(player,SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),this,
//            SLOT(slot_mediaStatusChanged(QMediaPlayer::MediaStatus)));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    player->setVolume(50);
    ui->horizontalSlider_volume->setValue(50);
    ui->label_user->setText("当前用户："+name);
    userName = name;
    DbManager::getInstance()->selectHistoryInfo(userName,historyMusics);
    //遍历容器 显示到列表控件中
    for(auto it = historyMusics.begin();it != historyMusics.end();it++)
    {
        ui->listWidget_history->addItem(*it);
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}

//改歌名
void MainWindow::on_playlist_currentIndexChanged(int index)
{
    // 检查索引是否有效
    if(index >= 0 && index < ui->listWidget->count())
    {
        // 获取对应索引的列表项
        QListWidgetItem *item = ui->listWidget->item(index);
        if(item)
        {
            // 更新标签显示的歌曲名称
            ui->label_music_name->setText(item->text());
            if(!historyMusics.count(fileNames[index]))
            {
            historyMusics.insert(fileNames[index]);
            ui->listWidget_history->addItem(fileNames[index]);
            }
        }
     }
}


void MainWindow::showAllFiles(QString path)
{
    //清空列表内容
    ui->listWidget->clear();
    playlist->clear();
    QDir dir(path);
    //2.判断目录是否存在，不存在 创建
    if(!dir.exists())
    {
        //创建
        dir.mkpath(path);
    }
        //3.提出当前目录下的所有文件 显示到ListWiget上
    fileNames = dir.entryList(QDir::Files,QDir::Name);
        //迭代器遍历
    for(auto iter = fileNames.begin();iter!=fileNames.end();iter++)
    {
        ui->listWidget->addItem(*iter);
        playlist->addMedia(QUrl(path+"/"+(*iter)));
    }
    player->setPlaylist(playlist);
    playlist->setCurrentIndex(0);
    ui->label_music_name->setText(fileNames[0]);
}

//void MainWindow::changeMusic()
//{
//    playlist->setCurrentIndex(playPosition);
//    ui->label_music_name->setText(fileNames[playPosition]);
//}

void MainWindow::on_pushButton_pre_clicked()
{
    if(playlist->mediaCount() == 0)
        return;
//    playPosition = playPosition==0?fileNames.size()-1:playPosition-1;
//    changeMusic();
    playlist->previous();
        // 更新显示当前歌曲名
    on_playlist_currentIndexChanged(playlist->currentIndex());

    if(player->state()==QMediaPlayer::PausedState||player->state()==QMediaPlayer::StoppedState)
    {
        player->play();
        ui->pushButton_play->setIcon(QIcon(":/stop.png"));
    }
}

void MainWindow::on_pushButton_play_clicked()
{
    if(playlist->mediaCount() == 0) return;

    if(player->state()==QMediaPlayer::PlayingState)
    {
        player->pause();
        ui->pushButton_play->setIcon(QIcon(":/start.png"));
    }else if(player->state()==QMediaPlayer::PausedState||player->state()==QMediaPlayer::StoppedState)
    {
        player->play();
        ui->pushButton_play->setIcon(QIcon(":/stop.png"));
    }
    if(!historyMusics.count(fileNames[currentIndex]))
    {
    historyMusics.insert(fileNames[currentIndex]);
    ui->listWidget_history->addItem(fileNames[currentIndex]);
    }
}

void MainWindow::on_pushButton_next_clicked()
{
    if(playlist->mediaCount() == 0) return;

//    playPosition=playPosition==fileNames.size()-1?0:playPosition+1;
//    changeMusic();
    playlist->next();
    on_playlist_currentIndexChanged(playlist->currentIndex());

    if(player->state()==QMediaPlayer::PausedState||player->state()==QMediaPlayer::StoppedState)
    {
        player->play();
        ui->pushButton_play->setIcon(QIcon(":/stop.png"));
    }
}

void MainWindow::on_pushButton_choose_dir_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this,"选择文件夹","E:/下载/music");
    showAllFiles(path);
}

void MainWindow::on_pushButton_change_user_clicked()
{
    LoginDialog *pl = new LoginDialog();
    pl->show();
    ui->listWidget_history->clear();
        //4.关闭当前窗口
    this->close();
}

void MainWindow::showTime(int position)
{
    //获取歌曲的总长度以毫秒为单位 所以1000
        int len = player->duration()/1000;
        qDebug()<<len; //151582 /1000 = 151

        //歌曲 总长为： 几分几秒
        int min = len/60;
        int sec = len%60;
        //在播放过程中，实时获取播放的进度秒数
        int cmin = position/1000/60;
        int csec = position/1000%60;

        //将上边四个变量 拼接成一个字符串 格式：[00:00 / 02:31]
        //                                     宽度2位 十进制   不够补0
        QString time =QString("[%1:%2 / %3:%4]").arg(cmin,2,      10,   QChar('0'))
                                                .arg(csec,2,     10,   QChar('0'))
                                                .arg(min,2,     10,   QChar('0'))
                                                .arg(sec,2,     10,   QChar('0'));
    ui->label_time->setText(time);

    //设置 滑动条最大的值 为歌曲的长度
        ui->horizontalSlider->setMaximum(player->duration());
        ui->horizontalSlider->setValue(position);
}
void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    playPosition = ui->listWidget->currentRow();
//    changeMusic();
    playlist->setCurrentIndex(playPosition);
    ui->label_music_name->setText(fileNames[playPosition]);
    if(player->state()==QMediaPlayer::PausedState||player->state()==QMediaPlayer::StoppedState)
    {
        player->play();
        ui->pushButton_play->setIcon(QIcon(":/stop.png"));
    }
}
void MainWindow::slot_positionChanged(qint64 position)
{
    showTime(position);
    ui->horizontalSlider->setMaximum(player->duration());
    ui->horizontalSlider->setValue(position); 
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    player->setPosition(position);
}

void MainWindow::slot_mediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if(playlist->mediaCount() == 0) return;

    if(status == QMediaPlayer::EndOfMedia)
    {
        on_pushButton_next_clicked();
    }
}


void MainWindow::on_horizontalSlider_volume_sliderMoved(int position)
{
    player->setVolume(position);
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        playlist->setPlaybackMode(QMediaPlaylist::Loop);
        break;
    case 1:
        playlist->setPlaybackMode(QMediaPlaylist::Random);
        break;
    case 2:
        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        break;
    }

}
