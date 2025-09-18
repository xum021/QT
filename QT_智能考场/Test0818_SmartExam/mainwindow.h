#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QDebug>
#include<opencv2/opencv.hpp>
using namespace cv;
#include<opencv2/face.hpp>
using namespace cv::face;
#include<QTimerEvent>
#include<vector>
using namespace std;
#include<QFile>
#include<QMessageBox>
#include"userdao.h"
#include<map>
#include<ctime>
#include<cstdlib>
#include"SpeakHelper.h"
#include"excelhelper.h"
#include<QFileDialog>//文件对话框 选表格

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

//保存座位和人名
struct PointAndName
{
    int m_x;
    int m_y;
    QString name;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QString c,int n,QWidget *parent = nullptr);
    ~MainWindow();
    //初始化函数
    void init();
    //重写定时器事件处理函数
    void timerEvent(QTimerEvent *e);
    //显示图片的函数
    void showImg();
    //查找人脸
    void findFace();
    //改变座位上的图像
    bool changeLabelImg(Mat face,PointAndName& v,int flag);

private slots:
    void on_pushButton_choose_clicked();

    void on_pushButton_over_clicked();

    void on_pushButton_export_clicked();

private:
    Ui::MainWindow *ui;
    //成员变量 考试名称 参考人数
    QString course;
    int num;
    //添加两个对象
    VideoCapture vc;
    Mat src;
    //级联分类
    CascadeClassifier cc;
    //保存查找到的人脸矩形的容器
    vector<Rect>find_face;
    //数据库指针
    UserDao *userDao;
    //人脸识别器对象
    Ptr<FaceRecognizer> recognizer;
    //容器
    map<int,PointAndName> map_users;
    //添加语音播报类的对象
    SpeakHelper helper;
    //创建表格操作的对象
    ExcelHelper ex_helper;
};
#endif // MAINWINDOW_H
