#ifndef AFX_PVS_ENGINE_H
#define AFX_PVS_ENGINE_H

#include "SearchEngine.h"

//极小窗口搜索引擎
class CPVS_Engine:public CSearchEngine
{
public:
    CPVS_Engine();
    virtual ~CPVS_Engine();

public:
    virtual void SearchAGoodMove(BYTE position[10][9]);

protected:
    int PrincipalVariation(int depth,int alpha,int beta);
};

#endif
