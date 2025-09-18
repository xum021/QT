#ifndef USERDAO_H
#define USERDAO_H

#include<QSqlDatabase>//数据库对象
#include<QSqlQuery>//执行数据库语句
#include<QDebug>
#include<QDateTime>//代表时间
#include<vector>
using namespace std;

struct UserData
{
    int id;
    QString name;
    QDateTime start;
    QDateTime end;
};

class UserDao
{
    //1.私有化构造函数和拷贝构造 禁止类外创建对象
    UserDao();
    UserDao(const UserDao& other);
    //2.私有的静态的类内指针
    static UserDao *userdao;
    QSqlDatabase db;
public:
    //3.共有的静态类内函数返回类指针
    static UserDao* getUser();
    ~UserDao();
    void creatTable();
    //插入数据
    void insertUser(QString name);
    //返回用户id的
    int getUserId();
    //根据id找到姓名
    QString getName(int id);
    //更新考试结束的时间
    void updateEndTime(int id);
    //提取所有信息
    void selectInfo(vector<UserData> &v);
};

#endif // USERDAO_H
