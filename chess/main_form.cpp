#include "main_form.h"

#include <qvariant.h>
#include <qimage.h>
#include <qpixmap.h>

#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <QGuiApplication>
//Added by qt3to4:
#include <QMouseEvent>
#include <QPixmap>
#include <QEvent>
#include "configform.h"
#include <QtWidgets/QStatusBar>
#include "chessgame.h"
#include "qpoint.h"
#include "qimage.h"
#include "qpainter.h"

static int mouseX = 0;
static int mouseY = 0;

struct CChessMan
{
    CHESSMANPOS pos;
    BYTE chessId;
};

class CQtProgress: public CProgress
{
public:
    CQtProgress(MainForm* theMainForm) {mainForm = theMainForm;}
    void setTotalSteps(int s){mainForm->getProgress()->setRange(0,s);}
    void setProgress(int p)
    {
        mainForm->getProgress()->setValue(p);
        qApp->processEvents();
    }
    int progress()const{return mainForm->getProgress()->value();}
    int totalSteps()const{return mainForm->getProgress()->maximum();}
    void nextStep(){setProgress(progress() + 1);}
    ~CQtProgress(){}
private:
    MainForm* mainForm;
};

enum {
    INITIALIZING,
    RED_THINKING,
    BLACK_THINKING,
    RED_MOVING,
    BLACK_MOVING,
    RED_WON,
    BLACK_WON
};

const char* statusStr(int status)
{
    switch(status)
    {
    case INITIALIZING:
        return "INITIALIZING";
    case RED_THINKING:
        return "RED_THINKING";
    case BLACK_THINKING:
        return "BLACK_THINKING";
    case RED_MOVING:
        return "RED_MOVING";
    case BLACK_MOVING:
        return "BLACK_MOVING";
    default:
        return "Unknown";
    }
}

#define DUMP_STATUS()\
do{\
   printf("status = %s, line %d\n",\
          statusStr(status), __LINE__);\
}while(0)

void MainForm::fileNew()
{
    restartGame();
}


void MainForm::fileOpen()
{
    QString s = QFileDialog::getOpenFileName(
                    this,
                    "open file dialog",
                    "/home",
                    "Images (*.png *.xpm *.jpg)"
                    );
    if (s.isEmpty())
        s = "Nothing";
    QMessageBox::information(this, "The file is", s);
}


void MainForm::fileSave()
{

}


void MainForm::fileSaveAs()
{

}

void MainForm::fileExit()
{
    qApp->quit();
}


void MainForm::editUndo()
{
    chessGame->undo();
    memcpy(backupBoard, *chessGame->getBoard(), sizeof(backupBoard));
    //redrawBoard(0, 0);
    mouseX = mouseY = 0;
    repaint();
}


void MainForm::editRedo()
{
    chessGame->redo();
    memcpy(backupBoard, *chessGame->getBoard(), sizeof(backupBoard));
    //redrawBoard(0, 0);
    mouseX = mouseY = 0;
    repaint();
}

void MainForm::helpAbout()
{
    QMessageBox::information(this, "About this game",
                          "<b>To my dear quasi-girlfriend</b><br>"
                          "<em>I wish you beautiful forever, "
                          "you know I'll love you in all my life, "
                          "would you love me too?</em>"
                          "<div align=\"right\">--Trent</div>");
}


void MainForm::editConfigAction_activated()
{
    configForm->exec();
    if (chessGame->getEngine())
        chessGame->getEngine()->SetThinkProgress(qtProgress);
    status = INITIALIZING;
    memcpy(&backupBoard, *chessGame->getBoard(), sizeof(backupBoard));
}


