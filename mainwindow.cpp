#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "src/Settings/TableSetting.h"
#include "src/Settings/WindowSetting.h"
#include "src/Common/window.h"
#include "src/Common/message.h"
#include "src/UI/Help.h"

#include <QDebug>

using namespace QXlsx;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Swimming");
    this->setWindowState(Qt::WindowMaximized); //窗口最大化显示
    this->setAutoFillBackground(true);
    this->setAttribute(Qt::WA_QuitOnClose);

    connect(ui->tabWidget,SIGNAL(tabCloseRequested(int)), this, SLOT(on_actdelTabPage(int)));

    m_tableModelManager = TableModelManager::getInstance();
}

MainWindow::~MainWindow()
{
    for (int i=0; i<m_tableModelManager->getTableModelCount(); i++){
        m_tableModelManager->delModel(i);
        ui->tabWidget->removeTab(i);
    }
    delete ui;
}

void MainWindow::on_actExport_triggered()
{
    auto tableSetting = TableSetting::getInstance();
    auto windowSetting = WindowSetting::getInstance();
    QStringList defaultTableHeaderData = tableSetting->getTableHeaderData();
    auto player = Player::getInstance();
    QPoint pos = windowSetting->getTipPos(this);
    player->exportTemplate(defaultTableHeaderData,pos);
}

void MainWindow::on_actOpenFile_triggered()
{
    auto player = Player::getInstance();
    QList<TableModel*> tablemodels = player->openXlsx();
    if (tablemodels.size()) {
        for (int i=0; i<tablemodels.size(); i++){
            this->setTabPage(tablemodels[i]);
        }
    }
    if (tablemodels.size()>1){
        this->setToolBarStatus();
    }
}

void MainWindow:: on_actSaveas_triggered()
{
    if (this->getTabCurIndex() != -1) {
        auto player = Player::getInstance();
        TableModel* tablemodel = m_tableModelManager->getCurTableModel(this->getTabCurIndex());
        player->saveXlsx(tablemodel->getModel());
    }
}

void MainWindow::on_actNewDoc_triggered()
{
    auto tableSetting = TableSetting::getInstance();
    QStringList defaultTableHeaderData = tableSetting->getTableHeaderData();
    qDebug() << defaultTableHeaderData;
    TableModel* tablemodel = new TableModel(0,defaultTableHeaderData.length());
    for (int i = 0; i < defaultTableHeaderData.length(); ++i){
        tablemodel->setHeaderModel(i,defaultTableHeaderData.at(i));
    }
    this->setTabPage(tablemodel);
}

void MainWindow::on_actDataFilter_triggered()
{
    if (this->getTabCurIndex() != -1) {
        auto filterValue = FilterValue::getInstance();
        auto filterModel = FilterModel::getInstance();
        TableModel* tablemodel = m_tableModelManager->getCurTableModel(this->getTabCurIndex());
        int ret = filterValue->exec();
        if (ret==QDialog::Accepted)
        {
            QMap<QString,QString> fileterValue = filterValue->getFilterValue();
            QList<QList<QStandardItem*>> filterData = tablemodel->getFilterData(fileterValue);
            filterModel->setResModel(filterData);
            int ret = filterModel->exec();
            if (ret == QDialog::Accepted){
                //TODO
            } else if (ret == QDialog::Rejected) {}
        } else if (ret == QDialog::Rejected) {
        }
    }
}

void MainWindow::on_actAppendData_triggered()
{
    if (this->getTabCurIndex() != -1) {
        auto newData = NewData::getInstance();
        int tabCount = m_tableModelManager->getTableModelCount();
        int ret = newData->exec();
        if (ret == QDialog::Accepted) {
            if (tabCount !=0) {
                TableModel* tableModel = m_tableModelManager->getCurTableModel(this->getTabCurIndex());
                QList<QStandardItem*> aItemList = newData->getRowData(tableModel->historyRowCount());
                tableModel->addRowData(aItemList);
            }
        } else if (ret == QDialog::Rejected) {
            qDebug() << "取消添加";
        }
    }
}

void MainWindow::on_actRowDel_triggered()
{
    if (this->getTabCurIndex() != -1) {
        TableModel* tablemodel = m_tableModelManager->getCurTableModel(this->getTabCurIndex());
        tablemodel->delRowData();
    }
}

void MainWindow::on_actComputed_triggered()
{
    if (this->getTabCurIndex() != -1) {
        TableModel* tablemodel = m_tableModelManager->getCurTableModel(this->getTabCurIndex());
        tablemodel->setComputedModel();
    }
}

QTabWidget* MainWindow::getTabWidget()
{
    return ui->tabWidget;
}

void MainWindow::setTabPage(TableModel* tablemodel)
{
    ui->tabWidget->addTab(tablemodel, QString::number(getTabCount() + 1));
    m_tableModelManager->insertModel(tablemodel);
}

int MainWindow::getTabCurIndex()
{
    return ui->tabWidget->currentIndex();
}

QWidget* MainWindow::getTabCurWdiget()
{
    return ui->tabWidget->currentWidget();
}

int MainWindow::getTabCount()
{
    return ui->tabWidget->count();
}

void MainWindow::on_actdelTabPage(int index)
{
    QString title = "删除页面";
    QString text = "警告，删除此页面数据将不能恢复，请谨慎操作!!!";
    auto warnMessage = WarnMessage::getInstance();
    int ret = warnMessage->sendMessage(title,text);
    if (ret == QMessageBox::Yes){
        m_tableModelManager->delModel(index);
        ui->tabWidget->removeTab(index);
    } else if (ret == QMessageBox::No){
        qDebug() << "不删除";
    } else if (ret == QMessageBox::Cancel){
        qDebug() << "取消";
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{

    int modelCount = m_tableModelManager->getTableModelCount();
    if (modelCount != 0) {
        QString title = "是否保存表格数据";
        QString text = "警告，是否保存表格数据，请关闭之前操作";
        auto warnMessage = WarnMessage::getInstance();
        int ret = warnMessage->sendMessage(title,text);
        if (ret == QMessageBox::Yes){
        } else if (ret == QMessageBox::No){

        } else if (ret == QMessageBox::Cancel){
        }
    }
}

void MainWindow::setToolBarStatus()
{
    bool isEnabled = false;
    ui->actExport->setEnabled(isEnabled);
    ui->actDataFilter->setEnabled(isEnabled);
    ui->actAppendData->setEnabled(isEnabled);
    ui->actNewDoc->setEnabled(isEnabled);
    ui->actSaveas->setEnabled(isEnabled);
    ui->actComputed->setEnabled(isEnabled);
    ui->actRowDel->setEnabled(isEnabled);
}



void MainWindow::on_actAbout_triggered()
{
    auto help = Help::getInstance();
    help->show();
}

