#ifndef BASESETTING_H
#define BASESETTING_H

#include <QSettings>
#include <QFileInfo>
#include <QTextCodec>

class BaseSetting: public QSettings
{
private:
    QSettings* m_basicSettings;
    QSettings* m_userSettings;
    void _userSettings();
public:
    BaseSetting();
    void writeSettings();
    void readSettings();

};

#endif // BASESETTING_H
