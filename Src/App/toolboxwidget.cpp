#include "toolboxwidget.h"

#include <QApplication>
#include <QToolButton>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QScrollArea>

#include <QFileDialog>

#include "toolboxtoolbar.h"
#include "resourcetreewidget.h"
#include "resourcemanager.h"

#include "FileInfo/fileservice.h"



ToolboxWidget::ToolboxWidget(QWidget *parent) :
    QDialog(parent)
{
    // init load all
    ResourceManager::getManager()->initAllResources();
    // create layout
    this->createLayout();
	// create connect
    this->createConnect();
}

void ToolboxWidget::slotImportFile()
{
    QString fileName = QFileDialog::getOpenFileName(0
                                            , QObject::tr("Import Resource File")
                                            , QApplication::applicationDirPath()
                                            , QObject::tr("Png files (*.png)"));
    if(FileService::sharedFileService()->vaildFile(fileName))
    {
        mResTreeWidget->importFile(fileName);
    }
}
void ToolboxWidget::slotImportFolder()
{
    QString dirName = QFileDialog::getExistingDirectory(0
                                                        , QObject::tr("Import Resource Folder")
                                                        );
    if(FileService::sharedFileService()->vaildFile(dirName))
    {
        mResTreeWidget->importFolder(dirName);
    }
}

void ToolboxWidget::slotRefreshResource()
{
    mResTreeWidget->refreshRes();
}

void ToolboxWidget::slotDeleteItemFromResource()
{
    mResTreeWidget->deleteRes();
}

// 创建显示
void ToolboxWidget::createLayout()
{
    mGridLayout = new QGridLayout(this);
    mGridLayout->setSpacing(0);
    mGridLayout->setContentsMargins(0,0,0,0);
    mTitle          = new QLabel(tr("Resource"),this);
    mTitle->setObjectName(tr("toolboxtitle"));
    mTitle->setAlignment(Qt::AlignHCenter);
    mTitle->setFixedHeight(20);

    mToolBar        = new ToolboxToolBar(tr("ToolBox"),this);
    mFindLineEdit   = new QLineEdit(this);
	// init visible
    mFindLineEdit->setVisible(false);
    mResTreeWidget    = new ResourceTreeWidget(this);

    mGridLayout->addWidget(mTitle,0,0,1,1);
    mGridLayout->addWidget(mToolBar,1,0,1,1);
    mGridLayout->addWidget(mFindLineEdit,2,0,1,1);
    mGridLayout->addWidget(mResTreeWidget,3,0,1,1);
}

void ToolboxWidget::createConnect()
{
    connect(mToolBar,SIGNAL(sigFilterLineEditVisible(bool)),this,SLOT(slotSetFindLineEditVisible(bool)));
    connect(mToolBar->mImportFileBtn,SIGNAL(clicked()),this,SLOT(slotImportFile()));
    connect(mToolBar->mImportFolderBtn,SIGNAL(clicked()),this,SLOT(slotImportFolder()));
    connect(mToolBar->mRefreshBtn,SIGNAL(clicked()),this,SLOT(slotRefreshResource()));
    connect(mResTreeWidget,SIGNAL(signalSelectItemType(QString)),this,SIGNAL(signalSelectItemType(QString)));

    connect(mResTreeWidget,SIGNAL(sigItemType(int)),this,SIGNAL(sigItemType(int)));
    connect(mResTreeWidget,SIGNAL(sigItemType(int)),mToolBar,SLOT(slotSetBtnEnableState(int)));
}

void ToolboxWidget::slotSetFindLineEditVisible(bool b)
{
    mFindLineEdit->setVisible(b);
}
