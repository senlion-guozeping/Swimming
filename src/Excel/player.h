#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QFileDialog>
#include <QTableWidget>
#include <QStandardPaths>
#include <QPoint>

#include "xlsxdocument.h"
#include "xlsxworksheet.h"
#include "xlsxcellrange.h"
#include "xlsxformat.h"
#include "xlsxcell.h"

#include "src/UI/tablemodel.h"
#include "src/Common/basictool.h"

class Player: public QObject
{
    Q_OBJECT

public:
    static Player *getInstance();
    Player();
    QList<TableModel*> openXlsx();
    bool saveXlsx(QStandardItemModel* itemModel);
    bool saveFilterXlsx(QStandardItemModel* theResModel,QStandardItemModel* theStatisticalModel, QStandardItemModel* theClusterModel);
    bool exportTemplate(QStringList sl_headerData,QPoint &pos);
    QList<QMap<int, QStringList>> getExcelData();
    int getRowCount();
    int getColumnCount();

private:
    QXlsx::Format m_cellFormat;
    QXlsx::Format m_headerFormat;
    QXlsx::Cell m_cell;
    bool _saveModel(QString filepath, QXlsx::Document& xlsx, QStandardItemModel* model);
    void _setCellFormat();
    void _setHeaderFormat();
    QXlsx::Format _CellFormat();
    QXlsx::Format _HeaderFormat();
};

#endif // PLAYER_H
