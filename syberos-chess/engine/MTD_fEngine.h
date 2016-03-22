#ifndef AFX_MTD_F_H
#define AFX_MTD_F_H

#include "SearchEngine.h"
#include "TranspositionTable.h"
#include "HistoryHeuristic.h"

//MTD(f)搜索引擎
class CMTD_fEngine:public CSearchEngine,public CHistoryHeuristic,public CTranspositionTable  
{
public:
    CMTD_fEngine();
    virtual ~CMTD_fEngine();

public:
    virtual void SearchAGoodMove(BYTE position[10][9]);

protected:
    int FAlphaBeta(int nDepth,int alpha,int beta);//带有置换表的fail-softalpha-beta搜索函数
    int Mtdf(int firstguess,int nDepth);          //MTD(f)搜索函数

protected:
    CHESSMOVE m_cmBackupBM;//用以保存最佳走法的变量
};

#endif
