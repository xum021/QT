/********************************************************************************
** Form generated from reading UI file 'coursedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COURSEDIALOG_H
#define UI_COURSEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CourseDialog
{
public:
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QComboBox *comboBox;
    QPushButton *pushButton;

    void setupUi(QDialog *CourseDialog)
    {
        if (CourseDialog->objectName().isEmpty())
            CourseDialog->setObjectName(QString::fromUtf8("CourseDialog"));
        CourseDialog->resize(515, 374);
        label = new QLabel(CourseDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(160, 10, 191, 51));
        label->setStyleSheet(QString::fromUtf8("font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font: 18pt \"Arial\";"));
        lineEdit = new QLineEdit(CourseDialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(140, 80, 241, 31));
        label_2 = new QLabel(CourseDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(140, 120, 91, 31));
        comboBox = new QComboBox(CourseDialog);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(260, 120, 121, 31));
        pushButton = new QPushButton(CourseDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(140, 260, 251, 71));

        retranslateUi(CourseDialog);

        QMetaObject::connectSlotsByName(CourseDialog);
    } // setupUi

    void retranslateUi(QDialog *CourseDialog)
    {
        CourseDialog->setWindowTitle(QCoreApplication::translate("CourseDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("CourseDialog", "\346\254\242\350\277\216\350\277\233\345\205\245\346\231\272\350\203\275\350\200\203\345\234\272", nullptr));
        lineEdit->setPlaceholderText(QCoreApplication::translate("CourseDialog", "\350\257\267\350\276\223\345\205\245\350\200\203\350\257\225\347\247\221\347\233\256", nullptr));
        label_2->setText(QCoreApplication::translate("CourseDialog", "\345\217\202\350\200\203\344\272\272\346\225\260\357\274\232", nullptr));
        pushButton->setText(QCoreApplication::translate("CourseDialog", "\345\274\200\345\247\213\350\200\203\350\257\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CourseDialog: public Ui_CourseDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COURSEDIALOG_H
