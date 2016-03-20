#include "chessgame.h"

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
    engine = NULL;
	evaluator = new CEveluation();
	moveGenerator = new CMoveGenerator();
    initChessBoard();
}

CChessGame::~CChessGame()
{
    if (engine)
        delete engine;
}

const char** CChessGame::getEngineList() const
{
    static const char* engines[] = {
        "Alpha-beta search",
        "Alpha-beta search with history heuristic",
        "Alpha-beta search with translation table",
        "Aspiration search",
        "Fail-soft alpha-beta search",
        "ID alpha-beta search engine",
        "MTD(f) search engine",
        "NegaScout-TT-HH search engine", // the coolest engine
        "PVS search engine",
        NULL,
    };
    return engines;
}

CSearchEngine* CChessGame::createEngine(int numEngine)
{
	static bool called = false;
	static CSearchEngine* engineTable[8];
	if (!called)
	{
		called = 1;
		engineTable[0] = new CAlphaBetaEngine();
		engineTable[1] = new CAlphabeta_HHEngine();
		engineTable[2] = new CAlphaBeta_TTEngine();
		engineTable[3] = new CAspirationSearch();
		engineTable[4] = new CFAlphaBetaEngine();
		engineTable[5] = new CIDAlphabetaEngine();
		engineTable[6] = new CMTD_fEngine();
		engineTable[7] = new CNegaScout_TT_HH();
		engineTable[8] = new CPVS_Engine();
	}
	if (numEngine >= 0 && numEngine <= 8)
		return engineTable[numEngine];
	return NULL;
}

void CChessGame::setEngine(CSearchEngine* anEngine)
{
    if (anEngine)
    {
        engine = anEngine;
		engine->SetMoveGenerator(moveGenerator);
		engine->SetEveluator(evaluator);
    }
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

bool CChessGame::moveChess(const CHESSMANPOS& from, const CHESSMANPOS& to,
		bool blackOnTop)
{
	if (moveGenerator->IsValidMove(board, from.x, from.y, to.x, to.y, 
				blackOnTop?REDCHESS:BLACKCHESS))
	{
		UNDOMOVE undoMove;

		redoStack.clear();
		undoMove.cmChessMove.From = from;
		undoMove.cmChessMove.To = to;
		undoMove.cmChessMove.nChessID = board[from.y][from.x];
		undoMove.nChessID = board[to.y][to.x];
		validateEngine();
		engine->RedoChessMove(board, &undoMove.cmChessMove);
		undoStack.push(undoMove);
		return true;
	}

	return false;
}

CHESSMOVE* CChessGame::computerRun(bool forRed)
{
	UNDOMOVE undoMove;
	if (!engine)
		return NULL;
	redoStack.clear();
	engine->SetUserChessColor(forRed?BLACKCHESS:REDCHESS);
	engine->SearchAGoodMove(board);
	computerMove = engine->GetBestMove();
	undoMove = engine->GetUndoMove();
	undoStack.push(undoMove);
	return &computerMove;
}

void CChessGame::validateEngine()
{
	if (!engine)
		createEngine(getBestEngine());
}

bool CChessGame::redo()
{
	int i = 0;
	UNDOMOVE undoMove;

	validateEngine();
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

	validateEngine();
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

CChessGame::GameOverState CChessGame::isGameOver()
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
	return DRAW;
}

