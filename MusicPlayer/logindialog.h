#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include"registerdialog.h"
#include<mainwindow.h>
#include"dbmanager.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private slots:
    void on_pushButton_register_clicked();

    void on_pushButton_login_clicked();

    void slot_signalinfo(QString name,QString pwd);

private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
