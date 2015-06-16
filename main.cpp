#include "transparentwindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TransparentWindow w;
    return a.exec();
}
