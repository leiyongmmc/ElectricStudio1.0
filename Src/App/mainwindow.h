#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QSplitter;
class QGridLayout;
class ToolboxWidget;
class GraphicsScene;
class GraphicsView;
class PropertiesAndStyleWidget;
class StatuBar;
class CoordinateFrame;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    // close event
    void closeEvent(QCloseEvent *);
private:
    void init();
    // create center widget
    void createCenterLayout();
    // create connect
    void createConnect();
    // clear scene and prop
    void clearSceneAndProp();
private slots:
    // new
    void slotNew();
    // open
    void slotOpen();
    // save
    void slotSave();
    // save as
    void slotSaveAs();
    // views
    void slotSetWidgetPaneVisible(bool);
    void slotSetPropertyPaneVisible(bool);
    void slotSetPanesVisible();

    // redo
    void slotRedo();
    void slotUndo();
private:
    QSplitter        *mHSplitter;
    ToolboxWidget    *mToolboxWgd;
    //CoordinateFrame  *mLeftCoordinate;
    //QSplitter        *mVSplitter;
    GraphicsScene    *mGraphicsScene;
    GraphicsView     *mGraphicsView;
    //CoordinateFrame  *mBottomCoordinate;
    PropertiesAndStyleWidget *mPropWgd;

    //
    StatuBar *mStatuBar;

};

#endif // MAINWINDOW_H
