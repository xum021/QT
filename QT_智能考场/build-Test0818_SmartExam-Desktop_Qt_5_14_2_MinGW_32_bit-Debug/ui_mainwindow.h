/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label_course;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_face;
    QLineEdit *lineEdit;
    QPushButton *pushButton_choose;
    QPushButton *pushButton_over;
    QPushButton *pushButton_export;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(964, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label_course = new QLabel(centralwidget);
        label_course->setObjectName(QString::fromUtf8("label_course"));
        label_course->setGeometry(QRect(30, 10, 581, 41));
        label_course->setStyleSheet(QString::fromUtf8("font: 18pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(30, 60, 601, 471));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_face = new QLabel(centralwidget);
        label_face->setObjectName(QString::fromUtf8("label_face"));
        label_face->setGeometry(QRect(650, 59, 300, 251));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(650, 410, 291, 41));
        pushButton_choose = new QPushButton(centralwidget);
        pushButton_choose->setObjectName(QString::fromUtf8("pushButton_choose"));
        pushButton_choose->setGeometry(QRect(650, 460, 141, 31));
        pushButton_over = new QPushButton(centralwidget);
        pushButton_over->setObjectName(QString::fromUtf8("pushButton_over"));
        pushButton_over->setGeometry(QRect(800, 460, 141, 31));
        pushButton_export = new QPushButton(centralwidget);
        pushButton_export->setObjectName(QString::fromUtf8("pushButton_export"));
        pushButton_export->setGeometry(QRect(650, 500, 291, 31));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 964, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_course->setText(QCoreApplication::translate("MainWindow", "XX\350\200\203\350\257\225", nullptr));
        label_face->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        lineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\257\267\350\276\223\345\205\245\350\200\203\347\224\237\345\247\223\345\220\215", nullptr));
        pushButton_choose->setText(QCoreApplication::translate("MainWindow", "\351\200\211\345\272\247", nullptr));
        pushButton_over->setText(QCoreApplication::translate("MainWindow", "\347\246\273\345\274\200", nullptr));
        pushButton_export->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\207\272\350\200\203\347\224\237\344\277\241\346\201\257", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
