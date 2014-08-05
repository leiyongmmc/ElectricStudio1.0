#ifndef SVGNODEELEMENT_H
#define SVGNODEELEMENT_H
#include "svgnode.h"
#include "entity_global.h"
#include <QtGui>
class ENTITYSHARED_EXPORT SvgNodeElement : public SvgNode
{
    Q_OBJECT
public:
    SvgNodeElement(SvgNode *parent = 0);

    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget=0);


protected:

};

#endif // SVGNODEELEMENT_H
