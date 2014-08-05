#ifndef SHAPEFORMATTINGTOOLBAR_H
#define SHAPEFORMATTINGTOOLBAR_H

#include <QLabel>

#include "toolbar.h"

#include "shapeformattingsetting.h"

class QMenu;

class QToolButton;

class ShapeFormattingToolBar : public ToolBar
{
    Q_OBJECT
public:
    ShapeFormattingToolBar(const QString &name,QWidget *parent = 0);
    void initFromShapeFormattingSetting(ShapeFormattingSetting setting = ShapeFormattingSetting());
    ShapeFormattingSetting& getShapeFormattingSetting();
	public slots:
	void slotSetShapeFormatting(ShapeFormattingSetting);
private:
    virtual void createToolbar();
    void createConnect();
private slots:
    void slotSetLineColor();
    void slotSetFillColor();
    void slotSetLineWidth();
signals:
    void sigShapeFormattingChanged(ShapeFormattingSetting setting);
private:
    QMenu           *mLineWidthMenu;
    QList<QToolButton*>  *mLineWidthBtns;
    QToolButton *mLineColor;
    QToolButton *mLineWidth;
    QToolButton *mLinePattern;
    QToolButton *mFillColor;

    ShapeFormattingSetting mShapeSetting;
};

#endif // SHAPEFORMATTINGTOOLBAR_H
