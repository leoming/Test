#ifndef AFX_ASPIRATIONSEARCH_H
#define AFX_ASPIRATIONSEARCH_H

#include "FAlphaBetaEngine.h"

//渴望搜索引擎
class CAspirationSearch:public CFAlphaBetaEngine
{
public:
    CAspirationSearch();
    virtual ~CAspirationSearch();

public:
    virtual void SearchAGoodMove(BYTE position[10][9]);
};

#endif
