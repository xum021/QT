#include "userdao.h"

//类外初始化
UserDao* UserDao::userdao = nullptr;

UserDao::UserDao()
{
        //配置数据库 加载数据库驱动：连接哪个数据库
        db = QSqlDatabase::addDatabase("QSQLITE");
        //2.设置数据库文件的名称
        db.setDatabaseName("face.db");
        //3.打开数据库
        db.open();
        //4.创建表
        creatTable();
}

UserDao::UserDao(const UserDao &other)
{

}

UserDao *UserDao::getUser()
{
    if(userdao == nullptr)
        userdao = new UserDao;
    return userdao;
}

UserDao::~UserDao()
{
    db.close();
}

void UserDao::creatTable()
{
    QString sql = "create table if not exists user_info"
                  "(id integer primary key autoincrement,"
                  "name varchar(20),"
                  "start datetime,"
                  "end datetime)";
    QSqlQuery query;
    //执行sql语句
    bool ok = query.exec(sql);
    if(ok)
        qDebug()<<"创建表成功";
    else
        qDebug()<<"创建表失败";
}

void UserDao::insertUser(QString name)
{
    QString sql = "INSERT INTO user_info(name,start,end)"
                  "VALUES( ? ,datetime('now','localtime'),"
                  "datetime('now','localtime'))";
    //1.执行数据库语句的对象
    QSqlQuery query;
    //2.prepare
    query.prepare(sql);
    //3.绑定值
    query.bindValue(0,name);
    //4.执行 并判断是否成功
    bool ok = query.exec();
    if(ok)
        qDebug()<<"insert succ";
    else
        qDebug()<<"insert fail";

}

int UserDao::getUserId()
{
    QString sql = "SELECT last_insert_rowid()";
    QSqlQuery query;
    bool ok = query.exec(sql);
    int id = 1;
    if(query.next())//如果存在下一条记录
    {
        id = query.value(0).toInt();
        qDebug()<<"id is"<<id;
    }
    return id;
}

QString UserDao::getName(int id)
{
    QString sql = "SELECT name FROM user_info WHERE id = ? ";
    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(0,id);
    query.exec();

    QString name;
    if(query.next())
    {
        name = query.value(0).toString();
    }
    return name;
}

void UserDao::updateEndTime(int id)
{
    QString sql = "UPDATE user_info SET end = datetime('now','localtime') WHERE id = ? ";
    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(0,id);
    bool ok = query.exec();
    if(ok)
    {
        qDebug()<<"update succ";
    }
    else
        qDebug()<<"update faile";
}

void UserDao::selectInfo(vector<UserData> &v)
{
    QString sql = "SELECT * FROM user_info";
    QSqlQuery query;
    query.exec(sql);
    while(query.next())
    {
        //提取一行信息
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QDateTime start = query.value(2).toDateTime();
        QDateTime end = query.value(3).toDateTime();

        //结构体对象
        UserData user;
        user.id = id;
        user.name = name;
        user.start = start;
        user.end = end;

        v.push_back(user);
    }
}
