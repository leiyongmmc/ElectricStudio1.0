#ifndef UTIL_H
#define UTIL_H

#include "util_global.h"

#include <QObject>
#include <QIcon>
#include <QMap>
#include <QPixmap>
#include <QMenu>
#include <QPainter>
#include <qmath.h>
#include <QPen>

class QMenu;

class UTILSHARED_EXPORT Util
{
public:
    Util();

    /** crate menu from action names */
    static QMenu* createMenu(QList<QString> actionNames);
	/** font styles */
    static void getFontStyle(QStringList &fontStyle);
	/** font sizes */
	static void getFontSize(QStringList &fontSize);
    /** scale*/ 
    static void getZoomPercent(QStringList &zoomPercent);
    // image and color icon
    static QIcon createColorToolButtonIcon(const QString &imageFile,const QColor &color);
    static QMap<int,QIcon> createLineWidthIcons();
    static QMap<int,QPixmap> createLineWidthPixmaps();
    static QIcon createColorIcon(QColor color,QSize size);
    static QIcon fillIcon(const QColor &color, const QSize &size);
    static QPixmap fillPixmap(const QColor &color, const QSize &size);

	static qreal PointLegth(QPointF pa, QPointF pb);

	static qreal ComputeAngle(QPointF nowpoint, QPointF centPoint);

    static qreal GetPointDistLine(QPointF a, QPointF b, QPointF c);

	static QPointF rotateWithCenter(const QPointF &p, const QPointF &center, qreal angle);
};

#endif // UTIL_H
