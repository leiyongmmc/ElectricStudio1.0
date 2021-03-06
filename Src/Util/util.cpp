#include "util.h"

Util::Util()
{
}

QMenu* Util::createMenu(QList<QString> actionNames)
{
    QMenu *menu = new QMenu();

    foreach (QString name, actionNames) {
        menu->addAction(name);
    }

    return menu;
}

void Util::getFontStyle(QStringList &fontStyle)
{
    fontStyle.clear();
    fontStyle.append("Normal");
    fontStyle.append("Italic");
    fontStyle.append("Oblique");
}

void Util::getFontSize(QStringList &fontSize)
{
    fontSize.clear();
    fontSize <<"6"<<"7"<<"8"<<"9"<<"10"<<"11"<<"12"<<"13"<<"14"
               <<"16"<<"18"<<"20"<<"28"<<"36"<<"48"<<"72";
}

void Util::getZoomPercent(QStringList &zoomPercent)
{
    zoomPercent.clear();
    zoomPercent <<"10%"<<"25%"<<"33%"<<"50%"<<"65%"<<"80%"<<"100%"
                <<"125%"<<"150%"<<"200%"<<"300%"<<"400%"<<"600%"<<"800%";
}

QIcon Util::createColorToolButtonIcon(const QString &imageFile, const QColor &color)
{
    QPixmap pixmap(24, 24);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    QPixmap image(imageFile);

    QRect target(0, 0, 24, 20);
    QRect source(0, 0, 24, 20);
    painter.fillRect(QRect(0, 20, 24, 10), color);
    painter.drawPixmap(target, image, source);
    return QIcon(pixmap);
}

QMap<int, QIcon> Util::createLineWidthIcons()
{
    QMap<int,QIcon> map;
    map.insert(1,fillIcon(Qt::black,QSize(200,1)));
    map.insert(2,fillIcon(Qt::black,QSize(200,2)));
    map.insert(4,fillIcon(Qt::black,QSize(200,4)));
    map.insert(8,fillIcon(Qt::black,QSize(200,8)));
    map.insert(10,fillIcon(Qt::black,QSize(200,10)));

    return map;
}

QMap<int, QPixmap> Util::createLineWidthPixmaps()
{
    QMap<int,QPixmap> map;
    map.insert(1,fillPixmap(Qt::black,QSize(200,1)));
    map.insert(2,fillPixmap(Qt::black,QSize(200,2)));
    map.insert(4,fillPixmap(Qt::black,QSize(200,4)));
    map.insert(8,fillPixmap(Qt::black,QSize(200,8)));
    map.insert(10,fillPixmap(Qt::black,QSize(200,10)));

    return map;
}

QIcon Util::createColorIcon(QColor color,QSize size)
{
    QPixmap pixmap(size);
    QPainter painter(&pixmap);
    painter.setPen(Qt::NoPen);
    painter.fillRect(QRect(0, 0, size.width(), size.height()), color);

    return QIcon(pixmap);
}

QIcon Util::fillIcon(const QColor &color,const QSize &size)
{
    QPixmap pixmap(size.width(),24);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(Qt::NoPen);
    painter.fillRect(QRect(0,0,size.width(),24),Qt::white);
    painter.fillRect(QRect(0, 12-size.height()/2, size.width(), size.height()), color);

    return QIcon(pixmap);
}

QPixmap Util::fillPixmap(const QColor &color, const QSize &size)
{
    QPixmap pixmap(size.width(),24);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(Qt::NoPen);
    painter.fillRect(QRect(0,0,size.width(),24),Qt::white);
    painter.fillRect(QRect(0, 12-size.height()/2, size.width(), size.height()), color);

    return pixmap;
}


qreal Util::PointLegth(QPointF pa, QPointF pb)
{
	return sqrt(pow((pa.x() - pb.x()), 2) + pow((pa.y() - pb.y()), 2));
}

qreal Util::ComputeAngle(QPointF nowpoint, QPointF centPoint)
{
	double length = PointLegth(nowpoint, centPoint);

	double hudu = asin(abs(nowpoint.y() - centPoint.y()) / length);
	double ag = hudu * 180 / M_PI;

	if ((centPoint.x() - nowpoint.x()) <= 0 && (centPoint.y() - nowpoint.y()) >= 0)
		ag = 90 - ag;

	else if ((centPoint.x() - nowpoint.x()) <= 0 && (centPoint.y() - nowpoint.y()) <= 0)
		ag = ag + 90;

	else if ((centPoint.x() - nowpoint.x()) >= 0 && (centPoint.y() - nowpoint.y()) <= 0)
		ag = 270 - ag;

	else if ((centPoint.x() - nowpoint.x()) >= 0 && (centPoint.y() - nowpoint.y()) >= 0)
		ag = ag + 270;

	return ag;
}
qreal Util::GetPointDistLine(QPointF a, QPointF b, QPointF c)
{
    if(b.x()!=a.x())
        {
            double k=(b.y()-a.y())/(b.x()-a.x());
            return fabs((c.y()-a.y())-k*(c.x()-a.x()))/sqrt(1+k*k);
        }
        else
            return fabs(c.x()-a.x());
}


QPointF Util::rotateWithCenter(const QPointF &p, const QPointF &center, qreal angle){

	qreal radix = angle / 180. * 3.1415926;
	qreal x = cos(radix)*(p.x() - center.x()) - sin(radix)*(center.y() - p.y());
	qreal y = cos(radix)*(center.y() - p.y()) + sin(radix)*(p.x() - center.x());
	y = -y;
	x += center.x();
	y += center.y();
	return QPointF(x, y);
}