void MainForm::initializeAll()
{
    QImage* allMen = NULL;
    int smallwidth = 0;
    int smallheight = 0;
    QString imagePath;
    status = INITIALIZING;

    frameCanvas->installEventFilter(this);
    progressBar->setRange(0,100);
    chessGame = new CChessGame();
    activeMan = new CChessMan();
    qtProgress = new CQtProgress(this);

    if (chessGame == NULL)
    {
        printf("chessGame is NULL!\n");
        exit(0);
    }
    configForm = new ConfigForm(this);
    configForm->initializeAll(chessGame);
    configForm->applyChanges();
    memcpy(&backupBoard, *chessGame->getBoard(), sizeof(backupBoard));

    if (chessGame->getEngine())
        chessGame->getEngine()->SetThinkProgress(qtProgress);
    /*
    imagePath = qApp->applicationDirPath() + "/images/board.bmp";
    boardImage = new QImage(imagePath);
    */
    boardImage = new QImage(":/images/images/board.bmp");
    if (!boardImage || boardImage->isNull())
    {
        printf("Can't open chess board bitmap\n");
        exit(0);
    }

    /*
    imagePath = qApp->applicationDirPath() + "/images/chessmen.png";
    allMen = new QImage(imagePath);
    */
    allMen = new QImage(":/images/images/chessmen.png");
    if (!allMen || allMen->isNull())
    {
        printf("Can't open chess men bitmap\n");
        exit(0);
    }
    smallwidth = allMen->width() / 14;
    smallheight = allMen->height();

    for (int i = 0; i < 14; i++)
    {
        chessMen[i] = new QImage(allMen->copy(i * smallwidth,
                                              0,
                                              smallwidth,
                                              smallheight));
    }
}


bool MainForm::eventFilter( QObject * target, QEvent * event )
{
    BYTE (&board)[10][9] = *chessGame->getBoard();

    if (target == frameCanvas)
    {
        QMouseEvent* mouseEvent = NULL;
        if (event->type() == QEvent::MouseButtonPress)
        {
            mouseEvent = (QMouseEvent*)event;
            posAtPoint(activeMan, mouseEvent->pos());
            if (isSelectRight(activeMan))
            {
                if (IsBlack(activeMan->chessId))
                    status = BLACK_MOVING;
                else
                    status = RED_MOVING;
                /* backup chess board */
                backupBoard[activeMan->pos.y][activeMan->pos.x] = NOCHESS;
                /* redraw the screen */
                //redrawBoard(mouseEvent->x(), mouseEvent->y());
                mouseX = mouseEvent->x();
                mouseY = mouseEvent->y();
                repaint();
            }
            else
            {
                activeMan->chessId = NOCHESS;
                showStatus(QString("That's not your chess on %1 %2")
                           .arg(activeMan->pos.x)
                           .arg(activeMan->pos.y));
            }
        }
        else if (event->type() == QEvent::MouseButtonRelease)
        {
            mouseEvent = (QMouseEvent*)event;
            if ((activeMan->chessId != NOCHESS)
                && (status != RED_THINKING) && (status != BLACK_THINKING))
                {
                /* get target position */
                CChessMan targetMan;
                posAtPoint(&targetMan, mouseEvent->pos());
                /* try to move */
                if (chessGame->moveChess(activeMan->pos,
                                         targetMan.pos,
                                         configForm->blackOnTop))
                {
                    if (status == RED_MOVING)
                    {
                        if (configForm->blackIsMan)
                        {
                            status = BLACK_MOVING;
                            showStatus("Black goes now");
                        }
                        else
                        {
                            status = BLACK_THINKING;
                            think();
                            showStatus("Black(computer) is thinking now");
                        }
                    }
                    else if (status == BLACK_MOVING)
                    {
                        if (configForm->redIsMan)
                        {
                            status = RED_MOVING;
                            showStatus("Red goes now");
                        }
                        else
                        {
                            status = RED_THINKING;
                            think();
                            showStatus("Red(computer is thinking now");
                        }
                    }
                    switch (chessGame->isGameOver())
                    {
                    case CChessGame::BLACK_WIN:
                        QMessageBox::information(this, "Black wins!",
                                                 "HAHAHAHA");
                        status = BLACK_WON;
                        restartGame();
                        break;
                    case CChessGame::RED_WIN:
                        QMessageBox::information(this, "Red wins!",
                                                 "HAHAHAHA");
                        status = RED_WON;
                        restartGame();
                        break;
                    default:
                        break;
                    }
                }
                memcpy(backupBoard, board, sizeof(board));
                activeMan->chessId = NOCHESS;
                //redrawBoard(0, 0);
                mouseX = 0;
                mouseY = 0;
                repaint();
            }
        }
        else if (event->type() == QEvent::MouseMove)
        {
            mouseEvent = (QMouseEvent*)event;
            //redrawBoard(mouseEvent->x(), mouseEvent->y());
            mouseX = mouseEvent->x();
            mouseY = mouseEvent->y();
            repaint();
        }
        else if (event->type() == QEvent::Paint)
        {
            redrawBoard(mouseX, mouseY);
        }
    }
    return QMainWindow::eventFilter(target, event);
}


