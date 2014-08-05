#ifndef SVGLINEELEMENT_H
#define SVGLINEELEMENT_H

#include "../svgnodeelement.h"

class ENTITYSHARED_EXPORT SvgLineElement : public SvgNodeElement
{
    Q_OBJECT
public:
    SvgLineElement(SvgNode *parent = 0);

    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget=0);
    virtual void onResize(QRectF rect);
	virtual SvgType svgType() const {
		return SVG_LINE;
	}
protected:
	virtual QList<QPointF> alignPoints(QPointF &center);
	virtual void cloneImpl(SvgNode *node);
	virtual SvgNode* createThis(){ return new SvgLineElement; }
	virtual void fromXmlImpl(const QDomElement &xml);
	virtual QDomElement toXmlImpl(QDomElement &parent) const;
	virtual void updateFrame();
	virtual void updateShape();
private:
    QPointF m_p1;
    QPointF m_p2;
};



#endif // SVGLINEELEMENT_H
