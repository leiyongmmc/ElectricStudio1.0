#ifndef SVGFILESERVICE_H
#define SVGFILESERVICE_H
#include "io_global.h"
#include "isvgservice.h"
class IOSHARED_EXPORT FileSvgService : public ISvgService
{
public:
    FileSvgService();
	virtual QList<QSharedPointer<SvgNode>> List()const;

	virtual SvgNode *Get(QString id, QObject *parent = NULL) const;

	virtual void SaveOrUpdate(const SvgNode *obj, QString path = "")const;

	virtual SvgNode* create(SvgType type = SvgType::SVG_G, SvgNode*parent = NULL)const;
};

#endif // SVGFILESERVICE_H
