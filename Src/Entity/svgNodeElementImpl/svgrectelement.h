#ifndef SVGRECTELEMENT_H
#define SVGRECTELEMENT_H

#include "../svgnodeelement.h"

class ENTITYSHARED_EXPORT SvgRectElement : public SvgNodeElement
{
    Q_OBJECT
public:
    SvgRectElement(SvgNode *parent = 0);

    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget=0);

    virtual void onResize(QRectF r);

	virtual QList<QPointF> tiePoints();

	virtual SvgType svgType() const {
		return SVG_RECT;
	}
protected:
	virtual void cloneImpl(SvgNode *node);
	virtual SvgNode* createThis(){ return new SvgRectElement; }
	virtual void fromXmlImpl(const QDomElement &xml) ;
	virtual QDomElement toXmlImpl(QDomElement &parent) const;
	virtual void updateFrame();
private:
	qreal m_x;
	qreal m_y;
	qreal m_width;
	qreal m_height;
};

#endif // SVGRECTELEMENT_H
