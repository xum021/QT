#ifndef COURSEDIALOG_H
#define COURSEDIALOG_H

#include <QDialog>
#include<QComboBox>
#include<QMessageBox>
#include"mainwindow.h"

namespace Ui {
class CourseDialog;
}

class CourseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CourseDialog(QWidget *parent = nullptr);
    ~CourseDialog();

signals:
    void sendInfo(QString cour,int n);

private slots:
    void on_pushButton_clicked();

private:
    Ui::CourseDialog *ui;
};

#endif // COURSEDIALOG_H
