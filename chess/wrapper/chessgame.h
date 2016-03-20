#ifndef CHESS_GAME_WRAPPER_H_
#define CHESS_GAME_WRAPPER_H_

#include "AlphaBetaEngine.h"
#include "Alphabeta_HH.h"
#include "AlphaBeta_TTEngine.h"
#include "AspirationSearch.h"
#include "Define.h"
#include "Eveluation.h"
#include "FAlphaBetaEngine.h"
#include "HistoryHeuristic.h"
#include "IDAlphabetaEngine.h"
#include "MoveGenerator.h"
#include "MTD_fEngine.h"
#include "NegaMaxEngine.h"
#include "NegaScout_TT_HH.h"
#include "PVS_Engine.h"
#include "SearchEngine.h"
#include "TranspositionTable.h"
#include <QStack>

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

class CChessGame
{
public:
	enum GameOverState{BLACK_WIN, RED_WIN, DRAW};
	CChessGame();
	virtual ~CChessGame();
	const char ** getEngineList() const;
	int getBestEngine() { return 7; }
	CSearchEngine* createEngine(int numEngine);
	void setEngine(CSearchEngine* anEngine);
	CSearchEngine* getEngine() { return engine; }
	BoardType* getBoard() { return &board; }
	void initChessBoard();
	void invertBoard();
	CHESSMOVE* computerRun(bool forRed);
	bool moveChess(const CHESSMANPOS& from, const CHESSMANPOS& to, bool blackOnTop);
	bool redo(); /* redo a change, return true if changed */
	bool undo(); /* undo a change, return true if changed */
	GameOverState isGameOver();
private:
	BYTE board[10][9];
	CSearchEngine* engine;
	CMoveStack undoStack;
	CMoveStack redoStack;
	CMoveGenerator* moveGenerator;
	CEveluation* evaluator;
	CHESSMOVE computerMove;
	void validateEngine();
};

#endif
