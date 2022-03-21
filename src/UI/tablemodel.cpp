#include "tablemodel.h"

#include "src/Algorithm/statistics.h"
#include "src/Common/message.h"
#include "src/Settings/TableSetting.h"
#include <QMessageBox>
#include <QHeaderView>
#include "QDebug"

static TableModel* INSTANCE=nullptr;
TableModel::TableModel(QObject *parent)
    :QTableView()
{
    Q_UNUSED(parent);
    m_model = new QStandardItemModel(this);
    this->setModel(m_model);
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

TableModel::TableModel(int row, int column)
    :QTableView()
{
    m_model = new QStandardItemModel(row,column);
    this->setModel(m_model);
}
TableModel::~TableModel()
{
    delete this;
}

TableModel *TableModel::getInstance()
{
    if (!INSTANCE) {
        INSTANCE = new TableModel();
    }
    return INSTANCE;
}

int TableModel::rowCount()
{
    return m_model->rowCount();
}

int TableModel::historyRowCount()
{
    return m_historyRowCount;
}
void TableModel::setTableModel(int row, int column, QString cellvalue)
{
    QStandardItem* item = new QStandardItem(cellvalue);
    item->setTextAlignment (Qt::AlignHCenter | Qt::AlignVCenter);
    m_model->setItem(row, column, item);
}

void TableModel::setHeaderModel(int column, QString cellvalue)
{
    QStandardItem* item = new QStandardItem(cellvalue);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_model->setHorizontalHeaderItem(column,item);
}

QStringList TableModel::getHeaderData()
{
    QStandardItem* hItem;
    QStringList headerdata;
    int columnCount = m_model->columnCount();
    for (int i = 0; i < columnCount; ++i)
    {
        hItem=m_model->horizontalHeaderItem(i);
        headerdata.append(hItem->text());
    }
    return headerdata;
}


QStandardItemModel* TableModel::getModel()
{
    return m_model;
}

QList<QList<QStandardItem*>> TableModel::getFilterData(QMap<QString, QString> filterValue)
{
    qDebug() << filterValue;
    int rowCount = m_model->rowCount();
    int columnCount = m_model->columnCount();
    int resRowCount = 0;
    QList<QList<QStandardItem*>> filterData;
    for (int i=0; i<rowCount; i++ ) {
        bool isSelect = this->_getRowDataMap(i,filterValue);
        if (isSelect) {
            QList<QStandardItem*> aItemList;
            for (int j = 0; j < columnCount; j++){
                aItemList.append(m_model->item(i,j));
            }
            filterData.append(aItemList);
            resRowCount++;
        }
    }
    // 添加表头
    QList<QStandardItem*> headerData;
    for (int i=0; i<this->getHeaderData().length(); i++) {
        QStandardItem* item = new QStandardItem(this->getHeaderData()[i]);
        headerData.push_back(item);
    }
    filterData.push_front(headerData);
    return filterData;
}

bool TableModel::_getRowDataMap(int rowIndex, QMap<QString, QString> filterValue)
{
    QString gender = filterValue["gender"];
    QString ageRange = filterValue["ageRange"];  //
    QString stroke = filterValue["stroke"];
    QString strokeItem = filterValue["strokeItem"];
    QString testDateRange = filterValue["testDate"]; //
    QString testEnv = filterValue["testEnv"];
    QString testDistance = filterValue["testDistance"];
    QString team = filterValue["team"];
    QString sportLevel = filterValue["sportLevel"];

    auto tableSetting = TableSetting::getInstance();
    QMap<QString,int> headerIndex = tableSetting->getHeaderIndex();
//    int i_identityIDIndex = headerIndex["identityID_index"];
    int i_strokeIndex = headerIndex["stroke_index"];
    int i_strokeItemIndex = headerIndex["strokeitem_index"];
    int i_genderIndex = headerIndex["gender_index"];
    int i_testDistanceIndex = headerIndex["testdistance_index"];
    int i_testEnvIndex = headerIndex["env_index"];
    int i_teamIndex = headerIndex["team_index"];
    int i_sportLevelIndex = headerIndex["sportlevel_index"];


    QStringList containStr;
    bool isTestEnvEqual = _isValueEqual(testEnv, rowIndex, i_testEnvIndex);
    bool isTestDistanceEqual = _isValueEqual(testDistance,rowIndex, i_testDistanceIndex);
    bool isGenderEqual = _isValueEqual(gender, rowIndex, i_genderIndex);
    bool isStrokeEqual = _isValueEqual(stroke, rowIndex, i_strokeIndex);
    bool isTypeEqual = _isValueEqual(strokeItem, rowIndex, i_strokeItemIndex);
    bool isTeamEqual = _isValueEqual(team, rowIndex, i_teamIndex);
    bool isSportLevelEqual = _isValueEqual(sportLevel, rowIndex, i_sportLevelIndex);

    if (isGenderEqual and isStrokeEqual and isTypeEqual and isTestDistanceEqual
        and isTestEnvEqual and isTeamEqual and isSportLevelEqual) {
        return true;
    } else {
        return false;
    }
}

bool TableModel::_isValueEqual(QString value, int rowIndex, int keyIndex)
{
    QString keyValue = m_model->item(rowIndex, keyIndex)->text();
    if (value == "all") {
        return true;
    } else if (value == keyValue) {
        return true;
    } else {
        return false;
    }
}

void TableModel::setComputedModel()
{
    auto statistics = Statistics::getInstance();
    auto tableSetting = TableSetting::getInstance();

    int rowCount = m_model->rowCount();

    QMap<QString,int> headerIndex = tableSetting->getHeaderIndex();
    int i_maxPowerIndex = headerIndex["maxpower_index"];
    int i_relPowerIndex = headerIndex["relpower_index"];
    int i_maxPower1Index = headerIndex["maxpowerone_index"];
    int i_maxPower2Index = headerIndex["maxpowertwo_index"];
    int i_maxPower3Index = headerIndex["maxpowerthree_index"];
    int i_penPowerIndex = headerIndex["percentage_index"];
    int i_weightIndex = headerIndex["weigth_idnex"];
    int i_identityIDIndex = headerIndex["identityID_index"];
    int i_strokeIndex = headerIndex["stroke_index"];
    int i_strokeItemIndex = headerIndex["strokeitem_index"];
    int i_contributeIndex = headerIndex["contribute_index"];
    QList<int> l_maxPowerIndex;
    l_maxPowerIndex.push_back(i_maxPower1Index);
    l_maxPowerIndex.push_back(i_maxPower2Index);
    l_maxPowerIndex.push_back(i_maxPower3Index);

    // 求最大力和相对力
    for (int i = 0; i < rowCount; i++) {
        QVector<double> v_maxPower;
        for (int j = 0; j < l_maxPowerIndex.length(); j++) {
            QString value = m_model->item(i,l_maxPowerIndex[j])->text();
            v_maxPower.append(value.toDouble());
        }
        QString weight = m_model->item(i,i_weightIndex)->text();
        QString maxPower = statistics->getMaxPower(v_maxPower);
        QString relPower = statistics->getRelativePower(maxPower,weight);
        this->setTableModel(i, i_maxPowerIndex, maxPower);
        this->setTableModel(i, i_relPowerIndex, relPower);
    }
    // 求百分比和贡献率
    QMap<QString,QString> m_rowMaxPowerValue;
    QList<QList<QString>> l_rowMaxPowerValue;
    for (int i = 0; i < rowCount; i++) {
        QString identityIDValue = m_model->item(i,i_identityIDIndex)->text();
        QString strokeValue = m_model->item(i,i_strokeIndex)->text();
        QString typeValue = m_model->item(i,i_strokeItemIndex)->text();
        QString key = identityIDValue + "-" +  strokeValue + "-" + typeValue;

        QList<QString> l_rowData;
        l_rowData.append(key);
        l_rowData.append(m_model->item(i,i_maxPowerIndex)->text());
        l_rowMaxPowerValue.append(l_rowData);
        m_rowMaxPowerValue.insert(key,m_model->item(i,i_maxPowerIndex)->text());
    }
    for (int i = 0; i<l_rowMaxPowerValue.length(); i++){
        QStringList strSplit = l_rowMaxPowerValue.at(i)[0].split("-");
        QString key =maxPowerKeyMap[strSplit[1] + "-" + strSplit[2]];
        QStringList hl  = contributionMap[strSplit[1]].split("-");

        double legValue = m_rowMaxPowerValue[strSplit.at(0) + "-" +strSplit[1] + "-" + hl.value(0)].toDouble();
        double handleValue = m_rowMaxPowerValue[strSplit.at(0) + "-" +strSplit[1] + "-" + hl.value(1)].toDouble();
        qDebug() << strSplit.at(0) + "-" +strSplit[1] + "-" + hl.value(0);
        qDebug() << strSplit.at(0) + "-" +strSplit[1] + "-" + hl.value(1);
        QString key_value = m_rowMaxPowerValue[strSplit.at(0) + "-" +strSplit.at(1) + "-" + key];
        QString percentage,contribute;
        if (key_value == "") {
            percentage = "";
        } else {
            percentage = statistics->getPercentage(l_rowMaxPowerValue.at(i)[1], key_value);
            percentage = QString::number(percentage.toDouble() * 100, 'f', 3) + '%';
        }
        if (legValue+handleValue == 0) {
            contribute = "";
        } else {
            qDebug() << l_rowMaxPowerValue.at(i)[1]<< legValue + handleValue;
            contribute = statistics->getContribute(l_rowMaxPowerValue.at(i)[1], legValue + handleValue);
            contribute = QString::number(contribute.toDouble() * 100, 'f', 3) + '%';
        }
        this->setTableModel(i,i_penPowerIndex,percentage);
        this->setTableModel(i,i_contributeIndex,contribute);
    }
}

void TableModel::addRowData(QList<QStandardItem *> aItemList)
{
    m_historyRowCount += 1;
    m_model->insertRow(m_model->rowCount(),aItemList);
}

void TableModel::delRowData()
{
    auto questionMessage = QuestionMessage::getInstance();
    QString title = tr("删除行数据?");
    QString text = tr("确定要删除这行数据?");
    QItemSelectionModel * selectionModel = this->selectionModel();
    QModelIndex curIndex = selectionModel->currentIndex();
    if (curIndex.row() == m_model->rowCount() -1 and curIndex.row() != -1){ //最后一行
        int ret = questionMessage->sendMessage(title,text);
        if (ret == QMessageBox::Ok) {
            m_model->removeRow(curIndex.row()) ; //删除最后一行
        }
    } else if (curIndex.row() != -1){
        int ret = questionMessage->sendMessage(title,text);
        if (ret == QMessageBox::Ok) {
            m_model->removeRow(curIndex.row());//删除一行，并重新设置当前选择行
            selectionModel->setCurrentIndex (curIndex, QItemSelectionModel::Select);
        }
    }
}


static TableModelManager* INSTANCE_Manager=nullptr;

TableModelManager::TableModelManager(QObject *parent)
{
    Q_UNUSED(parent);
}

TableModelManager *TableModelManager::getInstance()
{
    if (!INSTANCE_Manager) {
        INSTANCE_Manager = new TableModelManager();
    }
    return INSTANCE_Manager;
}

void TableModelManager::createModel()
{
    TableModel* tableModel = new TableModel();
    m_tableModels.push_back(tableModel);
}

void TableModelManager::insertModel(TableModel *tablemodel)
{
    m_tableModels.push_back(tablemodel);
}

void TableModelManager::delModel(int index)
{
    m_tableModels.removeAt(index);
}

QVector<TableModel*> TableModelManager::getALLModels()
{
    return m_tableModels;
}

int TableModelManager::getTableModelCount()
{
    int modelCount = m_tableModels.length();
    return modelCount;
}

TableModel* TableModelManager::getCurTableModel(int Index)
{
    TableModel* tablemodel = m_tableModels.at(Index);
    return tablemodel;
}
