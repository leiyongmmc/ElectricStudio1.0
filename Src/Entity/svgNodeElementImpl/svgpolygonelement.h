#ifndef SVGPOLYGONELEMENT_H
#define SVGPOLYGONELEMENT_H

#include "../svgnodeelement.h"

class ENTITYSHARED_EXPORT SvgPolygonElement : public SvgNodeElement
{
    Q_OBJECT
public:
    SvgPolygonElement(SvgNode *parent = 0);

    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget=0);
    virtual void onResize(QRectF rect);
	virtual QList<QPointF> tiePoints();
	virtual SvgType svgType() const {
		return SVG_POLYGON;
	}
protected:
	virtual QList<QPointF> alignPoints(QPointF &center);
	virtual void cloneImpl(SvgNode *node);
	virtual SvgNode* createThis(){ return new SvgPolygonElement; }
	virtual void fromXmlImpl(const QDomElement &xml) ;
	virtual QDomElement toXmlImpl(QDomElement &parent) const;
	virtual void updateFrame();
	virtual void updateShape();
private:
	QList<QPointF> m_points;

};

#endif // SVGPOLYGONELEMENT_H
