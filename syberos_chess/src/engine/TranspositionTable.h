// TranspositionTable.h: interface for the CTranspositionTable class.
//
//////////////////////////////////////////////////////////////////////

#ifndef TRANSPOSITIONTABLE_H_
#define TRANSPOSITIONTABLE_H_
#include "Define.h"

enum ENTRY_TYPE{exact, lower_bound, upper_bound};

typedef struct HASHITEM{
    LONGLONG checksum;	// or long long might be even better
	ENTRY_TYPE  entry_type;
    short depth;
    short eval;
}HashItem;

class CTranspositionTable  
{
public:
	CTranspositionTable();
	virtual ~CTranspositionTable();

	void CalculateInitHashKey(BYTE CurPosition[10][9]);
	void Hash_MakeMove(CHESSMOVE* move,BYTE CurPosition[10][9]);
	void Hash_UnMakeMove(CHESSMOVE* move,BYTE nChessID,BYTE CurPosition[10][9]);

	int LookUpHashTable(int alpha, int beta, int depth,int TableNo);
	void EnterHashTable(ENTRY_TYPE entry_type, short eval, short depth,int TableNo);

	UINT m_nHashKey32[15][10][9];
	ULONGLONG m_ulHashKey64[15][10][9];
	HashItem *m_pTT[10];
	void InitializeHashKey();
	UINT m_HashKey32;
	LONGLONG m_HashKey64;
};

#endif
