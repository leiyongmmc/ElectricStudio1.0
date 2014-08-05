#include "actionmanager.h"

#include <QMainWindow>

#include "../optionsdialog.h"

ActionManager* ActionManager::s_SharedActionManager = NULL;

ActionManager* ActionManager::sharedActionManager()
{
    if(!s_SharedActionManager)
        s_SharedActionManager = new ActionManager();

    return s_SharedActionManager;
}

void ActionManager::destroyManager()
{
    delete s_SharedActionManager;
    s_SharedActionManager = NULL;
}

ActionManager::ActionManager(QObject *parent) :
    QObject(parent)
{
}

ActionManager::~ActionManager()
{

}

void ActionManager::createActions(QMainWindow *parent)
{
    if(!parent)
        return;

    m_ActionNew = new QAction(parent);
    m_ActionNew->setText(tr("New"));
    m_ActionNew->setToolTip(tr("New"));
    m_ActionNew->setObjectName(QStringLiteral("actionNew"));
    QIcon icon;
    icon.addFile(QStringLiteral(":/New.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_ActionNew->setIcon(icon);
    m_ActionNew->setShortcut(QKeySequence::New);
    m_ActionOpen = new QAction(parent);
    m_ActionOpen->setText(tr("Open"));
    m_ActionOpen->setToolTip(tr("Open"));
    m_ActionOpen->setObjectName(QStringLiteral("actionOpen"));
    m_ActionOpen->setShortcut(QKeySequence::Open);
    QIcon icon1;
    icon1.addFile(QStringLiteral(":/Open.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_ActionOpen->setIcon(icon1);
    m_ActionSave = new QAction(parent);
    m_ActionSave->setText(tr("Save"));
    m_ActionSave->setToolTip(tr("Save"));
    m_ActionSave->setShortcut(QKeySequence::Save);
    m_ActionSave->setObjectName(QStringLiteral("actionSave"));
    QIcon icon2;
    icon2.addFile(QStringLiteral(":/Save.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_ActionSave->setIcon(icon2);
    m_ActionSaveAs = new QAction(parent);
    m_ActionSaveAs->setText(tr("Save As..."));
    m_ActionSaveAs->setToolTip(tr("Save As..."));
    m_ActionSaveAs->setShortcut(QKeySequence::SaveAs);
    m_ActionSaveAs->setObjectName(QStringLiteral("actionSave_As"));

    m_ActionImportFile = new QAction(parent);
    m_ActionImportFile->setText(tr("Import File"));
    m_ActionImportFile->setToolTip(tr("Import File"));
    m_ActionImportFile->setObjectName(QStringLiteral("actionImport_File"));

    m_ActionImportFolder = new QAction(parent);
    m_ActionImportFolder->setText(tr("Import Folder"));
    m_ActionImportFolder->setToolTip(tr("Import Folder"));
    m_ActionImportFolder->setObjectName(QStringLiteral("actionImport_Folder"));

    m_ActionExit = new QAction(parent);
    m_ActionExit->setText(tr("Exit"));
    m_ActionExit->setToolTip(tr("Exit"));
    m_ActionExit->setObjectName(QStringLiteral("actionExit"));
    m_ActionExit->setShortcut(QKeySequence::Quit);


    m_ActionRedo = new QAction(parent);
    m_ActionRedo->setText(tr("Redo"));
    m_ActionRedo->setToolTip(tr("Redo"));
    m_ActionRedo->setShortcut(QKeySequence::Redo);
    m_ActionRedo->setObjectName(QStringLiteral("actionRedo"));
    QIcon icon3;
    icon3.addFile(QStringLiteral(":/Redo.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_ActionRedo->setIcon(icon3);
    m_ActionUndo = new QAction(parent);
    m_ActionUndo->setText(tr("Undo"));
    m_ActionUndo->setToolTip(tr("Undo"));
    m_ActionUndo->setShortcut(QKeySequence::Undo);
    m_ActionUndo->setObjectName(QStringLiteral("actionUndo"));
    QIcon icon4;
    icon4.addFile(QStringLiteral(":/Undo.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_ActionUndo->setIcon(icon4);
    m_ActionCut = new QAction(parent);
    m_ActionCut->setText(tr("Cut"));
    m_ActionCut->setToolTip(tr("Cut"));
    m_ActionCut->setShortcut(QKeySequence::Cut);
    m_ActionCut->setObjectName(QStringLiteral("actionCut"));
    QIcon icon5;
    icon5.addFile(QStringLiteral(":/Cut.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_ActionCut->setIcon(icon5);
    m_ActionCopy = new QAction(parent);
    m_ActionCopy->setText(tr("Copy"));
    m_ActionCopy->setToolTip(tr("Copy"));
    m_ActionCopy->setShortcut(QKeySequence::Copy);
    m_ActionCopy->setObjectName(QStringLiteral("actionCopy"));
    QIcon icon6;
    icon6.addFile(QStringLiteral(":/Copy.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_ActionCopy->setIcon(icon6);
    m_ActionPaste = new QAction(parent);
    m_ActionPaste->setText(tr("Paste"));
    m_ActionPaste->setToolTip(tr("Paste"));
    m_ActionPaste->setShortcut(QKeySequence::Paste);
    m_ActionPaste->setObjectName(QStringLiteral("actionPaste"));
    QIcon icon7;
    icon7.addFile(QStringLiteral(":/Paste.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_ActionPaste->setIcon(icon7);
    m_ActionFind = new QAction(parent);
    m_ActionFind->setText(tr("Find"));
    m_ActionFind->setToolTip(tr("Find"));
    m_ActionFind->setShortcut(QKeySequence::Find);
    m_ActionFind->setObjectName(QStringLiteral("actionFind"));
    m_ActionReplace = new QAction(parent);
    m_ActionReplace->setText(tr("Replace"));
    m_ActionReplace->setToolTip("Replace");
    m_ActionReplace->setShortcut(QKeySequence::Replace);
    m_ActionReplace->setObjectName(QStringLiteral("actionReplace"));
    m_ActionSelectAll = new QAction(parent);
    m_ActionSelectAll->setText(tr("Select All"));
    m_ActionSelectAll->setToolTip(tr("Select All"));
    m_ActionSelectAll->setShortcut(QKeySequence::SelectAll);
    m_ActionSelectAll->setObjectName(QStringLiteral("actionSelect_All"));
    m_ActionDelete = new QAction(parent);
    m_ActionDelete->setText(tr("Delete"));
    m_ActionDelete->setToolTip(tr("Delete"));
    m_ActionDelete->setShortcut(QKeySequence::Delete);
    m_ActionDelete->setObjectName(QStringLiteral("actionDelete"));

    m_ActionMainToolBar = new QAction(parent);
    m_ActionMainToolBar->setText(tr("Main Toolbar"));
    m_ActionMainToolBar->setToolTip(tr("Main Toolbar"));
    m_ActionMainToolBar->setObjectName(QStringLiteral("MainToolBar"));
    m_ActionMainToolBar->setCheckable(true);
    m_ActionMainToolBar->setChecked(true);
    m_ActionEditorToolBar = new QAction(parent);
    m_ActionEditorToolBar->setText(tr("Editor Toolbar"));
    m_ActionEditorToolBar->setToolTip(tr("Editor Toolbar"));
    m_ActionEditorToolBar->setObjectName(QStringLiteral("EditorToolBar"));
    m_ActionEditorToolBar->setCheckable(true);
    m_ActionEditorToolBar->setChecked(true);
    m_ActionArrangeToolBar = new QAction(parent);
    m_ActionArrangeToolBar->setText(tr("Arrange Toolbar"));
    m_ActionArrangeToolBar->setToolTip(tr("Arrange Toolbar"));
    m_ActionArrangeToolBar->setObjectName(QStringLiteral("ArrangeToolBar"));
    m_ActionArrangeToolBar->setCheckable(true);
    m_ActionArrangeToolBar->setChecked(true);
    m_ActionShapeFormatToolBar = new QAction(parent);
    m_ActionShapeFormatToolBar->setText(tr("Shape Format Toolbar"));
    m_ActionShapeFormatToolBar->setToolTip(tr("Shape Format Toolbar"));
    m_ActionShapeFormatToolBar->setObjectName(QStringLiteral("ShapeFormattingToolBar"));
    m_ActionShapeFormatToolBar->setCheckable(true);
    m_ActionShapeFormatToolBar->setChecked(true);
    m_ActionTextFormatToolBar = new QAction(parent);
    m_ActionTextFormatToolBar->setText(tr("Text Format Toolbar"));
    m_ActionTextFormatToolBar->setToolTip(tr("Text Format Toolbar"));
    m_ActionTextFormatToolBar->setObjectName(QStringLiteral("TextFormattingToolBar"));
    m_ActionTextFormatToolBar->setCheckable(true);
    m_ActionTextFormatToolBar->setChecked(true);
    m_ActionLocationAndSizeToolBar = new QAction(parent);
    m_ActionLocationAndSizeToolBar->setText(tr("Location And Size Toolbar"));
    m_ActionLocationAndSizeToolBar->setToolTip(tr("Location And Size Toolbar"));
    m_ActionLocationAndSizeToolBar->setObjectName(QStringLiteral("LocationAndSizeToolBar"));
    m_ActionLocationAndSizeToolBar->setCheckable(true);
    m_ActionLocationAndSizeToolBar->setChecked(true);

    m_ActionWidgetPane = new QAction(parent);
    m_ActionWidgetPane->setText(tr("Widget Pane"));
    m_ActionWidgetPane->setToolTip(tr("Widget Pane"));
    m_ActionWidgetPane->setObjectName(QStringLiteral("actionWidgetPane"));
    m_ActionWidgetPane->setCheckable(true);
    m_ActionWidgetPane->setChecked(true);

    m_ActionPropertyPane = new QAction(parent);
    m_ActionPropertyPane->setText(tr("Property Pane"));
    m_ActionPropertyPane->setToolTip(tr("Property Pane"));
    m_ActionPropertyPane->setObjectName(QStringLiteral("actionPropertyPane"));
    m_ActionPropertyPane->setCheckable(true);
    m_ActionPropertyPane->setChecked(true);


    m_ActionResetView = new QAction(parent);
    m_ActionResetView->setText(tr("Reset Views"));
    m_ActionResetView->setToolTip(tr("Reset Views"));
    m_ActionResetView->setObjectName(QStringLiteral("actionResetView"));

    m_ActionGroup = new QAction(parent);
    m_ActionGroup->setText(tr("Group"));
    m_ActionGroup->setToolTip(tr("Group"));
    m_ActionGroup->setObjectName(QStringLiteral("actionGroup"));
    QIcon icon16;
    icon16.addFile(QStringLiteral(":/Group.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_ActionGroup->setIcon(icon16);
    m_ActionUngroup = new QAction(parent);
    m_ActionUngroup->setText(tr("Ungroup"));
    m_ActionUngroup->setToolTip(tr("Ungroup"));
    m_ActionUngroup->setObjectName(QStringLiteral("actionUngroup"));
    QIcon icon17;
    icon17.addFile(QStringLiteral(":/UnGroup.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_ActionUngroup->setIcon(icon17);

    m_ActionAlignLeft = new QAction(parent);
    m_ActionAlignLeft->setText(tr("Align Left"));
    m_ActionAlignLeft->setToolTip(tr("Align Left"));
    m_ActionAlignLeft->setObjectName(QStringLiteral("actionAlignLeft"));
    QIcon icon8;
    icon8.addFile(QStringLiteral(":/AlignLeft.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_ActionAlignLeft->setIcon(icon8);
    m_ActionAlignCenter = new QAction(parent);
    m_ActionAlignCenter->setText(tr("Align Center"));
    m_ActionAlignCenter->setToolTip(tr("Align Center"));
    m_ActionAlignCenter->setObjectName(QStringLiteral("actionAlignCenter"));
    QIcon icon9;
    icon9.addFile(QStringLiteral(":/AlignCenter.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_ActionAlignCenter->setIcon(icon9);
    m_ActionAlignRight = new QAction(parent);
    m_ActionAlignRight->setText(tr("Align Right"));
    m_ActionAlignRight->setToolTip(tr("Align Right"));
    m_ActionAlignRight->setObjectName(QStringLiteral("actionAlignRight"));
    QIcon icon10;
    icon10.addFile(QStringLiteral(":/AlignRight.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_ActionAlignRight->setIcon(icon10);
    m_ActionAlignTop = new QAction(parent);
    m_ActionAlignTop->setText(tr("Align Top"));
    m_ActionAlignTop->setToolTip(tr("Align Top"));
    m_ActionAlignTop->setObjectName(QStringLiteral("actionAlignTop"));
    QIcon icon11;
    icon11.addFile(QStringLiteral(":/AlignTop.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_ActionAlignTop->setIcon(icon11);
    m_ActionAlignMiddle = new QAction(parent);
    m_ActionAlignMiddle->setText(tr("Align Middle"));
    m_ActionAlignMiddle->setToolTip(tr("Align Middle"));
    m_ActionAlignMiddle->setObjectName(QStringLiteral("actionAlignMiddle"));
    QIcon icon12;
    icon12.addFile(QStringLiteral(":/AlignMiddle.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_ActionAlignMiddle->setIcon(icon12);
    m_ActionAlignBottom = new QAction(parent);
    m_ActionAlignBottom->setText(tr("Align Bottom"));
    m_ActionAlignBottom->setToolTip(tr("Align Bottom"));
    m_ActionAlignBottom->setObjectName(QStringLiteral("actionAlignBottom"));
    QIcon icon13;
    icon13.addFile(QStringLiteral(":/AlignBottom.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_ActionAlignBottom->setIcon(icon13);

    m_ActionDistributeH = new QAction(parent);
    m_ActionDistributeH->setText(tr("Distribute Horizontal"));
    m_ActionDistributeH->setToolTip(tr("Distribute Horizontal"));
    m_ActionDistributeH->setObjectName(QStringLiteral("actionDistributeHorizontally"));
    QIcon icon14;
    icon14.addFile(QStringLiteral(":/DistributeH.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_ActionDistributeH->setIcon(icon14);
    m_ActionDistributeV = new QAction(parent);
    m_ActionDistributeV->setText(tr("Distribute Vertical"));
    m_ActionDistributeV->setToolTip(tr("Distribute Vertical"));
    m_ActionDistributeV->setObjectName(QStringLiteral("actionDistributeVertically"));
    QIcon icon15;
    icon15.addFile(QStringLiteral(":/DistributeV.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_ActionDistributeV->setIcon(icon15);
    m_ActionShowGrid = new QAction(parent);
    m_ActionShowGrid->setText(tr("Show Grid"));
    m_ActionShowGrid->setToolTip(tr("Show Grid"));
    m_ActionShowGrid->setObjectName(QStringLiteral("actionShowGrid"));
    m_ActionShowGrid->setCheckable(true);
    m_ActionShowGrid->setChecked(true);
    m_ActionSnaptoGrid = new QAction(parent);
    m_ActionSnaptoGrid->setText(tr("Snap to Grid"));
    m_ActionSnaptoGrid->setToolTip(tr("Snap to Grid"));
    m_ActionSnaptoGrid->setObjectName(QStringLiteral("actionSnaptoGrid"));
    m_ActionSnaptoGrid->setCheckable(true);
    m_ActionSnaptoGrid->setChecked(true);
    m_ActionGridSetting = new QAction(parent);
    m_ActionGridSetting->setText(tr("Grid Setting"));
    m_ActionGridSetting->setToolTip(tr("Grid Setting"));
    m_ActionGridSetting->setObjectName(QStringLiteral("actionGridSetting"));


    m_ActionOptions = new QAction(parent);
    m_ActionOptions->setText(tr("Options"));
    m_ActionOptions->setToolTip(tr("Options"));
    m_ActionOptions->setObjectName(QStringLiteral("actionOptions"));

    m_ActionZoomIn10 = new QAction(parent);
    m_ActionZoomIn10->setText(tr("10%"));
    m_ActionZoomIn10->setToolTip(tr("Zoom In 10%"));
    m_ActionZoomIn10->setObjectName(QStringLiteral("actionZoomIn10"));

    m_ActionZoomIn20 = new QAction(parent);
    m_ActionZoomIn20->setText(tr("20%"));
    m_ActionZoomIn20->setToolTip(tr("Zoom In 20%"));
    m_ActionZoomIn20->setObjectName(QStringLiteral("actionZoomIn20"));

    m_ActionZoomIn50 = new QAction(parent);
    m_ActionZoomIn50->setText(tr("50%"));
    m_ActionZoomIn50->setToolTip(tr("Zoom In 50%"));
    m_ActionZoomIn50->setObjectName(QStringLiteral("actionZoomIn50"));

    m_ActionZoomIn100 = new QAction(parent);
    m_ActionZoomIn100->setText(tr("100%"));
    m_ActionZoomIn100->setToolTip(tr("Zoom In 100%"));
    m_ActionZoomIn100->setObjectName(QStringLiteral("actionZoomIn100"));

    m_ActionZoomOut10 = new QAction(parent);
    m_ActionZoomOut10->setText(tr("10%"));
    m_ActionZoomOut10->setToolTip(tr("Zoom Out 10%"));
    m_ActionZoomOut10->setObjectName(QStringLiteral("actionZoomOut10"));

    m_ActionZoomOut20 = new QAction(parent);
    m_ActionZoomOut20->setText(tr("20%"));
    m_ActionZoomOut20->setToolTip(tr("Zoom Out 20%"));
    m_ActionZoomOut20->setObjectName(QStringLiteral("actionZoomOut20"));

    m_ActionZoomOut50 = new QAction(parent);
    m_ActionZoomOut50->setText(tr("50%"));
    m_ActionZoomOut50->setToolTip(tr("Zoom Out 50%"));
    m_ActionZoomOut50->setObjectName(QStringLiteral("actionZoomOut50"));

    m_ActionZoomOut100 = new QAction(parent);
    m_ActionZoomOut100->setText(tr("100%"));
    m_ActionZoomOut100->setToolTip(tr("Zoom Out 100%"));
    m_ActionZoomOut100->setObjectName(QStringLiteral("actionZoomOut100"));

    m_ActionRotateR90 = new QAction(parent);
    m_ActionRotateR90->setText(tr("Rotate 45 CW"));
    m_ActionRotateR90->setToolTip(tr("Rotate 45 Degrees clockwise"));
    m_ActionRotateR90->setObjectName(QStringLiteral("actionRotate45CW"));

    m_ActionRotateL90 = new QAction(parent);
    m_ActionRotateL90->setText(tr("Rotate 45 CCW"));
    m_ActionRotateL90->setToolTip(tr("Rotate 45 Degrees Counter-clockwise"));
    m_ActionRotateL90->setObjectName(QStringLiteral("actionRotate45CCW"));


    m_ActionRotate180 = new QAction(parent);
    m_ActionRotate180->setText(tr("Rotate 180"));
    m_ActionRotate180->setToolTip(tr("Rotate 180 Degrees"));
    m_ActionRotate180->setObjectName(QStringLiteral("actionRotate180"));

    m_ActionFlipHorizontal = new QAction(parent);
    m_ActionFlipHorizontal->setText(tr("Flip Horizontal"));
    m_ActionFlipHorizontal->setToolTip(tr("Flip Horizontal"));
    m_ActionFlipHorizontal->setObjectName(QStringLiteral("actionFlipHorizontal"));

    m_ActionFlipVertical = new QAction(parent);
    m_ActionFlipVertical->setText(tr("Flip Vertical"));
    m_ActionFlipVertical->setToolTip(tr("Flip Vertical"));
    m_ActionFlipVertical->setObjectName(QStringLiteral("actionFlipVertical"));

    m_actionRefreshrRes = new QAction(parent);
    m_actionRefreshrRes->setText(tr("Refresh Resource"));
    m_actionRefreshrRes->setToolTip(tr("Refresh Resource"));
    m_actionRefreshrRes->setObjectName(QStringLiteral("actionRefreshRes"));

    m_ActionDeleteRes = new QAction(parent);
    m_ActionDeleteRes->setText(tr("Delete Resource"));
    m_ActionDeleteRes->setToolTip(tr("Delete Resource"));
    m_ActionDeleteRes->setObjectName(QStringLiteral("actionDeleteRes"));

    this->resetEnableState();

    connect(m_ActionResetView,SIGNAL(triggered()),this,SLOT(slotResetPanes()));
    connect(m_ActionOptions,SIGNAL(triggered()),this,SLOT(slotShowOptionsWidget()));
}

void ActionManager::resetEnableState()
{
    // file
    m_ActionSave->setEnabled(false);
    m_ActionSaveAs->setEnabled(false);
    // edit
    m_ActionRedo->setEnabled(false);
    m_ActionUndo->setEnabled(false);
    m_ActionCut->setEnabled(false);
    m_ActionCopy->setEnabled(false);
    m_ActionPaste->setEnabled(false);
    m_ActionDelete->setEnabled(false);
    // arrange
    m_ActionGroup->setEnabled(false);
    m_ActionUngroup->setEnabled(false);
    m_ActionAlignLeft->setEnabled(false);
    m_ActionAlignCenter->setEnabled(false);
    m_ActionAlignRight->setEnabled(false);
    m_ActionAlignTop->setEnabled(false);
    m_ActionAlignMiddle->setEnabled(false);
    m_ActionAlignBottom->setEnabled(false);
    m_ActionDistributeH->setEnabled(false);
    m_ActionDistributeV->setEnabled(false);
    // resource
    m_actionRefreshrRes->setEnabled(true);
    m_ActionImportFile->setEnabled(true);
    m_ActionImportFolder->setEnabled(true);
    m_ActionDeleteRes->setEnabled(false);

}

void ActionManager::slotSetResourceActionsState(int index)
{
    m_ActionImportFile->setEnabled(false);
    m_ActionImportFolder->setEnabled(false);
    m_ActionDeleteRes->setEnabled(false);
    if(index == 0)
    {
        m_ActionImportFolder->setEnabled(true);
    }
    else if(index == 1)
    {
        m_ActionImportFile->setEnabled(true);
        m_ActionDeleteRes->setEnabled(true);
    }
    else
    {
        m_ActionDeleteRes->setEnabled(true);
    }
}

void ActionManager::slotResetPanes()
{
    m_ActionWidgetPane->setChecked(true);
    m_ActionPropertyPane->setChecked(true);
}

void ActionManager::slotShowOptionsWidget()
{
    OptionsDialog *dig = new OptionsDialog();
    dig->setAttribute(Qt::WA_DeleteOnClose);
    dig->show();
}
