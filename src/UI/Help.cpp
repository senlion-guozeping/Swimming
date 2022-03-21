#include "Help.h"
#include "ui_Help.h"

static Help* INSTANCE=nullptr;
Help::Help(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Help)
{
    ui->setupUi(this);
}

Help::~Help()
{
    delete ui;
}

Help* Help::getInstance()
{
    if (!INSTANCE) {
        INSTANCE = new Help();
    }
    return INSTANCE;
}
