#ifndef AFX_FALPHABETAENGINE_H
#define AFX_FALPHABETAENGINE_H

#include "SearchEngine.h"

//fail-softalpha-beta搜索引擎
class CFAlphaBetaEngine:public CSearchEngine
{
public:
    CFAlphaBetaEngine();
    virtual ~CFAlphaBetaEngine();

public:
    virtual void SearchAGoodMove(BYTE position[10][9]);

protected:
    int FAlphaBeta(int depth,int alpha,int beta);//fail-softalpha-beta搜索函数，供接口函数调用
};

#endif
