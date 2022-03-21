#include "message.h"
#include <QPushButton>
static ErrMessage* ErrINSTANCE = nullptr;
static WarnMessage* WarnINSTANCE = nullptr;
static InfoMessage* InfoINSTANCE = nullptr;
static QuestionMessage* QuestionINSTANCE = nullptr;
Message::Message() {
    setWindowFlags(Qt::FramelessWindowHint | Qt::ToolTip);
}


ErrMessage *ErrMessage::getInstance()
{
    if (!ErrINSTANCE) {
        ErrINSTANCE = new ErrMessage();
    }
    return ErrINSTANCE;
}

ErrMessage::ErrMessage() {
    this->setIcon(QMessageBox::Critical);
}

int ErrMessage::sendMessage(const QString &title, const QString &text)
{
    int ret = QMessageBox::critical(this, title, text,
                                    QMessageBox::Ok,
                                    QMessageBox::Ok);
    return ret;
}

WarnMessage *WarnMessage::getInstance()
{
    if (!WarnINSTANCE) {
        WarnINSTANCE = new WarnMessage();
    }
    return WarnINSTANCE;
}

WarnMessage::WarnMessage() {
    this->setIcon(QMessageBox::Information);
}

int WarnMessage::sendMessage(const QString &title, const QString &text)
{
    int ret = QMessageBox::warning(this, title, text,
                                   QMessageBox::Cancel | QMessageBox::No| QMessageBox::Yes,
                                   QMessageBox::No);
    return ret;
}

InfoMessage* InfoMessage::getInstance()
{
    if(!InfoINSTANCE) {
        InfoINSTANCE = new InfoMessage();
    }
    return InfoINSTANCE;
}

InfoMessage::InfoMessage()
{
    this->setIcon(QMessageBox::Information);
}

int InfoMessage::sendMessage(const QString &title, const QString &text)
{
    int ret = QMessageBox::information(this, title, text,
                                       QMessageBox::Ok,
                                       QMessageBox::Ok);
    return ret;
}

QuestionMessage* QuestionMessage::getInstance()
{
    if (!QuestionINSTANCE) {
        QuestionINSTANCE = new QuestionMessage();
    }
    return QuestionINSTANCE;
}

QuestionMessage::QuestionMessage()
{
    this->setIcon(QMessageBox::Question);
}

int QuestionMessage::sendMessage(const QString &title, const QString &text)
{
    int ret = QMessageBox::question(this, title, text,
                                    QMessageBox::Cancel | QMessageBox::Close | QMessageBox::Ok,
                                    QMessageBox::Close);
    return ret;
}

void TipMessage::sendTipInfo(const QString &text,const QPoint& pos)
{
    //设置QToolTip颜色
    QPalette palette = QToolTip::palette();
    palette.setColor(QPalette::Inactive,QPalette::ToolTipBase,Qt::white);   //设置ToolTip背景色
    palette.setColor(QPalette::Inactive,QPalette::ToolTipText,QColor(102, 102, 102, 255));    //设置ToolTip字体色

    QToolTip::setPalette(palette);
    QFont font("Segoe UI", -1, 50);
    font.setPixelSize(12);
    QToolTip::setFont(font);  //设置ToolTip字体

    QWidget* widget = new QPushButton();
    widget->setFixedSize(100,200);
    const QRect rect(100,100,100,200);
    int msecDisplayTime=2500;
    QToolTip::showText(pos,text,widget,rect,msecDisplayTime);
}
