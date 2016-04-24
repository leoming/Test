#include "chessgame.h"
#include <QDebug>

CMoveStack::CMoveStack()
	:stack()
{
}

CMoveStack::~CMoveStack()
{
	clear();
}

void CMoveStack::push(UNDOMOVE const &anMove)
{
	stack.push(anMove);
}

UNDOMOVE CMoveStack::pop()
{
	return stack.pop();
}

void CMoveStack::clear()
{
	stack.clear();
}

bool CMoveStack::isEmpty()
{
	return stack.isEmpty();
}

CChessGame::CChessGame()
{
    engine = new CNegaScout_TT_HH();
    evaluator = new CEveluation();
	moveGenerator = new CMoveGenerator();
    engine->SetMoveGenerator(moveGenerator);
    engine->SetEveluator(evaluator);
    engine->SetSearchDepth(4);
    initChessBoard();
}

CChessGame::~CChessGame()
{
    if (engine)
        delete engine;
}

void CChessGame::initChessBoard()
{
    const BYTE initBoard[10][9] = {
    {B_CAR,B_HORSE,B_ELEPHANT,B_BISHOP,B_KING,B_BISHOP,B_ELEPHANT,B_HORSE,B_CAR},
    {NOCHESS,NOCHESS,NOCHESS,NOCHESS,NOCHESS,NOCHESS,NOCHESS,NOCHESS,NOCHESS},
    {NOCHESS,B_CANON,NOCHESS,NOCHESS,NOCHESS,NOCHESS,NOCHESS,B_CANON,NOCHESS},
    {B_PAWN,NOCHESS,B_PAWN,NOCHESS,B_PAWN,NOCHESS,B_PAWN,NOCHESS,B_PAWN},
    {NOCHESS,NOCHESS,NOCHESS,NOCHESS,NOCHESS,NOCHESS,NOCHESS,NOCHESS,NOCHESS},
            //楚河                       汉界//
    {NOCHESS,NOCHESS,NOCHESS,NOCHESS,NOCHESS,NOCHESS,NOCHESS,NOCHESS,NOCHESS},
    {R_PAWN,NOCHESS,R_PAWN,NOCHESS,R_PAWN,NOCHESS,R_PAWN,NOCHESS,R_PAWN},
    {NOCHESS,R_CANON,NOCHESS,NOCHESS,NOCHESS,NOCHESS,NOCHESS,R_CANON,NOCHESS},
    {NOCHESS,NOCHESS,NOCHESS,NOCHESS,NOCHESS,NOCHESS,NOCHESS,NOCHESS,NOCHESS},
    {R_CAR,R_HORSE,R_ELEPHANT,R_BISHOP,R_KING,R_BISHOP,R_ELEPHANT,R_HORSE,R_CAR}
    };
    memcpy(board, initBoard, sizeof(board));
    redoStack.clear();
    undoStack.clear();
}

void CChessGame::invertBoard()
{
    BYTE tmp;

    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 9; j++)
        {
            tmp = board[i][j];
            board[i][j] = board[9-i][8-j];
            board[9-i][8-j] = tmp;
        }
}

bool CChessGame::moveChess(int fromX, int fromY, int toX, int toY,
		bool blackOnTop)
{
    if (moveGenerator->IsValidMove(board, fromX, fromY, toX, toY,
				blackOnTop?REDCHESS:BLACKCHESS))
	{
		UNDOMOVE undoMove;

		redoStack.clear();
        undoMove.cmChessMove.From.x = fromX;
        undoMove.cmChessMove.From.y = fromY;
        undoMove.cmChessMove.To.x = toX;
        undoMove.cmChessMove.To.y = toY;
        undoMove.cmChessMove.nChessID = board[fromY][fromX];
        undoMove.nChessID = board[toY][toX];
		engine->RedoChessMove(board, &undoMove.cmChessMove);
		undoStack.push(undoMove);
		return true;
	}

	return false;
}

void CChessGame::computerRun(bool forRed)
{
	redoStack.clear();
	engine->SetUserChessColor(forRed?BLACKCHESS:REDCHESS);
	engine->SearchAGoodMove(board);
    //computerMove = engine->GetBestMove();
    undoStack.push(engine->GetUndoMove());
    //return &computerMove;
}

bool CChessGame::redo()
{
	int i = 0;
	UNDOMOVE undoMove;

	for (i = 0; i < 2; i++)
	{
		if (redoStack.isEmpty())
			return false;
		undoMove = redoStack.pop();
		undoStack.push(undoMove);
		engine->RedoChessMove(board, &undoMove.cmChessMove);
	}
	if (redoStack.isEmpty())
		return false;
	return true;
}

bool CChessGame::undo()
{
	int i = 0;
	UNDOMOVE undoMove;

	for (i = 0; i < 2; i++)
	{
		if (undoStack.isEmpty())
			return false;
		undoMove = undoStack.pop();
		redoStack.push(undoMove);
		engine->UndoChessMove(board, &undoMove.cmChessMove, undoMove.nChessID);
	}
	if (undoStack.isEmpty())
		return false;
	return true;
}

int CChessGame::isGameOver()
{
	int i, j;
	bool blackAlive = false, redAlive = false;

	for (i = 7; i < 10; i++)
		for (j = 3; j < 6; j++)
		{
			if (board[i][j] == B_KING)
				blackAlive = true;
			if (board[i][j] == R_KING)
				redAlive = true;
		}
	for (i = 0; i < 3; i++)
		for (j = 3; j < 6; j++)
		{
			if (board[i][j] == B_KING)
				blackAlive = true;
			if (board[i][j] == R_KING)
				redAlive = true;
		}
	if (!redAlive)
		return BLACK_WIN;
	if (!blackAlive)
		return RED_WIN;
    return 0;
}

int CChessGame::getChessAt(int x, int y)
{
    if (x < 9 && y < 10)
        return (int)board[y][x];
    return NOCHESS;
}

