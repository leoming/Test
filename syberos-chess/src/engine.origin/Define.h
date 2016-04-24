//define.h // data structure and macros
#ifndef define_h_
#define define_h_

#define NOCHESS 0    //没有棋子

#define B_KING       1  //黑帅
#define B_CAR        2  //黑车
#define B_HORSE      3  //黑马
#define B_CANON      4  //黑炮
#define B_BISHOP     5  //黑士
#define B_ELEPHANT   6  //黑象
#define B_PAWN       7  //黑卒
#define B_BEGIN      B_KING
#define B_END        B_PAWN

#define R_KING       8   //红帅
#define R_CAR        9   //红车
#define R_HORSE      10  //红马
#define R_CANON      11  //红炮
#define R_BISHOP     12  //红士
#define R_ELEPHANT   13  //红象
#define R_PAWN       14  //红兵
#define R_BEGIN      R_KING
#define R_END        R_PAWN

#define IsBlack(x)  (x>=B_BEGIN&&x<=B_END)
#define IsRed(x)  (x>=R_BEGIN&&x<=R_END)
#define IsSameSide(x,y)  ((IsBlack(x)&&IsBlack(y))||(IsRed(x)&&IsRed(y)))

typedef unsigned char BYTE;
typedef bool BOOL;
typedef long long LONGLONG;
typedef long LONG;
typedef unsigned int UINT;
typedef unsigned long long ULONGLONG;
#define TRUE true
#define FALSE false

typedef struct
{
	BYTE		x;
	BYTE		y;
}CHESSMANPOS, POINT;

typedef struct
{
	short	  	    ChessID;	//
	CHESSMANPOS	From;
	CHESSMANPOS	To;			//
	int			    Score;		// 
}CHESSMOVE;

//悔棋时需要的数据结构
typedef struct
{
    CHESSMOVE cmChessMove;
    short nChessID;//被吃掉的棋子
} UNDOMOVE;
#endif //define_h_
