#ifndef DBMANAGER_H
#define DBMANAGER_H
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QDebug>
#include<set>
using namespace std;

struct UserData
{
    int id;
    QString name;
    QString password;
};

struct History
{
    int userid;
    QString username;
    QString musicname;
};

class DbManager
{
    DbManager();
    DbManager(const DbManager&);
    static DbManager *instance;
public:
//    DbManager();
    QSqlDatabase db;
    void createTable();
    static DbManager *getInstance();
    ~DbManager();
    static void release();
    bool insertUser(UserData& user);
    bool selectUser(UserData &user);
    bool insertHistoryInfo(QString userName,QString fileName);
    void selectHistoryInfo(QString userName,set<QString> &infos);

};

#endif // DBMANAGER_H
