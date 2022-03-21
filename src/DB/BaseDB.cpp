#include "BaseDB.h"

Base::Base()
{
    m_driver = QSqlDatabase::addDatabase("QSQLITE");
    m_driver.setDatabaseName(QApplication::applicationDirPath()+"/scooters.dat");
}
