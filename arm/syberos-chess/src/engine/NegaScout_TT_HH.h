// NegaScout_TT_HH.h: interface for the NegaScout_TT_HH class.
//
//////////////////////////////////////////////////////////////////////

#ifndef NEGASCOUT_TT_HH_H_
#define NEGASCOUT_TT_HH_H_

#include "SearchEngine.h"
#include "TranspositionTable.h"
#include "HistoryHeuristic.h"

class CNegaScout_TT_HH : 
	public CTranspositionTable, 
	public CHistoryHeuristic, 
	public CSearchEngine  
{
public:
	CNegaScout_TT_HH();
	virtual ~CNegaScout_TT_HH();

    virtual void SearchAGoodMove(BYTE position[10][9]);

protected:
	int NegaScout(int depth, int alpha, int beta);
};

#endif