void MainForm::MainForm_usesTextLabelChanged( bool )
{

}


void MainForm::redrawBoard(int mouseX, int mouseY)
{
    BYTE (&board)[10][9] = ((status == BLACK_MOVING) || (status == RED_MOVING)) ?
                           backupBoard: *chessGame->getBoard();

    QPainter painter(frameCanvas);
    QRect rect = frameCanvas->frameRect();

    painter.eraseRect(rect);
    painter.drawImage(0, 0, *boardImage);

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 9; j++)
        {
            if (board[i][j] == NOCHESS)
                continue;
            painter.drawImage(j*39+14,
                              i*39+15,
                              *chessMen[board[i][j] - 1]);
        }
    if ((status == BLACK_MOVING) || (status == RED_MOVING))
    {
        if (activeMan->chessId != NOCHESS)
        {
            painter.drawImage(mouseX - 18,
                              mouseY - 18,
                              *chessMen[activeMan->chessId - 1]);
        }
    }
}


void MainForm::posAtPoint( CChessMan * man, QPoint const & point )
{
    BYTE (&board)[10][9] = *chessGame->getBoard();
    man->pos.x = (point.x() - 15) / 39;
    man->pos.y = (point.y() - 14) / 39;
    man->chessId = board[man->pos.y][man->pos.x];
}


void MainForm::showStatus( QString const & str )
{
    QStatusBar* statusBar = this->statusBar();
    if (statusBar)
    {
        statusBar->showMessage(str);
    }
}


bool MainForm::isSelectRight( CChessMan * man )
{
 bool rc = false;
    if (man->chessId == NOCHESS)
        return false;

    if (IsBlack(man->chessId))
    {
        if (configForm->blackIsMan
            && ((status == BLACK_MOVING) || (status == INITIALIZING)))
            rc = true;
        else
            rc = false;
    }
    else
    {
        if (configForm->redIsMan
            && ((status == RED_MOVING) || (status == INITIALIZING)))
            rc = true;
        else
            rc = false;
    }
 return rc;
}


void MainForm::restartGame()
{
    status = INITIALIZING;
    configForm->applyChanges();
    if (chessGame->getEngine())
        chessGame->getEngine()->SetThinkProgress(qtProgress);
    memcpy(backupBoard, *chessGame->getBoard(), sizeof(backupBoard));
    //redrawBoard(0, 0);
    mouseX = 0;
    mouseY =0 ;
    repaint();
}


QProgressBar* MainForm::getProgress()
{
    return progressBar;
}


void MainForm::think()
{
    /* perform the AI */
    if (status == BLACK_THINKING)
    {
        chessGame->computerRun(false);
        status = RED_MOVING;
    }
    else if (status == RED_THINKING)
    {
        chessGame->computerRun(true);
        status = BLACK_MOVING;
    }
    else
    {
        showStatus("Do you really want the computer to run?");
    }
    memcpy(backupBoard, *chessGame->getBoard(), sizeof(backupBoard));
}

/*
 *  Constructs a MainForm as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 */
MainForm::MainForm(QWidget* parent)
    : QMainWindow(parent)
{
    setupUi(this);

    (void)statusBar();
}

/*
 *  Destroys the object and frees any allocated resources
 */
MainForm::~MainForm()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void MainForm::languageChange()
{
    retranslateUi(this);
}

