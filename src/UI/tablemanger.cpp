#include "tablemanger.h"
static TableManger* INSTANCE=nullptr;
TableManger::TableManger()
{

}

TableManger *TableManger::getInstance()
{
    if (!INSTANCE) {
        INSTANCE = new TableManger();
    }
    return INSTANCE;
}

void TableManger::addRow()
{

}
