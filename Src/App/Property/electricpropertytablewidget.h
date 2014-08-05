#ifndef ELECTRICPROPERTYTABLEWIDGET_H
#define ELECTRICPROPERTYTABLEWIDGET_H

#include <QTableWidget>
#include <QMap>

#include "graphprimitiveprop.h"

class SvgNode;

class ElectricPropertyTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    ElectricPropertyTableWidget(QWidget *parent = 0);
public slots:
    void slotAdd();
    void slotRemove();
    void slotClear();
    void slotSubmit();
    void initFromSvg(SvgNode *node);
private:
	void addProp(GraphPrimitiveProp::PropType type, const QString& name, const QString &value);
    void addDefaultProp();
private:
    int mRowCnt;
    SvgNode *mNode;
};

#endif // ELECTRICPROPERTYTABLEWIDGET_H
