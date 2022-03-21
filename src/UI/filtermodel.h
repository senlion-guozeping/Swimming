#ifndef SELDATA_H
#define SELDATA_H
#include <QDialog>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QTableView>
#include <QToolBar>
#include <QAction>
#include <QFile>
#include <sstream>

#include "src/Algorithm/kmeans.h"
#include "src/Excel/player.h"

namespace Ui {
class FilterModel;
class Point;
class Cluster;
class KMeans;
class FilterSettings;
}

class FilterModel: public QDialog
{
    Q_OBJECT
public:
    static FilterModel *getInstance();
    explicit FilterModel(QWidget *parent = nullptr);
    ~FilterModel();
    void setResModel(QList<QList<QStandardItem*>> filterData);

private:
    int m_rowCount;
    int m_columnCount;

    QStandardItemModel* theResModel;
    QStandardItemModel* theClusterModel;
    QStandardItemModel* theStatisticalModel;
    QItemSelectionModel *theSelModel;

    int _getK();
    int _columnCount();
    int _rowCount();
    void _setColumnCount(int columnCount);
    void _setRowCount(int rowCount);
    void _setClusterNumItem();
    void _initStatisticalView();
    stringstream _clusterValuseSelMap(int rowIndex);
    QVector<QString> _getStatistical(QVector<double> vec);

private slots:
    void on_clusterClicked();
    void on_saveClicked();
    void on_settingClicked();
    void on_statisticalClicked();

public:
    Ui::FilterModel *ui;
    Ui::FilterSettings *settingUi;
};

#endif // SELDATA_H
