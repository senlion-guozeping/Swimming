#ifndef TABLEMODEL_H
#define TABLEMODEL_H
#include <QObject>
#include <QRegExp>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QTableView>
#include <QModelIndex>
#include <QMap>
#include <QString>
#include <QLabel>

class TableModel: public QTableView
{
    Q_OBJECT
private:    
    QStringList m_headerlist;
    QStandardItem *m_item;
    QStandardItemModel *m_model;
    int m_historyRowCount = 1;

    QMap<QString,QString> maxPowerKeyMap{
        {"自由泳-蹬边滑行","自配合"},{"自由泳-自腿","自配合"},{"自由泳-自手","自配合"},{"自由泳-自配合","自配合"},{"自由泳-海豚腿(俯卧)","自配合"},
        {"仰泳-蹬边滑行","仰配合"},{"仰泳-仰腿","仰配合"},{"仰泳-仰手","仰配合"},{"仰泳-仰配合","仰配合"},{"仰泳-海豚腿(仰卧)","仰配合"},
        {"蛙泳-蹬边滑行","蛙配合"},{"蛙泳-蛙腿","蛙配合"},{"蛙泳-蛙手","蛙配合"},{"蛙泳-蛙配合","蛙配合"},
        {"蝶泳-蹬边滑行","蝶配合"},{"蝶泳-蝶腿","蝶配合"},{"蝶泳-蝶手","蝶配合"},{"蝶泳-蝶配合","蝶配合"},{"蝶泳-海豚腿(俯卧)","蝶配合"}
    };
    QMap<QString,QString> contributionMap{
        {"自由泳","自腿-自手"},{"仰泳","仰腿-仰手"},{"蛙泳","蛙腿-蛙手"},{"蝶泳","蝶腿-蝶手"}
    };

    QStringList getHeaderData();
    bool _getRowDataMap(int rowIndex,QMap<QString, QString> filterValue);
    bool _isValueEqual(QString value, int rowIndex, int keyIndex);

public:
    static TableModel *getInstance();
    explicit TableModel(QObject *parent = 0);
    explicit TableModel(int rowCount, int columnCount);
    ~TableModel();
    int rowCount();
    int historyRowCount();
    void setTableModel(int row, int column, QString cellvalue);
    void setHeaderModel(int column, QString cellvalue);
    QStandardItemModel* getModel();
    QList<QList<QStandardItem*>> getFilterData(QMap<QString,QString> filterValue);

    void setComputedModel();

    void addRowData(QList<QStandardItem*> aItemList);
    void delRowData();
};

class TableModelManager
{
private:
    QVector<TableModel*> m_tableModels;
public:
    static TableModelManager *getInstance();
    explicit TableModelManager(QObject* parent = 0);
    void insertModel(TableModel* tablemodel);
    void createModel();
    void delModel(int index);
    QVector<TableModel*> getALLModels();
    TableModel* getCurTableModel(int Index);
    int getTableModelCount();
};

#endif // TABLEMODEL_H
