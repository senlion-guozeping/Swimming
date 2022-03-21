#include "filtervalue.h"
#include "ui_filtervalue.h"

#include "src/Common/message.h"
#include "src/Settings/TableSetting.h"
#include <QDebug>

static FilterValue* INSTANCE=nullptr;

FilterValue::FilterValue(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilterValue)
{
    ui->setupUi(this);
    ui->allSelect->setChecked(true);
    this->setWindowTitle("筛选过滤值");


    this->_setStroke();
    this->_setEnv();
    this->_setSportLevel();
    this->_setTeam();
    this->_setTestDintance();
//    this->_setTrainStage();

    connect(ui->stroke,SIGNAL(currentTextChanged(const QString)),this,SLOT(restStorkeType(const QString)));
}

FilterValue::~FilterValue()
{
    delete ui;
}

FilterValue *FilterValue::getInstance()
{
    if (!INSTANCE) {
        INSTANCE = new FilterValue();
    }
    return INSTANCE;
}

QMap<QString,QString> FilterValue::getFilterValue()
{
    QMap<QString,QString> data;
    bool isAllSelect = ui->allSelect->isChecked();
    bool isManSelect = ui->manSelect->isChecked();
    bool isWomanSelect = ui->womanSelect->isChecked();
    QString gender = getGender(isAllSelect,isManSelect,isWomanSelect);
    int startAgeRange = ui->startAgeRange->value();
    int endAgeRange = ui->endAgeRange->value();
    QString ageRange = getAgeRange(startAgeRange,endAgeRange);  //TODO
    QDate startTestDate = ui->startTestDate->date();
    QDate endTestDate = ui->endTestDate->date();
    QString testDate = getTestDate(startTestDate,endTestDate);  // TODO
    QString testEnv = paramValidation(ui->testEnv->currentText());
    QString sportLevel = paramValidation( ui->sportLevel->currentText());
    QString stroke = paramValidation(ui->stroke->currentText());
    QString type = paramValidation(ui->type->currentText());
    QString testDistance = paramValidation(ui->testDistance->currentText());
    QString team = paramValidation(ui->team->currentText());

    data.insert("gender",gender);
    data.insert("ageRange",ageRange);
    data.insert("testDate", testDate);
    data.insert("testEnv",testEnv);
    data.insert("sportLevel",sportLevel);
    data.insert("stroke",stroke);
    data.insert("strokeItem", type);
    data.insert("testDistance",testDistance);
    data.insert("team",team);

    return data;
}

void FilterValue::_setStroke() const
{
    auto tableSetting = TableSetting::getInstance();
    QStringList stroke = tableSetting->getStroke();
    ui->stroke->addItems(stroke);
}

void FilterValue::_setSportLevel() const
{
    auto tableSetting = TableSetting::getInstance();
    QStringList sportLevel = tableSetting->getSportLevel();
    ui->sportLevel->addItems(sportLevel);
}
void FilterValue::_setEnv() const
{
    auto tableSetting = TableSetting::getInstance();
    QStringList env = tableSetting->getEnv();
    ui->testEnv->addItems(env);
}
void FilterValue::_setTestDintance() const
{
    auto tableSetting = TableSetting::getInstance();
    QStringList testDistance = tableSetting->getTestDintance();
    ui->testDistance->addItems(testDistance);
}
void FilterValue::_setTeam() const
{
    auto tableSetting = TableSetting::getInstance();
    QStringList team = tableSetting->getTeam();
    ui->team->addItems(team);
}


QString FilterValue::getGender(bool isAllSelect, bool isManSelect, bool isWomanSelect)
{
    QString gender;
    if (isAllSelect){
        gender = "all";
    } else if (isManSelect) {
        gender = "男";
    }else if (isWomanSelect) {
        gender = "女";
    }
    return gender;
}

QString FilterValue::getAgeRange(int startAgeRange, int endAgeRange)
{
    QString startAge = QString::number(startAgeRange);
    QString endAge = QString::number(endAgeRange);
    return startAge + "::" + endAge;
}

QString FilterValue::getTestDate(QDate startTestDate, QDate endTestDate)
{
    QString startDate = startTestDate.toString(Qt::ISODateWithMs);
    QString endDate = endTestDate.toString(Qt::ISODateWithMs);
    return startDate + "::" + endDate;
}

void FilterValue::restStorkeType(const QString &text)
{
    auto tableSetting = TableSetting::getInstance();
    if (text != "请选择") {
        ui->type->clear();
        QStringList strokeItem = tableSetting->getStrokeItem()[text];
        qDebug() << text<< strokeItem;
        ui->type->addItems(strokeItem);
    }
}

QString FilterValue::paramValidation(QString param)
{
    if (param == "请选择"){
        param = "all";
    }
    return param;
}
