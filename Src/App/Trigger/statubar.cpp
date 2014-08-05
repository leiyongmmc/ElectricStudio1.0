#include "statubar.h"

StatuBar::StatuBar(QWidget* parent) :
    QStatusBar(parent)
{
    this->init();
}

void StatuBar::slotUpdateMousePos(QPointF pos)
{
    this->showMessage(tr("Mouse Position X=%1 Y=%2").arg(pos.x()).arg(pos.y()));
}

void StatuBar::init()
{
}
