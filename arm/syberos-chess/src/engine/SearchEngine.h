// SearchEngine.h: interface for the CSearchEngine class.
//
//////////////////////////////////////////////////////////////////////

#ifndef SEARCHENGINE_H_
#define SEARCHENGINE_H_

#include "MoveGenerator.h"
#include "Eveluation.h"
#include "Define.h"

class CSearchEngine  
{
public:
	CSearchEngine();
	virtual ~CSearchEngine();
	
    virtual void SearchAGoodMove(BYTE position[10][9])=0;
	
    virtual void SetSearchDepth(int nDepth){m_nSearchDepth = nDepth;}
	
    virtual void SetEveluator(CEveluation *pEval){m_pEval = pEval;}

    virtual void SetMoveGenerator(CMoveGenerator *pMG){m_pMG = pMG;}

protected:
	virtual BYTE MakeMove(CHESSMOVE* move);
	virtual void UnMakeMove(CHESSMOVE* move,BYTE type);
	virtual int IsGameOver(BYTE position[10][9], int nDepth);
	BYTE CurPosition[10][9];
	CHESSMOVE m_cmBestMove;
	CMoveGenerator *m_pMG;
	CEveluation *m_pEval;
	int m_nSearchDepth;
	int m_nMaxDepth;
};

#endif // !defined(AFX_SEARCHENGINE_H__2AF7A220_CB28_11D5_AEC7_5254AB2E22C7__INCLUDED_)
