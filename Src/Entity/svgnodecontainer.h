#ifndef SVGNODECONTAINER_H
#define SVGNODECONTAINER_H

#include "svgnode.h"
#include "entity_global.h"
class ENTITYSHARED_EXPORT SvgNodeContainer : public SvgNode
{
    Q_OBJECT
public:
    SvgNodeContainer(SvgNode *parent = 0);

    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget=0);

	virtual void toXml(QDomElement &parent) const;

	virtual void createRelations(SvgNode *top);
	virtual SvgType svgType() const {
		return SVG_G;
	}
protected:
	virtual SvgNode* createThis(){ return new SvgNodeContainer; }
	virtual void fromXmlImpl(const QDomElement &xml) ;
	virtual QDomElement toXmlImpl(QDomElement &parent) const;
	virtual void updateFrame();
};

#endif // SVGNODECONTAINER_H
