#ifndef WINDOWSETTING_H
#define WINDOWSETTING_H

#include <QPoint>
#include <QMainWindow>
#include "src/Settings/BaseSetting.h"

class WindowSetting: public BaseSetting
{
    QSettings* m_windowSetting;
public:
    static WindowSetting *getInstance();
    WindowSetting();
    ~WindowSetting();

    QPoint getTipPos(QMainWindow* mainWindow);
};

#endif // WINDOWSETTING_H
