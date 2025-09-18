#include "dbmanager.h"
DbManager* DbManager::instance = nullptr;
DbManager::DbManager()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("music.db");
    db.open();
    createTable();
}


DbManager::DbManager(const DbManager&)
{

}

void DbManager::createTable()
{
    /*
     * 保存用户信息
     * 表名：user_info
     * 字段：id(主键) name password
     * 保存历史纪录
     * 表名：history_iofo
     * 字段：userId关联到用户的id上(主键) userName musicName
     */
    QString sql = "create table if not exists user_info"
                  "(id integer primary key autoincrement,"
                  "name varchar(20),password integer)";
    QSqlQuery query;
    //执行sql语句
    bool ok = query.exec(sql);
    if(ok)
        qDebug()<<"创建用户表成功";
    else
        qDebug()<<"创建用户表失败";

    sql = "create table if not exists history_info"
                  "(userId integer primary key autoincrement,"
                  "userName varchar(20),musicName varchar(20))";
    //执行sql语句
    ok = query.exec(sql);
    if(ok)
        qDebug()<<"创建历史表成功";
    else
        qDebug()<<"创建历史表失败";
}

DbManager *DbManager::getInstance()
{
    if(instance == nullptr)
        instance = new DbManager();
    return instance;
}

DbManager::~DbManager()
{

}

void DbManager::release()
{
    if(instance != nullptr)
    {
        delete instance;
        instance = nullptr;
    }
}

bool DbManager::insertUser(UserData &user)
{
    QString sql = "SELECT count(*) FROM user_info WHERE name = ?;";
    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(0,user.name);
    query.exec();

    int count = -1;
    if(query.next())
    {
        count = query.value(0).toInt();
        if(count>0)
        {
            qDebug()<<"存在了";
            return false;
        }
        //不存在插入
        sql = "INSERT INTO user_info(name,password)VALUES(?,?)";
        query.prepare(sql);
        query.bindValue(0,user.name);
        query.bindValue(1,user.password);
        bool ok = query.exec();
        if(ok)
        {
            qDebug()<<"创建历史记录表成功";
            return true;
        }
        else
        {
            qDebug()<<"创建历史记录表失败";
            return false;
        }
    }
    return false;
}

bool DbManager::selectUser(UserData &user)
{
    QString sql = "SELECT count(*) FROM user_info WHERE name = ? AND password = ?";
    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(0,user.name);
    query.bindValue(1,user.password);
    query.exec();

    int count = -1;
    if(query.next())
    {
        count = query.value(0).toInt();
        if(count>0)
        {
            qDebug()<<count,"存在，登陆成功";
            return true;
        }
    }
    return false;
}

bool DbManager::insertHistoryInfo(QString userName, QString fileName)
{
    QString sql = "INSERT INTO history_info VALUES (0,?,?);";
    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(0,userName);
    query.bindValue(1,fileName);
    bool ok = query.exec();
    if(ok)
        qDebug()<<"历史记录插入成功";
    else
        qDebug()<<"历史记录插入失败";
    return ok;
}

void DbManager::selectHistoryInfo(QString userName, set<QString> &infos)
{
    QString sql = "SELECT musicName FROM history_info WHERE userName = ?;";
    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(0,userName);
    query.exec();
    //提取结果
    while (query.next()) {
        QString name = query.value(0).toString();
        //保存到容器
        infos.insert(name);
    }
    qDebug()<<"历史纪录的个数"<<infos.size();
}

