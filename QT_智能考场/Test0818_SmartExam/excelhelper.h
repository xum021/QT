#ifndef EXCELHELPER_H
#define EXCELHELPER_H

#include <QAxObject>
#include <vector>
#include"userdao.h"
using namespace std;

class ExcelHelper
{
public:
    void open(QString file);
    void close();
    void  addInfos(QString fileName,vector<UserData>& v);
    void addTitle(QString fileName);
private:
    QAxObject *excel = 0;    //excel设定为Excel文件的操作对��?
    QAxObject *workbooks = 0;
    QAxObject *workbook = 0;  //Excel操作对象
    QAxObject *worksheets = 0;//所有工作表
    QAxObject *worksheet = 0;//第一个工作表

    int cols;//列数
    int rows;//行数
};

#endif // EXCELHELPER_H
