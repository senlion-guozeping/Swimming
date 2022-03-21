#ifndef NEWDATA_H
#define NEWDATA_H

#include <QStandardItem>
#include <QDialog>
#include <QList>
#include <QDateTime>

namespace Ui {
class NewData;
}

class NewData : public QDialog
{
    Q_OBJECT

private:
    QString dataFormat();
    QString getAge(QString birthdayDate);
    QString getGender(bool isManChecked, bool isWomanChecked);
    QString getCurDate(QDate curDate);

    void _setStroke() const;
    void _setSportLevel() const;
    void _setEnv() const;
    void _setTestDintance() const;
    void _setTeam() const;
    void _setTrainStage() const;

public:
    static NewData *getInstance();
    explicit NewData(QWidget *parent = nullptr);
    ~NewData();
    const QList<QStandardItem*> getRowData(int historyRowCount);

private slots:
    void on_restStorkeType(const QString &text);

private:
    Ui::NewData *ui;
};

#endif // NEWDATA_H
