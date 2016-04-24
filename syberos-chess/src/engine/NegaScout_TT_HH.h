#ifndef AFX_NEGASCOUT_TT_HH_H
#define AFX_NEGASCOUT_TT_HH_H

#include "SearchEngine.h"
#include "TranspositionTable.h"
#include "HistoryHeuristic.h"

//使用了置换表和历史启发的NegaScout搜索引擎
class CNegaScout_TT_HH:public CTranspositionTable,public CHistoryHeuristic,public CSearchEngine 
{
public:
    CNegaScout_TT_HH();
    virtual ~CNegaScout_TT_HH();

public:
    virtual  void SearchAGoodMove(BYTE position[10][9]);

protected:
    int NegaScout(int depth, int alpha, int beta);//NegaScout搜索函数
};

#endif
