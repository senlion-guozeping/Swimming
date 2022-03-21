#ifndef FILTERVALUE_H
#define FILTERVALUE_H

#include <QDialog>
#include <QMap>
#include <QStringList>

namespace Ui {
class FilterValue;
}

class FilterValue : public QDialog
{
    Q_OBJECT

private:

    QString paramValidation(QString param);
    QString getGender(bool isAllSelect, bool isManSelect, bool isWomanSelect);
    QString getAgeRange(int startAgeRange, int endAgeRange );
    QString getTestDate(QDate startTestDate, QDate endTestDate);

    void _setStroke() const;
    void _setSportLevel() const;
    void _setEnv() const;
    void _setTestDintance() const;
    void _setTeam() const;
//    void _setTrainStage() const;

public:
    static FilterValue *getInstance();
    explicit FilterValue(QWidget *parent = nullptr);
    ~FilterValue();
    QMap<QString,QString> getFilterValue();

private slots:
    void restStorkeType(const QString &text);

private:
    Ui::FilterValue *ui;
};

#endif // FILTERVALUE_H
