#ifndef SVGCIRCLEELEMENT_H
#define SVGCIRCLEELEMENT_H

#include "../svgnodeelement.h"

class ENTITYSHARED_EXPORT SvgCircleElement : public SvgNodeElement
{
    Q_OBJECT
public:
    SvgCircleElement(SvgNode *parent = 0);
    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget=0);
    virtual void onResize(QRectF rect);
	virtual QList<QPointF> tiePoints();

	virtual SvgType svgType() const {
		return SVG_CIRCLE;
	}
protected:
	virtual QList<QPointF> alignPoints(QPointF &center);
	virtual void cloneImpl(SvgNode *node);
	virtual SvgNode* createThis(){ return new SvgCircleElement; }
	virtual void fromXmlImpl(const QDomElement &xml) ;
	virtual QDomElement toXmlImpl(QDomElement &parent) const;
	virtual void updateFrame();
	virtual void updateShape();
private:
    
	qreal m_cx;
	qreal m_cy;
	qreal m_r;
};


#endif // SVGCIRCLEELEMENT_H
