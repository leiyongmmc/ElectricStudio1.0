#ifndef COLORTRANSFORMER_H
#define COLORTRANSFORMER_H
#include "util_global.h"
#include <qcolor.h>
class UTILSHARED_EXPORT ColorTransformer
{
public:
    static QColor colorFromStr(QString str);

	static QString colorToStr(const QColor &color);
private:
    ColorTransformer();
};

#endif // COLORTRANSFORMER_H

