#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QString c, int n, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),course(c),num(n)
{
    ui->setupUi(this);
    qDebug()<<course<<" "<<num;
    init();
    if(vc.open(0))
    {
        //开启定时器 每隔50ms提取一帧图片并显示
        startTimer(50);
    }
    cc = CascadeClassifier("E:/opencv3.4-install/install/etc/haarcascades/haarcascade_frontalface_alt2.xml");
    //实例化数据库对象
    userDao = UserDao::getUser();
    //初始化人脸识别器
    QFile file("face.xml");
    if(file.exists())
    {
        //加载
        recognizer = FaceRecognizer::load<LBPHFaceRecognizer>("face.xml");
    }
    else
    {
        //创建
        recognizer = LBPHFaceRecognizer::create();
    }
    srand(time(0));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    //1.label显示考试名称
    ui->label_course->setText(course+"考试");
    //2.动态地向网格布局中添加label
    int index = 0;//下标 每次添加一个label index++
    int row = 0;//行数 不固定 列固定
    while (true)
    {
        for(int i=0;i<6;i++)//i 代表列
        {
            if(index == num)
                return;
            //1.创建label 堆空间
            QLabel *label = new QLabel(this);
            //2.给label设置要显示地图片
            QPixmap p("D:/picture/avatar.png");
            label->setFrameShape(QFrame::Box);
            //3.调整图片的大小
            p = p.scaled(60,60);
            //4.显示
            label->setPixmap(p);

            //设置标志位
            label->setObjectName("0");
            //5.把label添加到网格布局中
            //              (添加控件) (添加label)(行数)(列数)（每个空间占1行1列）
            ui->gridLayout->addWidget(label,row,i,1,1);
            index++;
        }
        row++;
    }
}

void MainWindow::timerEvent(QTimerEvent *e)
{
    //1.一帧一帧地提取图片
        vc>>src;
    //2.判空处理
        if(src.empty())
            return;
    //3.实现翻转
        flip(src,src,1);
        //查找
        findFace();
    //4.在label上显示
        showImg();
}

void MainWindow::showImg()
{
    Mat dst;
    //Mat-->QImage-->QPixmap
    cvtColor(src,dst,CV_BGR2RGB);
    QImage img(dst.data,
               dst.cols,
               dst.rows,
               dst.cols*dst.channels(),
               QImage::Format_RGB888);
    QPixmap p = QPixmap::fromImage(img);
    p = p.scaled(QSize(ui->label_face->size()));
//    ui->label_face->resize(QSize(p.size()));
    ui->label_face->setPixmap(p);
}

