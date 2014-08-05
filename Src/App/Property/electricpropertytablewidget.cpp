#include "electricpropertytablewidget.h"

#include <QTableWidgetItem>
#include <QComboBox>
#include <QHeaderView>

#include "svgnode.h"
#include "../appglobal.h"
#include "idevicetypeservice.h"

ElectricPropertyTableWidget::ElectricPropertyTableWidget(QWidget *parent) :
    QTableWidget(parent)
{
    mNode = NULL;
    mRowCnt = 0;
    this->setRowCount(mRowCnt);
    this->setColumnCount(3);

    QStringList headerLabels;
    headerLabels << tr("Type")<<tr("Property") <<tr("Value");

    this->setHorizontalHeaderLabels(headerLabels);
    this->horizontalHeader()->setStretchLastSection(true);
    this->verticalHeader()->setVisible(false);
	this->hideColumn(0);
}

void ElectricPropertyTableWidget::initFromSvg(SvgNode *svg)
{
    if(!svg)
        return;

    mNode = svg;

    // clear all
    for(int i = 0; i < mRowCnt; i++)
        this->removeRow(i);
	mRowCnt = 0;

    bool bDefaultTypeExisted = false;
    GraphPrimitiveProp deviceProp;

    const QLinkedList<GraphPrimitiveProp>& props = svg->props();
    QLinkedList<GraphPrimitiveProp>::const_iterator begin = props.cbegin();
    QLinkedList<GraphPrimitiveProp>::const_iterator end = props.cend();
    for (QLinkedList<GraphPrimitiveProp>::const_iterator itr = begin; itr != end; itr++)
    {
        if((*itr).type() == GraphPrimitiveProp::DEVICETYPE)
        {
            deviceProp.setName((*itr).name());
            deviceProp.setType((*itr).type());
            deviceProp.setValue((*itr).value());
            bDefaultTypeExisted = true;
            break;
        }
    }

    if(bDefaultTypeExisted == false)
    {
        this->addDefaultProp();
    }
    else
    {
        // add d
		this->addProp(deviceProp.type(), deviceProp.name(), deviceProp.value().toString());

    }
    // add normal items
    for(QLinkedList<GraphPrimitiveProp>::const_iterator itr = begin; itr != end; itr++)
    {
        if((*itr).type() == GraphPrimitiveProp::DEVICETYPE)
        {
            continue;
        }
        this->addProp((*itr).type(),(*itr).name(),(*itr).value().toString());
    }
}

void ElectricPropertyTableWidget::slotAdd()
{
	this->addProp(GraphPrimitiveProp::STRING, tr("PropName"), tr("PropValue"));
}

void ElectricPropertyTableWidget::addProp(GraphPrimitiveProp::PropType type
                                          , const QString &name
                                          , const QString &value)
{
    int row = mRowCnt++;
    this->setRowCount(mRowCnt);
    QTableWidgetItem *typeItem = new QTableWidgetItem(tr("%1").arg((int)type));
    this->setItem(row,0,typeItem);
    QTableWidgetItem *nameItem = new QTableWidgetItem(tr("%1").arg(name));
    this->setItem(row, 1, nameItem);
    QTableWidgetItem *valueItem = new QTableWidgetItem(tr("%1").arg(value));
    this->setItem(row, 2, valueItem);
}

void ElectricPropertyTableWidget::addDefaultProp()
{
    int row = mRowCnt++;
    this->setRowCount(mRowCnt);

    QTableWidgetItem *typeItem = new QTableWidgetItem(tr("%1").arg((int)GraphPrimitiveProp::DEVICETYPE));
    this->setItem(row, 0, typeItem);

    QTableWidgetItem *nameItem = new QTableWidgetItem(tr("Device Type"));
    this->setItem(row, 1, nameItem);

    QComboBox *deviceType = new QComboBox(this);
    this->setCellWidget(row,2,deviceType);

    const IDeviceTypeService &ser = AppGlobal::instance().serviceFactory().createDeviceTypeService();
    QList<QSharedPointer<DeviceType>> list = ser.List();
    for(int i = 0; i < list.count(); i++)
    {
        deviceType->insertItem(i,list.at(i).value->name());
    }
}

void ElectricPropertyTableWidget::slotRemove()
{
    mRowCnt--;
    if(mRowCnt < 1)
        mRowCnt = 1;

    this->setRowCount(mRowCnt);
    this->removeRow(this->currentRow());
}

void ElectricPropertyTableWidget::slotClear()
{
    for(int i = 0; i < mRowCnt; i++)
    {
		QTableWidgetItem* item = this->item(i, 0);
		if (item)
		{
			this->removeRow(i);
		}
        
    }

    mRowCnt = 0;
}

void ElectricPropertyTableWidget::slotSubmit()
{
    if(!mNode)
        return;

    // clear old
    mNode->clearProps();
    for(int i = 0; i < mRowCnt; i++)
    {
		GraphPrimitiveProp::PropType type = (GraphPrimitiveProp::PropType)this->item(i, 0)->text().toInt();
        QString name = this->item(i,1)->text();
        QVariant value;
		if (type == GraphPrimitiveProp::DEVICETYPE)
        {
            value = dynamic_cast<QComboBox*>(this->cellWidget(i,2))->currentText();
        }
        else
            value = this->item(i,2)->text();

        mNode->addProp(GraphPrimitiveProp(name,type,value));
    }
}
