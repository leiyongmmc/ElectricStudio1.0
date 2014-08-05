#ifndef SVGPATHELEMENT_H
#define SVGPATHELEMENT_H

#include "../svgnodeelement.h"

typedef enum{
    M = 77,  //start
	m = 109,
    L = 76,  //line
	l = 108,
    H = 72,  //horizontal line
	h = 104,
    V = 86,  //vertical line
	v = 118,
    A = 65,  //elliptical
	a = 97,
    Z = 90,  //closepath
	z = 122,
    C = 67,  //curveto
	c = 99,
    S = 83,  //smooth curveto
	s = 115,
    Q = 81,  //quadratic Belzier curve
	q = 113,
    T = 84,   //smooth quadratic Belzier curveto
	t = 116
}pathDataType;

typedef struct{
	pathDataType type;
	QList<QPointF> points;
	QPointF start;
	QPointF end;
}SvgPathElementItemData;


typedef struct {
	QList<SvgPathElementItemData> data;
    bool isClosed;
}SvgPathElementItem;

class ENTITYSHARED_EXPORT SvgPathElement : public SvgNodeElement
{
    Q_OBJECT
public:
    SvgPathElement(SvgNode *parent = 0);

    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget=0);
    virtual void onResize(QRectF rect);
	virtual QList<QPointF> tiePoints();
	virtual SvgType svgType() const {
		return SVG_PATH;
	}
protected:
	virtual QList<QPointF> alignPoints(QPointF &center);
	virtual void cloneImpl(SvgNode *node);
	virtual SvgNode* createThis(){ return new SvgPathElement; }
	virtual void fromXmlImpl(const QDomElement &xml) ;
	virtual QDomElement toXmlImpl(QDomElement &parent) const;
	virtual void updateFrame();
private:
    QList<SvgPathElementItem> m_pathList;

};

#endif // SVGPATHELEMENT_H
