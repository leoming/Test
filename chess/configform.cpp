#include "configform.h"

#include <qvariant.h>
#include <qimage.h>
#include <qpixmap.h>

#include <QtWidgets/QApplication>
#include "chessgame.h"
#include <QtWidgets/QMessageBox>

void ConfigForm::initializeAll( CChessGame * game )
{
    QString str;
    const char** engines = NULL;

    chessGame = game;
    redIsMan = true;
    blackIsMan = true;
    blackOnTop = true;
    /* Initialize the combobox for search engines */
    engines = game->getEngineList();

    for (int i = 0; engines[i] != NULL; i++)
    {
        str = engines[i];
        comboEngine->addItem(str);
    }
    computerEngine = game->getBestEngine();
    computerLevel = 3;
    updateUI(true);
}


void ConfigForm::buttonOK_clicked()
{
    updateUI(false);
    applyChanges();
    hide();
}


void ConfigForm::buttonCancel_clicked()
{
    /* restore previous settings */
    updateUI(true);
    hide();
}


void ConfigForm::updateUI( bool refreshUI )
{
    if (refreshUI)
    {
        comboRedPlayer->setCurrentIndex(redIsMan ? 0: 1);
        comboBlackPlayer->setCurrentIndex(blackIsMan ? 0 : 1);
        comboWhoIsOnTop->setCurrentIndex(blackOnTop ? 1 : 0);
        comboEngine->setCurrentIndex(computerEngine);
        comboComputerLevel->setCurrentIndex(computerLevel - 1);
    }
    else
    {
        redIsMan = (comboRedPlayer->currentIndex() == 0);
        blackIsMan = (comboBlackPlayer->currentIndex() == 0);
        blackOnTop = (comboWhoIsOnTop->currentIndex() == 1);
        computerEngine = comboEngine->currentIndex();
        computerLevel = comboComputerLevel->currentIndex() + 1;
    }
}


void ConfigForm::applyChanges()
{
    if (!redIsMan || !blackIsMan)
    {
        chessGame->setEngine(chessGame->createEngine(computerEngine));
        chessGame->getEngine()->SetSearchDepth(computerLevel);
    }
    chessGame->initChessBoard();
    if (!blackOnTop)
        chessGame->invertBoard();
}


void ConfigForm::comboRedPlayer_activated( int )
{
    if (comboRedPlayer->currentIndex())
    {
        if (comboBlackPlayer->currentIndex())
        {
            QMessageBox::critical(this, tr("NO"),
                                  tr("Only one player can be computer"));
            comboRedPlayer->setCurrentIndex(0);
        }
        else
        {
            comboWhoIsOnTop->setCurrentIndex(0);
            comboWhoIsOnTop->setEnabled(false);
        }
    }
    else
        comboWhoIsOnTop->setEnabled(true);
}


void ConfigForm::comboBlackPlayer_activated( int )
{
    if (comboBlackPlayer->currentIndex())
    {
        if (comboRedPlayer->currentIndex())
        {
            QMessageBox::critical(this, tr("NO"),
                                  tr("Only one player can be computer"));
            comboBlackPlayer->setCurrentIndex(0);
        }
        else
        {
            comboWhoIsOnTop->setCurrentIndex(1);
            comboWhoIsOnTop->setEnabled(false);
        }
    }
    else
        comboWhoIsOnTop->setEnabled(true);
}

/*
 *  Constructs a ConfigForm as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
ConfigForm::ConfigForm(QWidget* parent, Qt::WindowFlags fl)
    : QDialog(parent, fl)
{
    setupUi(this);

}

/*
 *  Destroys the object and frees any allocated resources
 */
ConfigForm::~ConfigForm()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void ConfigForm::languageChange()
{
    retranslateUi(this);
}

