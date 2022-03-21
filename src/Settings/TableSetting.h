#ifndef TABLESETTING_H
#define TABLESETTING_H

#include "src/Settings/BaseSetting.h"

class TableSetting: public BaseSetting
{
private:
    QSettings* m_tableSetting;
public:
    static TableSetting *getInstance();
    TableSetting();
    ~TableSetting();

    QStringList getTableHeaderData();
    QStringList getSportLevel() const;
    QStringList getEnv() const;
    QStringList getTestDintance() const;
    QStringList getTeam() const;
    QStringList getTrainStage() const;
    QStringList getStatisticalRowHeader() const;
    QStringList getStaticticalColHeader() const;

    const QMap<QString,int> getHeaderIndex() const;
    const QStringList getStroke() const;
    const QMap<QString,QStringList> getStrokeItem() const;

};

#endif // TABLESETTING_H
