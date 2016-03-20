#ifndef MAINFORM_H
#define MAINFORM_H

class ConfigForm;
class CChessGame;
class QImage;
struct CChessMan;
class QProgressBar;
class CQtProgress;

#include <QtGui>
#include <QtCore>
#include <QtWidgets/QtWidgets>
#include "Define.h"

class MainForm : public QMainWindow
{
    Q_OBJECT
public:
    QAction *fileNewAction;
    QAction *fileOpenAction;
    QAction *fileSaveAction;
    QAction *fileSaveAsAction;
    QAction *fileExitAction;
    QAction *editUndoAction;
    QAction *editRedoAction;
    QAction *helpAboutAction;
    QAction *editConfigAction;
    QAction *editnew_itemAction;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *textLabel1;
    QFrame *frameCanvas;
    //QListBox *listBox1;
    QProgressBar *progressBar;
    QToolBar *toolBar;
    QMenuBar *MenuBar;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *helpMenu;

    void setupUi(QMainWindow *MainForm)
    {
        if (MainForm->objectName().isEmpty())
            MainForm->setObjectName(QString::fromUtf8("MainForm"));
        MainForm->resize(580, 546);
        QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(0), static_cast<QSizePolicy::Policy>(0));
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainForm->sizePolicy().hasHeightForWidth());
        MainForm->setSizePolicy(sizePolicy);
        MainForm->setMinimumSize(QSize(510, 546));
        MainForm->setMaximumSize(QSize(600, 500));
        fileNewAction = new QAction(MainForm);
        fileNewAction->setObjectName(QString::fromUtf8("fileNewAction"));
        const QIcon icon = QIcon(":/images/images/filenew");
        fileNewAction->setIcon(icon);
        fileOpenAction = new QAction(MainForm);
        fileOpenAction->setObjectName(QString::fromUtf8("fileOpenAction"));
        const QIcon icon1 = QIcon(":/images/images/fileopen");
        fileOpenAction->setIcon(icon1);
        fileSaveAction = new QAction(MainForm);
        fileSaveAction->setObjectName(QString::fromUtf8("fileSaveAction"));
        const QIcon icon2 = QIcon(":/images/images/filesave");
        fileSaveAction->setIcon(icon2);
        fileSaveAsAction = new QAction(MainForm);
        fileSaveAsAction->setObjectName(QString::fromUtf8("fileSaveAsAction"));
        fileExitAction = new QAction(MainForm);
        fileExitAction->setObjectName(QString::fromUtf8("fileExitAction"));
        editUndoAction = new QAction(MainForm);
        editUndoAction->setObjectName(QString::fromUtf8("editUndoAction"));
        const QIcon icon3 = QIcon(":/images/images/undo");
        editUndoAction->setIcon(icon3);
        editRedoAction = new QAction(MainForm);
        editRedoAction->setObjectName(QString::fromUtf8("editRedoAction"));
        const QIcon icon4 = QIcon(":/images/images/redo");
        editRedoAction->setIcon(icon4);
        helpAboutAction = new QAction(MainForm);
        helpAboutAction->setObjectName(QString::fromUtf8("helpAboutAction"));
        editConfigAction = new QAction(MainForm);
        editConfigAction->setObjectName(QString::fromUtf8("editConfigAction"));
        const QIcon icon5 = QIcon(":/images/images/searchfind");
        editConfigAction->setIcon(icon5);
        editnew_itemAction = new QAction(MainForm);
        editnew_itemAction->setObjectName(QString::fromUtf8("editnew_itemAction"));
        widget = new QWidget(MainForm);
        widget->setObjectName(QString::fromUtf8("widget"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        textLabel1 = new QLabel(widget);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
        textLabel1->setWordWrap(false);

        gridLayout->addWidget(textLabel1, 1, 0, 1, 1);

        frameCanvas = new QFrame(widget);
        frameCanvas->setObjectName(QString::fromUtf8("frameCanvas"));
        frameCanvas->setMinimumSize(QSize(376, 413));
        frameCanvas->setMaximumSize(QSize(376, 413));
        frameCanvas->setFrameShape(QFrame::StyledPanel);
        frameCanvas->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(frameCanvas, 0, 0, 1, 2);

        /*
        listBox1 = new Q3ListBox(widget);
        listBox1->setObjectName(QString::fromUtf8("listBox1"));
        QSizePolicy sizePolicy1(static_cast<QSizePolicy::Policy>(7), static_cast<QSizePolicy::Policy>(7));
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(listBox1->sizePolicy().hasHeightForWidth());
        listBox1->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(listBox1, 0, 2, 2, 1);
        */

        progressBar = new QProgressBar(widget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));

        gridLayout->addWidget(progressBar, 1, 1, 1, 1);

        MainForm->setCentralWidget(widget);
        toolBar = new QToolBar("Tools", MainForm);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MenuBar = new QMenuBar(MainForm);
        MenuBar->setObjectName(QString::fromUtf8("MenuBar"));
        fileMenu = new QMenu(MenuBar);
        fileMenu->setObjectName(QString::fromUtf8("fileMenu"));
        editMenu = new QMenu(MenuBar);
        editMenu->setObjectName(QString::fromUtf8("editMenu"));
        helpMenu = new QMenu(MenuBar);
        helpMenu->setObjectName(QString::fromUtf8("helpMenu"));

        toolBar->addAction(fileNewAction);
        toolBar->addAction(fileOpenAction);
        toolBar->addAction(fileSaveAction);
        toolBar->addSeparator();
        toolBar->addAction(editUndoAction);
        toolBar->addAction(editRedoAction);
        toolBar->addAction(editConfigAction);
        toolBar->addSeparator();
        MenuBar->addAction(fileMenu->menuAction());
        MenuBar->addAction(editMenu->menuAction());
        MenuBar->addAction(helpMenu->menuAction());
        fileMenu->addAction(fileNewAction);
        fileMenu->addAction(fileOpenAction);
        fileMenu->addAction(fileSaveAction);
        fileMenu->addAction(fileSaveAsAction);
        fileMenu->addSeparator();
        fileMenu->addSeparator();
        fileMenu->addAction(fileExitAction);
        editMenu->addAction(editUndoAction);
        editMenu->addAction(editRedoAction);
        editMenu->addSeparator();
        editMenu->addAction(editConfigAction);
        helpMenu->addSeparator();
        helpMenu->addAction(helpAboutAction);

        retranslateUi(MainForm);
        QObject::connect(fileNewAction, SIGNAL(triggered()), MainForm, SLOT(fileNew()));
        QObject::connect(fileOpenAction, SIGNAL(triggered()), MainForm, SLOT(fileOpen()));
        QObject::connect(fileSaveAction, SIGNAL(triggered()), MainForm, SLOT(fileSave()));
        QObject::connect(fileSaveAsAction, SIGNAL(triggered()), MainForm, SLOT(fileSaveAs()));
        QObject::connect(fileExitAction, SIGNAL(triggered()), MainForm, SLOT(fileExit()));
        QObject::connect(editUndoAction, SIGNAL(triggered()), MainForm, SLOT(editUndo()));
        QObject::connect(editRedoAction, SIGNAL(triggered()), MainForm, SLOT(editRedo()));
        QObject::connect(helpAboutAction, SIGNAL(triggered()), MainForm, SLOT(helpAbout()));
        QObject::connect(editConfigAction, SIGNAL(triggered()), MainForm, SLOT(editConfigAction_activated()));
        //QObject::connect(MainForm, SIGNAL(usesTextLabelChanged(bool)), MainForm, SLOT(MainForm_usesTextLabelChanged(bool)));

        QMetaObject::connectSlotsByName(MainForm);
    } // setupUi

    void retranslateUi(QMainWindow *MainForm)
    {
        MainForm->setWindowTitle(QApplication::translate("MainForm", "Main Form", 0));
        fileNewAction->setIconText(QApplication::translate("MainForm", "New", 0));
        fileNewAction->setText(QApplication::translate("MainForm", "&New", 0));
        fileNewAction->setShortcut(QApplication::translate("MainForm", "Ctrl+N", 0));
        fileOpenAction->setIconText(QApplication::translate("MainForm", "Open", 0));
        fileOpenAction->setText(QApplication::translate("MainForm", "&Open...", 0));
        fileOpenAction->setShortcut(QApplication::translate("MainForm", "Ctrl+O", 0));
        fileSaveAction->setIconText(QApplication::translate("MainForm", "Save", 0));
        fileSaveAction->setText(QApplication::translate("MainForm", "&Save", 0));
        fileSaveAction->setShortcut(QApplication::translate("MainForm", "Ctrl+S", 0));
        fileSaveAsAction->setIconText(QApplication::translate("MainForm", "Save As", 0));
        fileSaveAsAction->setText(QApplication::translate("MainForm", "Save &As...", 0));
        fileSaveAsAction->setShortcut(QString());
        fileExitAction->setIconText(QApplication::translate("MainForm", "Exit", 0));
        fileExitAction->setText(QApplication::translate("MainForm", "E&xit", 0));
        fileExitAction->setShortcut(QString());
        editUndoAction->setIconText(QApplication::translate("MainForm", "Undo", 0));
        editUndoAction->setText(QApplication::translate("MainForm", "&Undo", 0));
        editUndoAction->setShortcut(QApplication::translate("MainForm", "Ctrl+Z", 0));
        editRedoAction->setIconText(QApplication::translate("MainForm", "Redo", 0));
        editRedoAction->setText(QApplication::translate("MainForm", "&Redo", 0));
        editRedoAction->setShortcut(QApplication::translate("MainForm", "Ctrl+Y", 0));
        helpAboutAction->setIconText(QApplication::translate("MainForm", "About", 0));
        helpAboutAction->setText(QApplication::translate("MainForm", "&About", 0));
        helpAboutAction->setShortcut(QString());
        editConfigAction->setIconText(QApplication::translate("MainForm", "Config", 0));
        editnew_itemAction->setIconText(QApplication::translate("MainForm", "new item", 0));
        editnew_itemAction->setText(QApplication::translate("MainForm", "new item", 0));
        textLabel1->setText(QApplication::translate("MainForm", "I'm thinking:", 0));
        toolBar->addAction(QApplication::translate("MainForm", "Tools", 0));
        fileMenu->setTitle(QApplication::translate("MainForm", "&File", 0));
        editMenu->setTitle(QApplication::translate("MainForm", "&Edit", 0));
        helpMenu->setTitle(QApplication::translate("MainForm", "&Help", 0));
    } // retranslateUi


public:
    MainForm(QWidget* parent = 0, Qt::WindowFlags fl = Qt::Desktop);
    ~MainForm();

    virtual bool eventFilter( QObject * target, QEvent * event );
    virtual void redrawBoard( int mouseX, int mouseY );
    virtual void posAtPoint( CChessMan * man, QPoint const & point );
    virtual void showStatus( QString const & str );
    virtual bool isSelectRight( CChessMan * man );
    virtual void restartGame();
    virtual QProgressBar * getProgress();
    virtual void think();

public slots:
    virtual void fileNew();
    virtual void fileOpen();
    virtual void fileSave();
    virtual void fileSaveAs();
    virtual void fileExit();
    virtual void editUndo();
    virtual void editRedo();
    virtual void helpAbout();
    virtual void editConfigAction_activated();
    virtual void initializeAll();
    virtual void MainForm_usesTextLabelChanged( bool );

protected:
    BYTE backupBoard[10][9];
    int status;
    ConfigForm* configForm;
    CChessGame* chessGame;
    QImage* boardImage;
    QImage* chessMen[14];
    CChessMan* activeMan;
    CQtProgress* qtProgress;

protected slots:
    virtual void languageChange();

};

#endif // MAINFORM_H
