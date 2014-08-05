#include "editortoolbar.h"

#include <QDebug>
#include <QComboBox>
#include <QAction>
#include <QToolButton>
#include <QSpacerItem>
#include <QStringList>

#include "util.h"


EditorToolBar::EditorToolBar(const QString& name,QWidget *parent) :
    ToolBar(name,parent)
{
    this->setObjectName(name);

    this->createToolbar();
    this->createConnect();
}

void EditorToolBar::createToolbar()
{
    mSelectMode = new QAction(this);
    mSelectMode->setObjectName(tr("SelectMode"));
    mSelectMode->setText(tr("Select Mode"));
    mSelectMode->setToolTip(tr("Select Mode"));
    QIcon selectModeIcon;
    selectModeIcon.addFile(QStringLiteral(":/SelectMode.png"), QSize(), QIcon::Normal, QIcon::Off);
    mSelectMode->setIcon(selectModeIcon);
    mSelectMode->setCheckable(true);
    mSelectMode->setChecked(true);

    mConnectorMode = new QAction(this);
    mConnectorMode->setObjectName(tr("ConnectorMode"));
    mConnectorMode->setText(tr("Connector Mode"));
    mConnectorMode->setToolTip(tr("Connector Mode"));
    QIcon connectorModeIcon;
    connectorModeIcon.addFile(QStringLiteral(":/ConnectorMode.png"), QSize(), QIcon::Normal, QIcon::Off);
    mConnectorMode->setIcon(connectorModeIcon);
    mConnectorMode->setCheckable(true);

    mZoom = new QComboBox(this);
    mZoom->setObjectName(tr("Zoom"));
    mZoom->setToolTip(tr("Zoom"));
    mZoom->setMinimumWidth(60);
    //mZoom->setEditable(true);
    QStringList zoomPercent;
    Util::getZoomPercent(zoomPercent);
    mZoom->addItems(zoomPercent);
    mZoom->setCurrentText(tr("100%"));
    mZoom->setVisible(false);

    this->addAction(mSelectMode);
    this->addAction(mConnectorMode);
    this->addSeparator();
    //this->addWidget(mZoom);
}

void EditorToolBar::createConnect()
{
    connect(this,SIGNAL(actionTriggered(QAction*)),this,SLOT(slotHandleActrionTriggered(QAction*)));
    connect(mZoom,SIGNAL(currentTextChanged(QString)),this,SIGNAL(sigZoomPercentChanged(QString)));
}

void EditorToolBar::slotHandleActrionTriggered(QAction *action)
{
    if(action->objectName() == tr("SelectMode"))
    {
        mSelectMode->setChecked(true);
        mConnectorMode->setChecked(false);
        emit sigSceneModeChanged(SceneMode_Select);
    }
    else if(action->objectName() == tr("ConnectorMode"))
    {
        mSelectMode->setChecked(false);
        mConnectorMode->setChecked(true);
        emit sigSceneModeChanged(SceneMode_Connector);
    }
}
