// HistoryHeuristic.h: interface for the CHistoryHeuristic class.
//
//////////////////////////////////////////////////////////////////////

#ifndef HISTORYHEURISTIC_H_
#define HISTORYHEURISTIC_H_
#include "Define.h"

class CHistoryHeuristic  
{
public:
	CHistoryHeuristic();
	virtual ~CHistoryHeuristic();
	
	void ResetHistoryTable();
	int GetHistoryScore(CHESSMOVE *move);
	void EnterHistoryScore(CHESSMOVE *move,int depth);
	void MergeSort(CHESSMOVE *source, int n, BOOL direction);
protected:
	void Merge(CHESSMOVE *source, CHESSMOVE *target, int l,int m, int r);
	void MergePass(CHESSMOVE *source, CHESSMOVE *target, const  int s, const  int n, const BOOL direction);
	void Merge_A(CHESSMOVE *source, CHESSMOVE *target, int l,int m, int r);
	int m_HistoryTable[90][90];
	CHESSMOVE m_TargetBuff[100]; 

};

#endif
