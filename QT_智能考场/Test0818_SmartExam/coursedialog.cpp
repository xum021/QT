#include "coursedialog.h"
#include "ui_coursedialog.h"

CourseDialog::CourseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CourseDialog)
{
    ui->setupUi(this);
    //使下拉菜单显示考试人数
    for(int i=30;i<=50;i++)
    {
        ui->comboBox->addItem(QString::number(i));
    }
}

CourseDialog::~CourseDialog()
{
    delete ui;
}

void CourseDialog::on_pushButton_clicked()
{
    //1.获取考试名称和考试人数
    QString course = ui->lineEdit->text();
    int num = ui->comboBox->currentText().toInt();
    //2.判空
    if(course.isEmpty())
    {
        //提示
        QMessageBox::warning(this,"警告","请输入考试名称");
        return;
    }
    //3.将考试名称和参考人数传递给主窗口
    MainWindow *mw = new MainWindow(course,num);
//    connect(this,&CourseDialog::sendInfo,mw,);
//    emit sendInfo(course,num);
    //4.显示主窗口并关闭当前窗口
    mw->show();
    this->close();
}
