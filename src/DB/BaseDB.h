#ifndef BASEDB_H
#define BASEDB_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QApplication>
class Base
{
private:
    QSqlDatabase m_driver;
public:
    Base();
};

#endif // BASEDB_H
