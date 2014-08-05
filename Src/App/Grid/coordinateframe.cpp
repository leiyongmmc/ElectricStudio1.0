#include "coordinateframe.h"
#include "ui_coordinateframe.h"

CoordinateFrame::CoordinateFrame(Qt::Orientation ori,QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CoordinateFrame)
  , mOri(ori)
{
    ui->setupUi(this);
}

CoordinateFrame::~CoordinateFrame()
{
    delete ui;
}
