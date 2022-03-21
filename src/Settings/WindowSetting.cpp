#include "WindowSetting.h"

static WindowSetting* INSTANCE=nullptr;

WindowSetting *WindowSetting::getInstance()
{
    if (!INSTANCE) {
        INSTANCE = new WindowSetting();
    }
    return INSTANCE;
}

WindowSetting::WindowSetting()
{
    m_windowSetting = new QSettings("/Users/guozeping/Downloads/Swimming/config/Basic.ini",QSettings::IniFormat);
}

WindowSetting::~WindowSetting()
{
    delete this;
}

QPoint WindowSetting::getTipPos(QMainWindow* mainWindow)
{
    int width = mainWindow->width();
    QPoint pos(mainWindow->geometry().x() + width,mainWindow->geometry().y());
    return pos;
}
