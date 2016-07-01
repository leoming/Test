#include "chessgame.h"
#include "NegaMaxEngine.h"
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
    engine->SetSearchDepth(3);
    //engine2->SetMoveGenerator(moveGenerator);
    //engine2->SetEveluator(evaluator);
    //engine2->SetSearchDepth(5);
    initChessBoard();
}

CChessGame::~CChessGame()
{
    if (engine)
        delete engine;
    //if (engine2)
    //    delete engine2;
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
    //redoStack.clear();
    //undoStack.clear();
}

void CChessGame::caculateComputerMove()
{
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 9; j++)
        {
            //qDebug() << "bakeBoard[" << i << "][" << j << "]" << bakBoard[i][j];
            //qDebug() << "board[" << i << "][" << j << "]" << board[i][j];
            if (bakBoard[i][j] == board[i][j]) {
                continue;
            }
            else if (board[i][j] == NOCHESS) {
                from.x = j; from.y = i;
            }
            else {
                to.x = j; to.y = i;
            }
        }
}

bool CChessGame::moveChess(int fromX, int fromY, int toX, int toY)
{
    if (moveGenerator->IsValidMove(board, fromX, fromY, toX, toY))
    {
        board[toY][toX] = board[fromY][fromX];
        board[fromY][fromX] = NOCHESS;
		return true;
    }

	return false;
}

void CChessGame::computerRun()
{
    //redoStack.clear();
    memcpy(bakBoard,board,90);
    //engine->SetUserChessColor(forRed?BLACKCHESS:REDCHESS);
    engine->SearchAGoodMove(board);
    //computerMove = engine->GetBestMove();
    //undoStack.push(engine->GetUndoMove());
    caculateComputerMove();

    //return &computerMove;
}
/*
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
        //engine->UndoChessMove(board, &undoMove.cmChessMove, undoMove.nChessID);
	}
	if (undoStack.isEmpty())
		return false;
	return true;
}
*/

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

int CChessGame::getComputerMoveFromX()
{
    return from.x;
}

int CChessGame::getComputerMoveFromY()
{
    return from.y;
}

int CChessGame::getComputerMoveToX()
{
    return to.x;
}

int CChessGame::getComputerMoveToY()
{
    return to.y;
}

void CChessGame::reStart()
{
    initChessBoard();
}

void CChessGame::setMoveChess(BYTE x, BYTE y, BYTE value)
{
    m_moveChess.nChessID = value;
    m_moveChess.ptMovePoint.x = x;
    m_moveChess.ptMovePoint.y = y;
}
// 0 user 1 computer
bool CChessGame::checkIsChecked(int type)
{
    CHESSMANPOS target;
    target.x = 100;
    target.y = 100;
    if (type == 0) {
        for (int y = 0; y < 3; y++)
            for (int x = 3; x < 6; x++)
            {
                if (board[y][x] == B_KING) {
                    target.x = x;
                    target.y = y;
                    break;
                }
            }

        for (int y = 0; y < 10; y++)
            for (int x = 0; x < 9; x++)
            {
                if (board[y][x] == R_PAWN ||
                        board[y][x] == R_CANON ||
                        board[y][x] == R_CAR ||
                        board[y][x] == R_HORSE) {
                    if (moveGenerator->IsValidMove(board, x, y, target.x, target.y)) {
                        return true;
                    }
                }
            }
        return false;
    } else if (type == 1) {
        for (int y = 7; y < 10; y++)
            for (int x = 3; x < 6; x++)
            {
                if (board[y][x] == R_KING) {
                    target.x = x;
                    target.y = y;
                    break;
                }
            }
        for (int y = 0; y < 10; y++)
            for (int x = 0; x < 9; x++)
            {
                if (board[y][x] == B_PAWN ||
                        board[y][x] == B_CANON ||
                        board[y][x] == B_CAR ||
                        board[y][x] == B_HORSE) {
                    if (moveGenerator->IsValidMove(board, x, y, target.x, target.y)) {
                        return true;
                    }
                }
            }
        return false;
    }
    return false;
}
