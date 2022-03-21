#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMap>
#include <QList>
#include <QString>
#include <QMainWindow>
#include <QCloseEvent>

#include "src/UI/filtermodel.h"
#include "src/Excel/player.h"
#include "src/UI/filtervalue.h"
#include "src/UI/tablemodel.h"
#include "src/UI/newdata.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setTabPage(TableModel* tablemodel);


private:
    TableModelManager* m_tableModelManager;

    int getTabCurIndex();
    int getTabCount();
    QWidget* getTabCurWdiget();
    QTabWidget* getTabWidget();
    void setToolBarStatus();


private slots:
    void on_actOpenFile_triggered();

    void on_actNewDoc_triggered();

    void on_actSaveas_triggered();

    void on_actRowDel_triggered();

    void on_actDataFilter_triggered();

    void on_actAppendData_triggered();

    void on_actComputed_triggered();

    void on_actdelTabPage(int index);

    void on_actExport_triggered();

    void on_actAbout_triggered();

protected:
    void closeEvent(QCloseEvent* event);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
