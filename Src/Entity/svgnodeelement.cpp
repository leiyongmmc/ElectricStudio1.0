#include "svgnodeelement.h"
#include "colortransformer.h"
#include "util.h"
SvgNodeElement::SvgNodeElement(SvgNode *parent)
        :SvgNode(parent)
{
}


void SvgNodeElement::paint(QPainter *painter,
                   const QStyleOptionGraphicsItem *option,
                   QWidget *widget){
//    Q_UNUSED(option);
//    Q_UNUSED(widget);
	
    SvgNode::paint(painter,option,widget);
	QPen pen;
	pen.setWidth(m_strokeWidth);
	pen.setColor(m_stroke);
	painter->setPen(pen);

	QPointF center;
	QList<QPointF> list = this->alignPoints(center);
	QPointF offset = fixedOriginPoint() - m_frame.topLeft() - QPointF(m_strokeWidth / 2.f, m_strokeWidth / 2.f);
	
	for each ( QPointF p in list)
	{
		p = Util::rotateWithCenter(p, center, -this->m_rotationAngle);
		p = this->transform().inverted().map(p);
		painter->drawEllipse(p, 2, 2);
	}
	center = this->transform().inverted().map(center);
	painter->drawEllipse(center, 2, 2);
    //painter->setBrush(m_fill);
//    painter->rotate(m_rotationAngle);
}

