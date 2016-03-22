#include "MTD_fEngine.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMTD_fEngine::CMTD_fEngine()
{

}

CMTD_fEngine::~CMTD_fEngine()
{

}

void CMTD_fEngine::SearchAGoodMove(BYTE position[][9])
{
    int firstguess=0;

    memcpy(CurPosition,position,90);
    m_nMaxDepth=m_nSearchDepth;
    CalculateInitHashKey(CurPosition);//计算初始棋盘的哈希值

    //迭代深化调用 MTD(f)搜索
    for(m_nMaxDepth=1;m_nMaxDepth<=m_nSearchDepth;m_nMaxDepth++)
        firstguess=Mtdf(firstguess,m_nMaxDepth);
    MakeMove(&m_cmBackupBM);
    memcpy(position,CurPosition,90);
}

int CMTD_fEngine::Mtdf(int firstguess, int nDepth)
{
    int g,lowerbound,upperbound,beta;
    
    g=firstguess;
    //初始搜索范围-20000 - 20000
    upperbound=20000;
    lowerbound=-20000;
    while(lowerbound<upperbound)
    {
        m_cmBackupBM=m_cmBestMove;
        //将窗口向目标移动
        if(g==lowerbound)
            beta=g+1;
        else 
            beta=g;
        g=FAlphaBeta(nDepth,beta-1,beta);//空窗探测
        if(g<beta)
            upperbound=g;
        else
            lowerbound=g;
    }

    return g;
}

int CMTD_fEngine::FAlphaBeta(int nDepth, int alpha, int beta)
{
    int current=-19999 ;
    int score;
    int Count,i;
    BYTE type;

    i=IsGameOver(CurPosition, nDepth);
    if(i!=0)
        return i;

    score=LookUpHashTable(alpha,beta,nDepth,(m_nMaxDepth-nDepth)%2);//察看哈希表中有无当前节点的有效数据
    if(score!=66666)
        return score;//命中，直接返回置换表中数据

    if(nDepth<=0)//叶子节点取估值
    {
        current=m_pEval->Eveluate(CurPosition,(m_nMaxDepth-nDepth)%2,m_nUserChessColor);
        EnterHashTable(exact,current,nDepth,(m_nMaxDepth-nDepth)%2);//将估值放入置换表
        return current;
    }

    Count=m_pMG->CreatePossibleMove(CurPosition,nDepth,(m_nMaxDepth-nDepth)%2,m_nUserChessColor);
    if(nDepth==m_nMaxDepth)
    {
        progress->setTotalSteps(Count);
        progress->setProgress(1);
    }

    int eval_is_exact=0;//数据类型标志设为 0

    for (i=0;i<Count;i++) 
    {
        if(nDepth==m_nMaxDepth)
            progress->nextStep();

        Hash_MakeMove(&m_pMG->m_MoveList[nDepth][i],CurPosition);//产生子节点的哈希值
        type=MakeMove(&m_pMG->m_MoveList[nDepth][i]);           //产生子节点

        score=-FAlphaBeta(nDepth-1,-beta,-alpha);//递归搜索子节点
        
        Hash_UnMakeMove(&m_pMG->m_MoveList[nDepth][i],type, CurPosition); 
        UnMakeMove(&m_pMG->m_MoveList[nDepth][i],type); 

                
        if(score>current)
        {
            current=score;
            if(nDepth == m_nMaxDepth)
                m_cmBestMove = m_pMG->m_MoveList[nDepth][i];
            if(score>=beta)//beta剪枝
            {
                EnterHashTable(lower_bound, score, nDepth,(m_nMaxDepth-nDepth)%2);//将下边界装入置换表
                return current;
            }
            if(score>alpha)
            {
                eval_is_exact=1;//设定确切值标志
                alpha=score;//保留最大值
            }
        }
    }

    //将搜索结果放入置换表
    if(eval_is_exact) 
        EnterHashTable(exact,alpha,nDepth,(m_nMaxDepth-nDepth)%2);
    else 
        EnterHashTable(upper_bound,current,nDepth,(m_nMaxDepth-nDepth)%2);

    return current;//返回极大值 /边界
}
