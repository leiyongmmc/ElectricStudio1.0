#ifndef SVGPOLYLINEELEMENT_H
#define SVGPOLYLINEELEMENT_H

#include "../svgnodeelement.h"
#include "../pointitemcontainerdelegate.h"
#include "../ILink.h"

class PointItemContainer;

class ENTITYSHARED_EXPORT SvgPolylineElement : public SvgNodeElement, public PointItemContainerDelegate, public ILink
{
    Q_OBJECT
public:
    SvgPolylineElement(SvgNode *parent = 0);

    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget=0);

    virtual void onResize(QRectF rect);
    virtual void onMoving();
	const QList<QPointF> &points() const{
		return m_points;
	}

	virtual SvgType svgType() const {
		return SVG_POLYLINE;
	}

	virtual void createRelations(SvgNode *top);

    void appendPoint(const QPointF& p);

	

	void removeAt(int idx){
		m_points.removeAt(idx);
		updateFrame();
		updateShape();
	}

	void setPoint(QPointF p, int idx){
		m_points.replace(idx, p);
		updateFrame();
		updateShape();
	}

	virtual void replaceWithScenePoint(bool isStart, QPointF newPoint);

	virtual QUuid getId() const{
		return m_id;
	}


	virtual QList<QPointF> actualScenePoints() const{
		QList<QPointF> list;
        for each (const QPointF& p in m_points)
		{
            list.append(this->mapToScene(p));
		}
		return list;
	}

    virtual void onPointPosChanged(int idx, QPointF newPoint);

	virtual bool tiePointCheckDelegate(QPointF curr, QPointF *res) ;

    void setEnableFlag(bool enable);

    void setMouseMovePos(QPointF pos);

    virtual bool twoEndpointsLinked();

protected:
	virtual QList<QPointF> alignPoints(QPointF &center);
	virtual void cloneImpl(SvgNode *node);
	virtual SvgNode* createThis(){ return new SvgPolylineElement; }
	virtual void fromXmlImpl(const QDomElement &xml) ;
	virtual QDomElement toXmlImpl(QDomElement &parent) const;
	virtual void updateFrame();
	virtual void updateShape();
private:
	QList<QPointF> m_points;

	QVector<QPointF> m_shapePolygonPoints;

	PointItemContainer *m_pointItemContainer;

	QRegion m_region;
};

#endif // SVGPOLYLINEELEMENT_H
