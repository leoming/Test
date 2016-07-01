#ifndef CHESS_GAME_WRAPPER_H_
#define CHESS_GAME_WRAPPER_H_

#include "Define.h"
#include "Eveluation.h"
#include "HistoryHeuristic.h"
#include "MoveGenerator.h"
#include "NegaScout_TT_HH.h"
#include "SearchEngine.h"
#include "TranspositionTable.h"
#include <QStack>
#include <QObject>

#define BLACK_WIN 1
#define RED_WIN 2

class CMoveStack
{
public:
	CMoveStack();
	~CMoveStack();
	void push(UNDOMOVE const& move);
	UNDOMOVE pop();
	void clear();
	bool isEmpty();
private:
    QStack<UNDOMOVE> stack;
};

typedef BYTE BoardType[10][9];

typedef struct _movechess
{
    BYTE nChessID;
    POINT ptMovePoint;
}MOVECHESS;

class CChessGame : public QObject
{
    Q_OBJECT
public:
	CChessGame();
	virtual ~CChessGame();
	BoardType* getBoard() { return &board; }
public slots:
    void computerRun();
    bool moveChess(int fromX, int fromY, int toX, int toY);
    //bool redo(); /* redo a change, return true if changed */
    //bool undo(); /* undo a change, return true if changed */
    int isGameOver();
    int getChessAt(int x, int y);
    int getComputerMoveFromX();
    int getComputerMoveFromY();
    int getComputerMoveToX();
    int getComputerMoveToY();
    void reStart();
    void setMoveChess(BYTE x, BYTE y, BYTE value);
    bool checkIsChecked(int type);
private:
    void initChessBoard();
    void caculateComputerMove();

private:
	BYTE board[10][9];
    BYTE bakBoard[10][9];
    CSearchEngine* engine;
    //CMoveStack undoStack;
	CMoveGenerator* moveGenerator;
	CEveluation* evaluator;
    CHESSMANPOS from;
    CHESSMANPOS to;
    MOVECHESS m_moveChess;
};

#endif
