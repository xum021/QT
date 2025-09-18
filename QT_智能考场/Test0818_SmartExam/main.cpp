#include "coursedialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CourseDialog w;
    w.show();
    return a.exec();
}
