#ifndef SVGELLIPSEELEMENT_H
#define SVGELLIPSEELEMENT_H
#include "../svgnodeelement.h"

class ENTITYSHARED_EXPORT SvgEllipseElement : public SvgNodeElement
{
    Q_OBJECT
public:
    SvgEllipseElement(SvgNode *parent = 0);
    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget=0);
    virtual void onResize(QRectF rect);
	virtual QList<QPointF> tiePoints();
	virtual SvgType svgType() const {
		return SVG_ELLIPSE;
	}
protected:
	virtual QList<QPointF> alignPoints(QPointF &center);
	virtual void cloneImpl(SvgNode *node);
	virtual SvgNode* createThis(){ return new SvgEllipseElement; }
	virtual void fromXmlImpl(const QDomElement &xml);
	virtual QDomElement toXmlImpl(QDomElement &parent) const;
	virtual void updateFrame();
	virtual void updateShape();
private:
	qreal m_cx;
	qreal m_cy;
	qreal m_rx;
	qreal m_ry;
};

#endif // SVGELLIPSEELEMENT_H
