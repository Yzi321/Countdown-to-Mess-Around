#include "mainwindow.h"

#include <QApplication>
#include "mainwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    QCoreApplication::setOrganizationName("Yzi321");
    QCoreApplication::setApplicationName(u8"ÃþÓãµ¹¼ÆÊ±");
    QApplication::setQuitOnLastWindowClosed(false);
    MainWidget mainWidget;
    mainWidget.show();

    return a.exec();
}
