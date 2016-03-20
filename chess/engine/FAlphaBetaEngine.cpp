#include "FAlphaBetaEngine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFAlphaBetaEngine::CFAlphaBetaEngine()
{

}

CFAlphaBetaEngine::~CFAlphaBetaEngine()
{

}

void CFAlphaBetaEngine::SearchAGoodMove(BYTE position[][9])
{
    memcpy(CurPosition,position,90);     //复制传入的棋盘

    m_nMaxDepth=m_nSearchDepth;          //设定搜索深度
    FAlphaBeta(m_nMaxDepth,-20000,20000);//调用fail-softalpha-beta
    m_umUndoMove.cmChessMove=m_cmBestMove;
    m_umUndoMove.nChessID=MakeMove(&m_cmBestMove);  

    memcpy(position,CurPosition,90);     //将走过的棋盘传出
}

int CFAlphaBetaEngine::FAlphaBeta(int nDepth,int alpha,int beta)
{
    int current=-20000;//current初始为极小值
    int score;
    int Count,i;
    BYTE type;
    
    i=IsGameOver(CurPosition,nDepth);//检查此节点游戏是否结束
    if(i!=0)
        return i;//此节点游戏结束，返回极大/极小值

    //如果是叶子节点取估值
    if(nDepth<=0)
        return m_pEval->Eveluate(CurPosition,(m_nMaxDepth-nDepth)%2,m_nUserChessColor);
    
    Count=m_pMG->CreatePossibleMove(CurPosition,nDepth,(m_nMaxDepth-nDepth)%2,m_nUserChessColor);
    if(nDepth==m_nMaxDepth)
    {
        progress->setTotalSteps(Count);
        progress->setProgress(1);
    }

    for(i=0;i<Count;i++)
    {
        if(nDepth==m_nMaxDepth)
            progress->nextStep();

        type=MakeMove(&m_pMG->m_MoveList[nDepth][i]);
        score=-FAlphaBeta(nDepth-1,-beta,-alpha);
        UnMakeMove(&m_pMG->m_MoveList[nDepth][i],type);

        if(score>current)
        {
            current=score;//保留最大值

            //当靠近根节点时记录最佳走法
            if(nDepth==m_nMaxDepth)
                m_cmBestMove=m_pMG->m_MoveList[nDepth][i];

            if(score>=alpha)
                alpha=score;//修改alpha边界

            if(score>=beta)
                break;//beta剪枝
        }
    }

    return current;//返回极大值或边界值
}
