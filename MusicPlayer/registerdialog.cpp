#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "dbmanager.h"

RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}
//设置全局变量
QString userName;
QString passWord;

//注册按钮
void RegisterDialog::on_pushButton_clicked()
{
    //1.获取输入的账号和密码
    QString userName = ui->lineEdit_name->text();
    QString passWord = ui->lineEdit_pwd->text();
    QString passcfm = ui->lineEdit_cfm->text();
    //2.判空
    if(userName.isEmpty()||passWord.isEmpty()||passcfm.isEmpty())
    {
        QMessageBox::warning(this,"警告","账号或密码不可为空");
        return;
    }
    //3.比较两次输入的密码是否一致
    if(passWord != passcfm)
    {
        qDebug()<<"两次的密码不同";
        return;
    }
    //插入数据库
    DbManager* pd = DbManager::getInstance();
    //4.将当前的账号和密码保存到全局变量中
    UserData user;
    user.name = userName;
    user.password = passWord;

    bool ok = pd->insertUser(user);
    if(ok)
    {
        QMessageBox::information(this," ","注册成功");
        //4.如果注册成功 将用户名和密码 显示到登录窗口
        emit signalInfo(userName,passWord);
        //5.隐藏本窗口
        this->close();
    }
    else{
        QMessageBox::information(this," ","注册失败");
    }

}
