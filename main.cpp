#include "mainwindow.h"
#include <QApplication>

#include "src/Common/modulemanager.h"
#include "src/Common/log.h"

int main(int argc, char *argv[])
{   
    QApplication a(argc, argv);
    MainWindow w;
    // 初始化模块管理类
    auto moduleManager = new ModuleManager();
    moduleManager->initModuleInstance();
    qInstallMessageHandler(myMessageOutput);
    w.show();
    return a.exec();
}
