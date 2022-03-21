#include "newdata.h"
#include "ui_newdata.h"
#include <QDebug>

#include "src/Settings/TableSetting.h"
#include "src/Common/message.h"

static NewData* INSTANCE=nullptr;

NewData::NewData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewData)
{
    ui->setupUi(this);

    this->_setStroke();
    this->_setEnv();
    this->_setSportLevel();
    this->_setTeam();
    this->_setTestDintance();
    this->_setTrainStage();

    connect(ui->stroke,SIGNAL(currentTextChanged(const QString)),this,SLOT(on_restStorkeType(const QString)));
}

NewData::~NewData()
{
    delete ui;
}

NewData *NewData::getInstance()
{
    if (!INSTANCE) {
        INSTANCE = new NewData();
    }
    return INSTANCE;
}

const QList<QStandardItem*> NewData::getRowData(int historyRowCount)
{
    QList<QStandardItem*> aItemList;
    bool isManChecked = ui->man->isChecked();
    bool isWomanChecked = ui->woman->isChecked();
    QString gender = getGender(isManChecked,isWomanChecked);
    QString weight = ui->weight->text();
    QString birthdayDate = ui->birthday->text();
    QString age = getAge(birthdayDate);
    QString sportLevel = ui->sportLevel->currentText();
    QString team = ui->team->currentText();
    QString trainPhasse = ui->trainPhasse->currentText();
    QString stroke = ui->stroke->currentText();
    QString type = ui->type->currentText();
    QString testDistance = ui->testDistance->currentText();
    QString maxPower1 = ui->maxPower1->text();
    QString maxPower2 = ui->maxPower2->text();
    QString maxPower3 = ui->maxPower3->text();
    QString testDate = getCurDate(QDate::currentDate());
    QString testEnv = ui->testEnv->currentText();

    QStandardItem* identityID = new QStandardItem(ui->name->text()  + "::" + birthdayDate);
    QStandardItem* testID = new QStandardItem(QString::number(historyRowCount)  + "::" + testDate);
    QStandardItem* name_item = new QStandardItem(ui->name->text());
    QStandardItem* gender_item = new QStandardItem(gender);
    QStandardItem* weight_item = new QStandardItem(weight);
    QStandardItem* age_item = new QStandardItem(age);
    QStandardItem* sportLevel_item = new QStandardItem(sportLevel);
    QStandardItem* team_item = new QStandardItem(team);
    QStandardItem* trainStage_item = new QStandardItem(trainPhasse);
    QStandardItem* stroke_item = new QStandardItem(stroke);
    QStandardItem* strokeItem_item = new QStandardItem(type);
    QStandardItem* testDistance_item = new QStandardItem(testDistance);
    QStandardItem* maxPowerOne_item = new QStandardItem(maxPower1);
    QStandardItem* maxPowerTwo_item = new QStandardItem(maxPower2);
    QStandardItem* maxPowerThree_item = new QStandardItem(maxPower3);
    QStandardItem* testEnv_item = new QStandardItem(testEnv);
    aItemList.push_back(identityID);
    aItemList.push_back(testID);
    aItemList.push_back(name_item);
    aItemList.push_back(gender_item);
    aItemList.push_back(weight_item);
    aItemList.push_back(age_item);
    aItemList.push_back(sportLevel_item);
    aItemList.push_back(team_item);
    aItemList.push_back(trainStage_item);
    aItemList.push_back(stroke_item);
    aItemList.push_back(strokeItem_item);
    aItemList.push_back(testDistance_item);
    aItemList.push_back(maxPowerOne_item);
    aItemList.push_back(maxPowerTwo_item);
    aItemList.push_back(maxPowerThree_item);
    aItemList.push_back(new QStandardItem(" "));
    aItemList.push_back(new QStandardItem(" "));
    aItemList.push_back(new QStandardItem(" "));
    aItemList.push_back(new QStandardItem(" "));
    aItemList.push_back(testEnv_item);
    for (int i=0; i<aItemList.length();i++) {
        QStandardItem* item =  aItemList.at(i);
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    }
    return aItemList;
}

QString NewData::dataFormat()
{

}

QString NewData::getCurDate(QDate curDate)
{
    return curDate.toString("yyyy/MM/dd");
}

QString NewData::getAge(QString birthdayDate)
{
    QDateTime curdate = QDateTime::currentDateTime();//获取系统现在的时间
    int curyear = curdate.toString("yyyy/MM/dd").split('/')[0].toInt();
    int biryear = birthdayDate.split('/')[0].toUInt();
    QString age = QString::number(curyear-biryear);
    return age;
}

void NewData::_setStroke() const
{
    auto tableSetting = TableSetting::getInstance();
    QStringList stroke = tableSetting->getStroke();
    ui->stroke->addItems(stroke);
}

void NewData::_setSportLevel() const
{
    auto tableSetting = TableSetting::getInstance();
    QStringList sportLevel = tableSetting->getSportLevel();
    ui->sportLevel->addItems(sportLevel);
}
void NewData::_setEnv() const
{
    auto tableSetting = TableSetting::getInstance();
    QStringList env = tableSetting->getEnv();
    ui->testEnv->addItems(env);
}
void NewData::_setTestDintance() const
{
    auto tableSetting = TableSetting::getInstance();
    QStringList testDistance = tableSetting->getTestDintance();
    ui->testDistance->addItems(testDistance);
}
void NewData::_setTeam() const
{
    auto tableSetting = TableSetting::getInstance();
    QStringList team = tableSetting->getTeam();
    ui->team->addItems(team);
}
void NewData::_setTrainStage() const
{
    auto tableSetting = TableSetting::getInstance();
    QStringList trainStage = tableSetting->getTrainStage();
    ui->trainPhasse->addItems(trainStage);
}

QString NewData::getGender(bool isManChecked, bool isWomanChecked)
{
    QString gender;
    if (isManChecked) {
        gender = "男";
    }
    if (isWomanChecked) {
        gender = "女";
    }
    return gender;
}

void NewData::on_restStorkeType(const QString &text)
{
    auto tableSetting = TableSetting::getInstance();
    if (text != "请选择") {
        ui->type->clear();
        QStringList strokeItem = tableSetting->getStrokeItem()[text];
        qDebug() << text<< strokeItem;
        ui->type->addItems(strokeItem);
    }
}
