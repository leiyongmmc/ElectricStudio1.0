#include "griddialog.h"
#include "ui_griddialog.h"

#include "gridsetting.h"

GridDialog::GridDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GridDialog)
{
    ui->setupUi(this);
    this->init();
}

GridDialog::~GridDialog()
{
    delete ui;
}

void GridDialog::init()
{
    this->initGridPage();
}

void GridDialog::initGridPage()
{
    GridSetting *setting = GridSetting::getGridSetting();
    if(setting)
    {

    }
}

void GridDialog::setCurrentTab(int index)
{
    ui->tabWidget->setCurrentIndex(index);
}
