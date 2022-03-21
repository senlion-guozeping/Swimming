#include "player.h"
#include <QDebug>

#include "src/Common/message.h"
#include "src/Settings/TableSetting.h"

using namespace QXlsx;

static Player* INSTANCE=nullptr;

Player::Player()
{
    this->_setCellFormat();
    this->_setHeaderFormat();
}

Player *Player::getInstance()
{
    if (!INSTANCE) {
        INSTANCE = new Player();
    }
    return INSTANCE;
}

QList<TableModel*> Player::openXlsx()
{
    QString filePath = QFileDialog::getOpenFileName(0, "Open xlsx file", QString(), "*.xlsx");
    QList<TableModel*> tablemodels;

    if (!filePath.isEmpty()) {
        Document xlsx(filePath);
        QString cellValue;
        foreach (QString sheetName, xlsx.sheetNames()) {
            Worksheet *sheet = dynamic_cast<Worksheet *>(xlsx.sheet(sheetName));
            TableModel* tablemodel = new TableModel();
            tablemodels.push_back(tablemodel);
            int rowCount = sheet->dimension().rowCount();
            int columnCount = sheet->dimension().columnCount();

            QMap<int,QStringList> sheetData;
            for (int i = 1; i < rowCount + 1; i++) {
                QStringList rowData;
                for (int j = 1; j < columnCount + 1; j++) {
                    QXlsx::Cell *cell = sheet->cellAt(i, j);
                    if (cell == NULL){
                        cellValue = "";
                    } else  {
                        cellValue = cell->value().toString();
                        if(cellValue.toDouble()){
                            cellValue = QString::number(cellValue.toDouble(),'f', 2);
                        }
                    }
                    // 设置tablemodel
                    if (i == 1){
                        tablemodel->setHeaderModel(j - 1,cellValue);
                    } else {
                        tablemodel->setTableModel(i - 2,j - 1,cellValue);
                    }
                    rowData.append(cellValue);
                }
                sheetData.insert(i,rowData);
            }
        }
    }

    return tablemodels;
}

bool Player::saveXlsx(QStandardItemModel *itemModel)
{
    QXlsx::Document xlsx;
    QString filepath = QFileDialog::getSaveFileName(NULL, "save xlsx file", "", "xlsx(*.xlsx)");
    if (filepath != "") {
        this->_saveModel(filepath,xlsx,itemModel);
    }
    return true;
}

bool Player::saveFilterXlsx(QStandardItemModel *theResModel, QStandardItemModel *theStatisticalModel, QStandardItemModel *theClusterModel)
{
    QXlsx::Document xlsx;
    QString filepath = QFileDialog::getSaveFileName(NULL, "save xlsx file", "", "xlsx(*.xlsx)");
    if (filepath != "") {
        if (!xlsx.selectSheet("Sheet1")) {
            xlsx.addSheet("Sheet1");
            this->_saveModel(filepath,xlsx,theResModel);
        } else {
            this->_saveModel(filepath,xlsx,theResModel);
        }
        if(!xlsx.selectSheet("Sheet2")){
            xlsx.addSheet("Sheet2");
            this->_saveModel(filepath,xlsx,theStatisticalModel);
        } else {
            this->_saveModel(filepath,xlsx,theStatisticalModel);
        }
        if (!xlsx.selectSheet("Sheet3")) {
            xlsx.addSheet("Sheet3");
            this->_saveModel(filepath,xlsx, theClusterModel);
        } else {
            this->_saveModel(filepath,xlsx, theClusterModel);
        }
    }
    return true;
}

bool Player::exportTemplate(QStringList sl_headerData,QPoint &pos)
{
    QString filename = "template.xlsx";
    QString location = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString filepath = location + "/"  + filename;
    QXlsx::Document xlsx;
    for (int i = 0; i<sl_headerData.length(); i++) {
        xlsx.write(1, i + 1, sl_headerData.at(i), _HeaderFormat());
    }
    bool isSave = xlsx.saveAs(filepath);
    if (isSave) {
        QString text = "导出模版成功";
        TipMessage::sendTipInfo(text,pos);
        return true;
    } else {
        QString text = "导出模版失败";
        TipMessage::sendTipInfo(text,pos);
        return false;
    }
}

bool Player::_saveModel(QString filepath, QXlsx::Document& xlsx, QStandardItemModel *model)
{
    int columnCount = model->columnCount();
    int rowCount = model->rowCount();
    // 表头数据
    for (int i = 0; i < columnCount; i++) {
       QString headerValue = model->horizontalHeaderItem(i)->text();
       xlsx.write(1, i + 1, headerValue, _HeaderFormat());
    }
    // 数据区
    for (int i = 1; i < rowCount + 1; i++)
    {
        for (int j = 0; j < columnCount; j++)
        {
            QString cellValue = model->item(i - 1, j)->text();
            xlsx.write(i + 1, j + 1, cellValue, _CellFormat());
        }
    }
    xlsx.saveAs(filepath);
    return true;
}

void Player::_setCellFormat()
{
    m_cellFormat.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
}

void Player::_setHeaderFormat()
{
    m_headerFormat.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
}

QXlsx::Format Player::_CellFormat()
{
    return m_cellFormat;
}

QXlsx::Format Player::_HeaderFormat()
{
    return m_headerFormat;
}

