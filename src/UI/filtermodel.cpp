#include "filtermodel.h"
#include "ui_filtermodel.h"
#include "QDebug"


#include "src/Settings/TableSetting.h"
#include "src/Algorithm/statistics.h"

static FilterModel* INSTANCE=nullptr;

FilterModel::FilterModel(QWidget* parent):
    QDialog(parent),
    ui(new Ui::FilterModel)
{
    ui->setupUi(this);
    Qt::WindowFlags flags=Qt::Dialog;
    flags |=Qt::WindowMinMaxButtonsHint;
    flags |=Qt::WindowCloseButtonHint;
    setWindowFlags(flags);


    theResModel = new QStandardItemModel(this);
    theSelModel = new QItemSelectionModel(theResModel);
    theStatisticalModel = new QStandardItemModel(this);
    theClusterModel = new QStandardItemModel(this);

    ui->resView->setModel(theResModel);
    ui->resView->setSelectionModel(theSelModel);
    ui->statistical_view->setModel(theStatisticalModel);
    ui->cluster_view->setModel(theClusterModel);

    this->_initStatisticalView();
    ui->statistical_view->hide();
    ui->cluster_view->hide();
    ui->setting_widget->hide();
    ui->maxPower_checkBox->setCheckState(Qt::Checked);


    connect(ui->settingTb,SIGNAL(clicked()),this,SLOT(on_settingClicked()));
    connect(ui->clusterTb,SIGNAL(clicked()),this,SLOT(on_clusterClicked()));
    connect(ui->saveTb,SIGNAL(clicked()),this,SLOT(on_saveClicked()));
    connect(ui->statisticalTb,SIGNAL(clicked()),this,SLOT(on_statisticalClicked()));
}
FilterModel::~FilterModel()
{
    delete ui;
}

FilterModel *FilterModel::getInstance()
{
    if (!INSTANCE) {
        INSTANCE = new FilterModel();
    }
    return INSTANCE;
}

void FilterModel::_initStatisticalView()
{
    auto tableSetting = TableSetting::getInstance();
    QStringList rowHeader = tableSetting->getStatisticalRowHeader();
    QStringList columnHeader = tableSetting->getStaticticalColHeader();
    ui->statistical_view->setMinimumWidth(this->width() / 3);
    for (int i=0; i<rowHeader.length(); i++) {// 设置行表头
        theStatisticalModel->setHorizontalHeaderItem(i,new QStandardItem(rowHeader[i]));
    }
    for (int i=0; i<columnHeader.length(); i++) {
        theStatisticalModel->setVerticalHeaderItem(i, new QStandardItem(columnHeader[i]));
    }
}

void FilterModel::setResModel(QList<QList<QStandardItem*>> filterData)
{
    // 清空筛选结果的模型
    theResModel->clear();
    // 设置筛选结果的模型
    for (int i = 0; i < filterData.length(); ++i) {
            for (int j = 0; j < filterData[i].length(); ++j) {
                if (i == 0) {// 表头
                    theResModel->setHorizontalHeaderItem(j, filterData[i][j]);
                } else if (i >= 1) {
                    QStandardItem* item = new QStandardItem(filterData[i][j]->text());
                    item->setTextAlignment(Qt::AlignCenter);
                    theResModel->setItem(i-1,j,item);
            }
        }
    }
    _setRowCount(theResModel->rowCount());
    _setColumnCount(theResModel->columnCount());
    _setClusterNumItem();
}



int FilterModel::_getK()
{
    int i_clusterNum;
    QString s_clusterNum = ui->selClusterNum->currentText();
    if (s_clusterNum == "请选择") {
        int rowCount = _rowCount();
        if (rowCount < 3) {
            i_clusterNum = rowCount;
        } else {
            i_clusterNum = 3;
        }
    } else {
        i_clusterNum = s_clusterNum.toInt();
    }
    return i_clusterNum;
}




int FilterModel::_columnCount()
{
    return m_columnCount;
}

int FilterModel::_rowCount()
{
    return m_rowCount;
}

void FilterModel::_setColumnCount(int columnCount)
{
    m_columnCount = columnCount;
}

void FilterModel::_setRowCount(int rowCount)
{
    m_rowCount = rowCount;
}

void FilterModel::_setClusterNumItem()
{
    ui->selClusterNum->clear();
    ui->selClusterNum->addItem("请选择");
    if (_rowCount() < 3 and _rowCount() > 0) {
        for (int i=1; i< _rowCount() + 1; i++) {
            ui->selClusterNum->addItem(QString::number(i));
        }
    }
    if (_rowCount() >= 3) {
        for (int i=3; i< _rowCount() + 1; i++) {
            ui->selClusterNum->addItem(QString::number(i));
        }
    }
}

void FilterModel::on_settingClicked()
{
    int width = this->geometry().width() * 0.3;
    ui->setting_widget->setFixedWidth(width);
    bool isHideen = ui->setting_widget->isHidden();
    if (isHideen) {
        ui->setting_widget->show();
    } else {
        ui->setting_widget->hide();
    }
}

void FilterModel::on_saveClicked()
{
    auto player = Player::getInstance();
    bool isSave = player->saveFilterXlsx(theResModel,theStatisticalModel,theClusterModel);
    if (isSave) {
        qDebug() << "保存成功";
    }
}

