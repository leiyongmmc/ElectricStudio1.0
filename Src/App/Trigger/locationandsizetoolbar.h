#ifndef LOCATIONANDSIZETOOLBAR_H
#define LOCATIONANDSIZETOOLBAR_H

#include <QRectF>

#include "toolbar.h"


class QLabel;
class QLineEdit;

class LocationAndSizeToolBar : public ToolBar
{
    Q_OBJECT
public:
    LocationAndSizeToolBar(const QString &name,QWidget *parent = 0);
    void setLocationAndSize(QRectF rect);
private:
    virtual void createToolbar();
    void createConnect();
private:
    QLabel *mXLabel;
    QLineEdit *mXLineEdit;
    QLabel *mYLabel;
    QLineEdit *mYLineEdit;
    QLabel *mWidthLabel;
    QLineEdit *mWidthLineEdit;
    QLabel *mHeightLabel;
    QLineEdit *mHeightLineEdit;
};

#endif // LOCATIONANDSIZETOOLBAR_H
