#include "AspirationSearch.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAspirationSearch::CAspirationSearch()
{

}

CAspirationSearch::~CAspirationSearch()
{

}

void CAspirationSearch::SearchAGoodMove(BYTE position[][9])
{
    int x,y;

    memcpy(CurPosition,position,90);
    
    //先进行浅层搜索，猜测目标值范围
    m_nMaxDepth=m_nSearchDepth-1;
    x=FAlphaBeta(m_nMaxDepth,-20000,20000);
    
    progress->setProgress(0);
    //对目标值附近的小窗口进行搜索
    m_nMaxDepth=m_nSearchDepth;
    y=FAlphaBeta(m_nMaxDepth,x-50,x+50);

    if(y<x-50)//fail-low research
    {
        progress->setProgress(0);
        FAlphaBeta(m_nMaxDepth,-20000,y);
    }
    if(y>x+50)//fail-high research
    {
        progress->setProgress(0);
        FAlphaBeta(m_nMaxDepth,y,20000);
    }
    
    m_umUndoMove.cmChessMove=m_cmBestMove;
    m_umUndoMove.nChessID=MakeMove(&m_cmBestMove);  
    
    memcpy(position,CurPosition,90);//将走过的棋盘传出
}