void MainWindow::findFace()
{
    //1.灰度图
    Mat gray;
    cvtColor(src,gray,CV_BGR2GRAY);
    //2.查找人脸
    cc.detectMultiScale(gray,find_face);
    //3。判断是否为空
    if(find_face.size())
    {
        //4.画框
        rectangle(src,find_face[0],Scalar(0,0,255),3);
    }
}
//选座
void MainWindow::on_pushButton_choose_clicked()
{
    //1.获取考生姓名 判空处理 为空就弹窗提示
    QString name = ui->lineEdit->text();
    //2.判空
    if(name.isEmpty())
    {
        QMessageBox::warning(this,"警告","请输入学生姓名");
        return;
    }
    //2.截取人脸的照片 保存到容器里(录入 给人脸识别器)
    vector<Mat> studyFaces;
    Mat dst;
    if(find_face.size()==0)
    {
        QMessageBox::information(this,"","未找到正在考试的人员");
        return;
    }
    dst = src(find_face[0]);
    //创建副本图片
    Mat temp = dst.clone();
    cvtColor(dst,dst,CV_BGR2GRAY);
    cv::resize(dst,dst,Size(60,60));
    studyFaces.push_back(dst);
    //3.插入到数据库 如果插入成功 返回一个id(录入 给人脸识别器)
    userDao->insertUser(name);
    int id = userDao->getUserId();
    vector<int>studyLabels;
    studyLabels.push_back(id);
    //4.让人脸识别器更新并保存
    recognizer->update(studyFaces,studyLabels);
    recognizer->save("face.xml");
    //5.随机抽取一个座位并显示人脸照片

    PointAndName value;

    do
    {
        int count = rand()%num;
        int row = count/6;//行
        int col = count%6;//列
        value.m_x = row;
        value.m_y = col;
        value.name = name;
    }
    while (changeLabelImg(temp,value,1));

    //添加语音播报
    helper.speak(name+"请开始考试");
    QString tips = QString("请在%1行,%2列开始考试").arg(value.m_x+1).arg(value.m_y+1);
    QMessageBox::information(this,"",tips);

    //保存到map容器
    map_users[id] = value;
}
//参数1：Mat face 截取的人脸照片
//参数2：结构体的引用 座位和人的信息
//参数3：判断要选座还是离开 选座1 离开0
//返回值：判定要不要继续生成新座位
bool MainWindow::changeLabelImg(Mat face, PointAndName &v, int flag)
{
    //思考：什么情况需要更改照片 选座 离开
    //什么情况需要生成座位? 离开      不要新生成了
    //                   座位没人坐 不要新生成了
    //                   座位有人坐 新生成

    //1.拿到当前座位的label
    QLayoutItem *item = ui->gridLayout->itemAtPosition(v.m_x,v.m_y);
    QWidget *w = item->widget();
    //通过父类指针获取子类
    QLabel *label = dynamic_cast<QLabel*>(w);

    if(flag == 0)//离开
    {
        label->setText(v.name+"离开了");
        return false;
    }
    QString objName = label->objectName();
    if(objName == "1")//座位被占用
        return true;//新生成

    //没占用 可以使用 修改标志位
    label->setObjectName("1");
    //显示图像
    Mat rgb;
    cvtColor(face,rgb,CV_BGR2RGB);
    QImage img(rgb.data,
               rgb.cols,
               rgb.rows,
               rgb.cols*rgb.channels(),
               QImage::Format_RGB888);
    QPixmap p = QPixmap::fromImage(img);
    //重置图像大小
    p = p.scaled(QSize(60,60));
    label->setPixmap(p);
    return false;
}

void MainWindow::on_pushButton_over_clicked()
{
    //1.找到待预测的人脸照片
    if(find_face.size()==0)
    {
        QMessageBox::warning(this,"","未找到正在考试的人员");
        return;
    }
    Mat dst = src;
    //2.转灰度 重置大小
    cvtColor(dst,dst,CV_BGR2GRAY);
    cv::resize(dst,dst,Size(60,60));
    //3.给人脸识别器 让人脸识别其识别(去xml里做对比)
    int label = -1;
    double confi = 0;//可信度
    recognizer->predict(dst,label,confi);
    qDebug()<<label<<" "<<confi;
    //4.如果预测成功 拿到label 根据标签匹配人名
    QString name = userDao->getName(label);
    //5.弹窗 询问是否结束考试 是 -->修改座位 更新结束时间
    int choose = QMessageBox::question(this,"询问",name+"确定结束考试吗?",QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Ok);
    switch (choose)
    {
    case QMessageBox::Ok:
    {
        //离开 更新数据库的结束考试时间
        userDao->updateEndTime(label);
        //站到对应的座位 改为XXX离开了
        PointAndName value = map_users[label];
        changeLabelImg(Mat(),value,0);
    }
    case QMessageBox::Cancel:
        break;
    default:
        break;

    //添加语音播报
    helper.speak(name+"滚出考场");


    }
}
//导出考生信息
void MainWindow::on_pushButton_export_clicked()
{
    //1.选择想要写入的表格
    QString filename = QFileDialog::getOpenFileName(this,"","E:/QT/1.xlsx");
    qDebug()<<filename;
    //2.打开表格
    ex_helper.open(filename);
    //3.写入标题
    ex_helper.addTitle(filename);
    //4.写入内容
    vector<UserData> v;
    userDao->selectInfo(v);
    ex_helper.addInfos(filename,v);
    //5.关闭
    ex_helper.close();

    QMessageBox::information(this,"","导出成功");
}
