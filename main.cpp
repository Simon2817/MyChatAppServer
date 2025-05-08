#include "adminloginpage.h"

#include <QApplication>
#include <mainwindow.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AdminLoginPage *adminLoginPage = AdminLoginPage::getInstance();
    MainWindow *mainWindow = MainWindow::getInstance();
    return a.exec();
}
