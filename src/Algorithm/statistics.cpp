#include "statistics.h"
#include <algorithm>
#include <QDebug>
#include <vector>
static Statistics* INSTANCE=nullptr;
Statistics::Statistics() {}

Statistics *Statistics::getInstance()
{
    if (!INSTANCE) {
        INSTANCE = new Statistics();
    }
    return INSTANCE;
}

QString Statistics::getMaxPower(QVector<double> vec)
{// 最大力
    auto max = *std::max_element(vec.begin(), vec.end());
    return QString::number(max);
}

QString Statistics::getRelativePower(QString maxPower, QString weight)
{// 相对立
    QString relPower;
    if (weight == "0.00") {
        relPower = "";
    } else {
        float value = maxPower.toFloat() / weight.toFloat();
        relPower = QString::number(value, 'f', 5);
    }
    return relPower;
}
QString Statistics::getPercentage(QString maxPower, QString typeTOPower)
{// 百分比
    float value = maxPower.toFloat() / typeTOPower.toFloat();
    QString percentage = QString::number(value, 'f', 5);
    return percentage;
}

QString Statistics::getContribute(QString maxPower, double hl)
{
    double value = maxPower.toDouble();
    QString contribute = QString::number(value / hl);
    return contribute;
}

QString Statistics::getMaxValue(QVector<double> vec)
{
    auto max = *std::max_element(vec.begin(), vec.end());
    return QString::number(max);
}

QString Statistics::getMinValue(QVector<double> vec)
{
    auto min = *std::min_element(vec.begin(), vec.end());
    return QString::number(min);
}
QString Statistics::getAverageValue(QVector<double> vec)
{
    double sum = std::accumulate(vec.begin(), vec.end(), 0.0);
    double mean = sum / vec.length();
    return QString::number(mean);

}
QString Statistics::getStandardDev(QVector<double> vec)
{
    double average = getAverageValue(vec).toDouble();
    double sum = 0;
    for (int i=0; i<vec.length(); i++){
        sum = sum + pow(vec[i] - average, 2);
    }
    double variance = sum / vec.length();
    double standardDev = sqrt(variance);
    return QString::number(standardDev);
}
