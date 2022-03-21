#include "BaseSetting.h"
#include <QDebug>
#include <QCoreApplication>

BaseSetting::BaseSetting()
{
//    this->readSettings();
//    this->writeSettings();
//    this->_userSettings();
}


void BaseSetting::_userSettings()
{
    m_userSettings = new QSettings(":/config/config/Basic.ini",QSettings::IniFormat);
    m_userSettings->beginGroup("Table");
    m_userSettings->setValue("header","11111");
    m_userSettings->endGroup();
}

void BaseSetting::readSettings()
{
     m_userSettings = new QSettings("/Users/guozeping/Downloads/Swimming/config/Basic.ini",QSettings::IniFormat);
     m_userSettings->setIniCodec(QTextCodec::codecForName("UTF-8"));
     m_userSettings->beginGroup("Table");
     QString size = m_userSettings->value("headerdata","null").toString();
     QString size2 = m_userSettings->value("genderIndex","null").toString();
     qDebug() << size<<size2;
     m_userSettings->endGroup();
}

void BaseSetting::writeSettings()
{
    QSettings* config =  new QSettings("/Users/guozeping/Downloads/Swimming/config/Basic.ini",QSettings::IniFormat);
    config->beginGroup("Table");
    config->setValue("headerdata","22222");
    config->endGroup();
    delete config;
}
