#include "NegaScout_TT_HH.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNegaScout_TT_HH::CNegaScout_TT_HH()
{

}

CNegaScout_TT_HH::~CNegaScout_TT_HH()
{

}

void CNegaScout_TT_HH::SearchAGoodMove(BYTE position[][9])
{
    memcpy(CurPosition,position,90);

    m_nMaxDepth=m_nSearchDepth;
    CalculateInitHashKey(CurPosition);
    ResetHistoryTable();
    NegaScout(m_nMaxDepth,-20000,20000);
    m_umUndoMove.cmChessMove=m_cmBestMove;
    m_umUndoMove.nChessID=MakeMove(&m_cmBestMove);  

    memcpy(position,CurPosition,90);
}

#include <QDebug>

int CNegaScout_TT_HH::NegaScout(int depth, int alpha, int beta)
{
    int Count,i;
    BYTE type;
    int a,b,t;
    int side;
    int score;
    //qDebug() << "chess: " << __FILE__ << __LINE__;
    
    i=IsGameOver(CurPosition, depth);
    if(i!=0)
        return i;
    
    side=(m_nMaxDepth-depth)%2;//计算当前节点的类型，极大 0/极小 1
    
    score=LookUpHashTable(alpha,beta,depth,side); 
    if(score!=66666) 
        return score;
    
    if(depth<=0)//叶子节点取估值
    {
        score=m_pEval->Eveluate(CurPosition,side,m_nUserChessColor);
        EnterHashTable(exact,score,depth,side);//将估值存入置换表
        return score;
    }
    
    //printBoard();
    Count=m_pMG->CreatePossibleMove(CurPosition,depth,side,m_nUserChessColor);
    
    for(i=0;i<Count;i++) 
        m_pMG->m_MoveList[depth][i].Score=GetHistoryScore(&m_pMG->m_MoveList[depth][i]);
    MergeSort(m_pMG->m_MoveList[depth],Count,0);
    
    int bestmove=-1;
    
    a=alpha;
    b=beta;

    int eval_is_exact=0;

    for(i=0;i<Count;i++) 
    {
        Hash_MakeMove(&m_pMG->m_MoveList[depth][i],CurPosition);
        type=MakeMove(&m_pMG->m_MoveList[depth][i]);
        
        t=-NegaScout(depth-1,-b,-a);
        
        if(t>a && t<beta && i>0) 
        {
            //对于第一个后的节点，如果上面的搜索 failhigh
            a=-NegaScout(depth-1,-beta,-t);     /* re-search */
            eval_is_exact=1;//设数据类型为精确值
            if(depth==m_nMaxDepth)
                m_cmBestMove=m_pMG->m_MoveList[depth][i];
            bestmove=i;
        }
        Hash_UnMakeMove(&m_pMG->m_MoveList[depth][i],type,CurPosition); 
        UnMakeMove(&m_pMG->m_MoveList[depth][i],type); 
        if(a<t)
        {
            eval_is_exact=1;
            a=t;
            if(depth==m_nMaxDepth)
                m_cmBestMove=m_pMG->m_MoveList[depth][i];
        }
        if(a>= beta) 
        {
            EnterHashTable(lower_bound,a,depth,side);
            EnterHistoryScore(&m_pMG->m_MoveList[depth][i],depth);
            return a;
        }
        b=a+1;                      /* set new null window */
    }
    //printBoard();
    if(bestmove!=-1)
        EnterHistoryScore(&m_pMG->m_MoveList[depth][bestmove], depth);
    if (eval_is_exact) 
        EnterHashTable(exact,a,depth,side);
    else 
        EnterHashTable(upper_bound,a,depth,side);

    //printBoard();
    return a;
}

void CNegaScout_TT_HH::printBoard()
{
    for (int i = 0; i < 10; ++i) {
        qDebug() << CurPosition[i][0] << CurPosition[i][1] << CurPosition[i][2] << CurPosition[i][3] << CurPosition[i][4] << CurPosition[i][5] << CurPosition[i][6] << CurPosition[i][7] << CurPosition[i][8];
    }
    qDebug() << "=====================";
}
