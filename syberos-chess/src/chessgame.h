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

class CChessGame : public QObject
{
    Q_OBJECT
public:
	CChessGame();
	virtual ~CChessGame();
	BoardType* getBoard() { return &board; }
public slots:
    void computerRun(bool forRed = false);
    bool moveChess(int fromX, int fromY, int toX, int toY, bool blackOnTop = true);
	bool redo(); /* redo a change, return true if changed */
	bool undo(); /* undo a change, return true if changed */
    int isGameOver();
    int getChessAt(int x, int y);
private:
    void initChessBoard();
    void invertBoard();

private:
	BYTE board[10][9];
	CSearchEngine* engine;
	CMoveStack undoStack;
	CMoveStack redoStack;
	CMoveGenerator* moveGenerator;
	CEveluation* evaluator;
    //CHESSMOVE computerMove;
	void validateEngine();
};

#endif