void FilterModel::on_clusterClicked()
{
    if (_rowCount() == 0) {
        qDebug() << "无行数可以聚类";
        return;
    }
    if (_rowCount() > 0) {
        // 增加聚类列
        QStandardItem* cItem = new QStandardItem("所属类");
        theResModel->setHorizontalHeaderItem(_columnCount(), cItem);

        // 聚类
        int K = _getK();
        int iters = 100;
        vector<Point> all_points;
        for (int i = 0; i < _rowCount(); ++i) {
            std::stringstream sstream = this->_clusterValuseSelMap(i);
            Point point(i, sstream.str());
            all_points.push_back(point);
        }

        Kmeans kmeans(K, iters);
        kmeans.run(all_points);

        for (int i=0; i<K; i++)
        {// 写入结果
            int size = kmeans.clusters[i].getSize(); //某类有几个点
            for (int j = 0; j < size; j++)
            {
                int row_index = kmeans.clusters[i].getPoint(j).getID();
                QStandardItem* aItem = new QStandardItem(QString::number(i+1));
                theResModel->setItem(row_index, _columnCount(),aItem);
            }
        }
        // 写中心点
        ui->cluster_view->show();
        vector<int> centorPoint = kmeans.getCenterPoint();
        int rowCount = centorPoint.size();
        for (int i=0; i<rowCount; i++){
            int rowSerial = centorPoint[i];
            QString rowHeader = QString("第%1类中心点数据").arg(i+1);
            theClusterModel->setVerticalHeaderItem(i,new QStandardItem(rowHeader));
            for (int j=0; j<theResModel->columnCount(); j++) {// 设置数据
                theClusterModel->setHorizontalHeaderItem(j,new QStandardItem(theResModel->horizontalHeaderItem(j)->text()));
                theClusterModel->setItem(i,j,new QStandardItem(theResModel->item(rowSerial,j)->text()));
            }
        }
    }
}

void FilterModel::on_statisticalClicked()
{
    qDebug() << "统计数据";
    ui->statistical_view->show();
    auto tableSetting = TableSetting::getInstance();
    QMap<QString,int> headerIndex = tableSetting->getHeaderIndex();
    int i_maxpower_index = headerIndex["maxpower_index"];
    int i_relpower_index = headerIndex["relpower_index"];
    int i_percentage_index = headerIndex["percentage_index"];
    int i_contribute_index = headerIndex["contribute_index"];

    QVector<double> maxPower,relPower,percentage,contribute;

    for (int i=0; i<theResModel->rowCount(); i++) {
        maxPower.push_back(theResModel->item(i,i_maxpower_index)->text().toDouble());
        relPower.push_back(theResModel->item(i,i_relpower_index)->text().toDouble());
        QString percenageValue = theResModel->item(i,i_percentage_index)->text();
        QString contributeValue = theResModel->item(i,i_contribute_index)->text();
        if (percenageValue != "") {
             percenageValue = percenageValue.remove('%');
        }
        if (contributeValue !="") {
            contributeValue = contributeValue.remove('%');
        }
        percentage.push_back(percenageValue.toDouble() / 100);
        contribute.push_back(contributeValue.toDouble() / 100);
    }

    QVector<QVector<double>> statisticData;
    statisticData.push_back(maxPower);
    statisticData.push_back(relPower);
    statisticData.push_back(percentage);
    statisticData.push_back(contribute);
    for (int i=0; i<theStatisticalModel->columnCount(); i++) {
        QVector<double> vec = statisticData[i];
        QVector<QString> statistics_res = this->_getStatistical(vec);
        for (int j=0; j<theStatisticalModel->rowCount(); j++) {
            QStandardItem* item = new QStandardItem(statistics_res[j]);
            item->setTextAlignment(Qt::AlignCenter);
            theStatisticalModel->setItem(j,i,item);
        }
    }
}

stringstream FilterModel::_clusterValuseSelMap(int rowIndex)
{
    std::string  nullStr = " ";
    auto tableSetting = TableSetting::getInstance();
    QMap<QString,int> headerIndex = tableSetting->getHeaderIndex();
    int i_maxPowerIndex = headerIndex["maxpower_index"];
    int i_relPowerIndex = headerIndex["relpower_index"];
    int i_percentageIndex = headerIndex["percentage_index"];
    int i_contributeIndex = headerIndex["contribute_index"];
    std::stringstream sstream;
    bool isSelMaxPower = ui->maxPower_checkBox->isChecked();
    if (isSelMaxPower) {
        QString value = theResModel->item(rowIndex,i_maxPowerIndex)->text();
        sstream<< value.toStdString();
    }
    bool isSelRelPower   =  ui->relPower_checkBox->isChecked();
    if (isSelRelPower) {
        QString value = theResModel->item(rowIndex,i_relPowerIndex)->text();
        sstream<< nullStr + value.toStdString();
    }
    bool isSelPerage = ui->perage_checkBox->isChecked();
    if (isSelPerage) {
        QString value = theResModel->item(rowIndex,i_percentageIndex)->text();
        if (value != "") {
            double value_d = value.remove("%").toDouble();
            value = QString::number(value_d / 100);
        }
        sstream<< nullStr+ value.toStdString();
    }
    bool isSelContribution = ui->contribution_checkBox->isChecked();
    if (isSelContribution) {
        QString value = theResModel->item(rowIndex,i_contributeIndex)->text();
        if (value != ""){
            double value_d = value.remove("%").toDouble();
            value = QString::number(value_d / 100);
        }
        sstream<< nullStr + value.toStdString();
    }
    return sstream;
}

QVector<QString> FilterModel::_getStatistical(QVector<double> vec)
{
    auto statistics = Statistics::getInstance();
    QVector<QString> statistics_res;
    QString maxValue = statistics->getMaxValue(vec);
    QString minVluae = statistics->getMinValue(vec);
    QString averageValue = statistics->getAverageValue(vec);
    QString standardValue = statistics->getStandardDev(vec);
    statistics_res.push_back(maxValue);
    statistics_res.push_back(minVluae);
    statistics_res.push_back(averageValue);
    statistics_res.push_back(standardValue);
    qDebug() << statistics_res;
    return statistics_res;
}
