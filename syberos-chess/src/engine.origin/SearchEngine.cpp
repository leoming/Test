// SearchEngine.cpp: implementation of the CSearchEngine class.
//
//////////////////////////////////////////////////////////////////////

#include "SearchEngine.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CSearchEngine::CSearchEngine()
{
}

CSearchEngine::~CSearchEngine()
{
	delete m_pMG;
	delete m_pEval;
}

BYTE CSearchEngine::MakeMove(CHESSMOVE* move)
{
	BYTE nChessID;
	nChessID = CurPosition[move->To.y][move->To.x];
	CurPosition[move->To.y][move->To.x] = CurPosition[move->From.y][move->From.x];
	CurPosition[move->From.y][move->From.x] = NOCHESS;
	return nChessID;
}

void CSearchEngine::UnMakeMove(CHESSMOVE* move,BYTE nChessID)
{
	CurPosition[move->From.y][move->From.x] = CurPosition[move->To.y][move->To.x];
	CurPosition[move->To.y][move->To.x] = nChessID;
}


int CSearchEngine::IsGameOver(BYTE position[10][9], int nDepth)
{
	int i,j;
	BOOL RedLive = FALSE, BlackLive=FALSE; 
	
	for (i = 7; i < 10; i++)
		for (j = 3; j < 6; j++)
		{
			if (position[i][j] == B_KING)
				BlackLive = TRUE;
			if (position[i][j] == R_KING)
				RedLive  = TRUE;
		}

	for (i = 0; i < 3; i++)
		for (j = 3; j < 6; j++)
		{
			if (position[i][j] == B_KING)
				BlackLive = TRUE;
			if (position[i][j] == R_KING)
				RedLive  = TRUE;
		}

	i = (m_nMaxDepth - nDepth + 1) % 2;
	
	if (!RedLive)
		if (i)
			return 19990 + nDepth;
		else
			return -19990 - nDepth;
	if (!BlackLive)
		if (i)
			return -19990 - nDepth;
		else
			return 19990 + nDepth;
	return 0;
}
