#ifndef TEXTFORMATTINGTOOLBAR_H
#define TEXTFORMATTINGTOOLBAR_H

#include "toolbar.h"
#include "textformattingsetting.h"

class QFontComboBox;
class QComboBox;
class QToolButton;
class QAction;

class TextFormattingToolBar : public ToolBar
{
    Q_OBJECT
public:
    TextFormattingToolBar(const QString &name,QWidget *parent = 0);
    void initFromTextFormattingSetting(TextFormattingSetting setting = TextFormattingSetting());
    TextFormattingSetting& getTextFormattingSetting();
public slots:
	void slotSetTextFormatting(TextFormattingSetting);
private:
    virtual void createToolbar();
    void createConnect();
private slots:
    void slotSetFontFamily(QString);
    void slotSetFontStyle(QString);
    void slotSetFontSize(QString);
    void slotSetTextColor();
    void slotSetTextHorizontalAlign();
    void slotSetTextBIU(bool);
signals:
    void sigTextFormattingChanged(TextFormattingSetting);
private:
    // font family
    QFontComboBox *mFontFamily;
    // font style
    QComboBox *mFontStyle;
    // font size
    QComboBox *mFontSize;
    // bold
    QToolButton *mBold;
    // italic
    QToolButton *mItalic;
    // underline
    QToolButton *mUnderline;
    // align left
    QToolButton *mAlignLeft;
    // align center
    QToolButton *mAlignCenter;
    // align right
    QToolButton *mAlignRight;
    // text color
    QToolButton *mTextColor;

    TextFormattingSetting mTextSetting;
};

#endif // TEXTFORMATTINGTOOLBAR_H
