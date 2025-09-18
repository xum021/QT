#include "logindialog.h"
#include "ui_logindialog.h"

//引入全局变量
extern QString userName;
extern QString passWord;

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
//    mw = new MainWindow(this);
//    connect(this,&LoginDialog::slot_signalinfo,mw,&RegisterDialog::signalInfo);
//    connect(ui->pushButton_login,&QPushButton::clicked,
//            this,&LoginDialog::slot_btn);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::slot_signalinfo(QString name, QString pwd)
{
    ui->lineEdit_user_name->setText(name);
    ui->lineEdit_password->setText(pwd);
}

void LoginDialog::on_pushButton_register_clicked()
{
    RegisterDialog *rd = new RegisterDialog(this);
    connect(rd,&RegisterDialog::signalInfo,this,&LoginDialog::slot_signalinfo);
    rd->show();
}
//登录
void LoginDialog::on_pushButton_login_clicked()
{
    //1.获取到输入的账号和密码
    QString userName = ui->lineEdit_user_name->text();
    QString passWord = ui->lineEdit_password->text();
    if(userName.isEmpty())
    {
        QMessageBox::information(this," ","账号不能为空");
        return;
    }
    if(passWord.isEmpty())
    {
        QMessageBox::information(this," ","密码不能为空");
        return;
    }
    //2.用输入的和全局变量作比较
    UserData user;
    user.name = userName;
    user.password = passWord;
    bool ok = DbManager::getInstance()->selectUser(user);
//    if(userName == ::userName && passWord == ::passWord)
//    {
    if(ok)
    {
    //3.创建MainWindow并显示
        MainWindow *mw = new MainWindow(userName);
        mw->show();
            //4.关闭当前窗口
        this->close();
    }
    else
//        qDebug()<<"账号或密码错误";
        QMessageBox::information(this," ","登陆失败");
}
