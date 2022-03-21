#ifndef TABLEMANGER_H
#define TABLEMANGER_H

#include <QObject>
class TableManger: public QObject
{
    Q_OBJECT
public:
    static TableManger *getInstance();
    TableManger();
    void addRow();
    void deleteRow();
};

#endif // TABLEMANGER_H
