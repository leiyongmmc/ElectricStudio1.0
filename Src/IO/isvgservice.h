#ifndef ISVGSERVICE_H
#define ISVGSERVICE_H
#include "io_global.h"
#include "IService.h"
#include "svgnode.h"


class IOSHARED_EXPORT ISvgService  : public IService<SvgNode>
{
public:
	virtual SvgNode* create(SvgType type = SvgType::SVG_G, SvgNode*parent = NULL)const = 0;
};

#endif // ISVGSERVICE_H
