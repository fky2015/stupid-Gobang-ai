#if 1
//		基于点评估的估值函数
#include "ChessMap.h"

#define F2 1		// **ap**
#define FB2 8		//	*p*a**
#define FC2 9		//	*p**a*
#define S2 2
#define D2 10
#define F3 3
#define FA3 11
#define SA3 12
#define S3 4 
#define F4 5
#define WIN5 7
#define S4 6
#define SA4 13


//#define CHA_A 1
//#define CHA_B 2
#define BLANK 0

#define UP	1
#define DOWN	5
#define RIGHT		3
#define LEFT	7
#define UPRIGHT		2
#define UPLEFT	8
#define DOWNLEFT		6		
#define DOWNRIGHT	4

#define up(pos) map[x-(pos)][y]
#define down(pos) map[x+(pos)][y]
#define left(pos) map[x][y-(pos)]
#define right(pos) map[x][y+(pos)]
#define upright(pos) map[x-(pos)][y+(pos)]
#define downright(pos) map[x+(pos)][y+(pos)]
#define downleft(pos) map[x+(pos)][y-(pos)]
#define upleft(pos) map[x-(pos)][y-(pos)]
#define pass_params_definition const int (*map)[15],int x,int y
#define pass_params map, x, y

const int w_free2 = 120;
const int w_freeB2 = 120;
const int w_freeC2 = 120;
const int w_sleep2 = 30;
const int w_dead2 = 5;
const int w_free3 = 720;
const int w_freeA3 = 720;
const int w_sleep3 = 250;
const int w_sleepA3 = 250;
const int w_win4 = 4320;
const int w_win5 = 5000;
const int w_sleep4 = 300;
const int w_sleepA4 = 300;

#define SUM(x) w_ ## x*(x)
	//		初步设想
	//		传入类型 ： 二维数组，落子点
	//		函数功能：评价落子该点对我方的正收益
	//		返回值：估值
	//		注意：使用宏定义或者const定义权值，方便修改
	//		二维数组包含：
	//			a--我方棋子
	//			b--对方棋子
	//			分别用character_a ,character_b 表示

	//		另外 需要实现判断边界的功能
	//		以及 拆分成多个子问题

	//		方向	8	1  2
	//				7      3
	//				6  5  4

	// (x,y) 不包含原点的长度lenth
#define BOUNDARY 15
inline bool is_legal(int x, int y, int lenth, int direction)		//		判断边界
{
	switch (direction) {
	case UP:
		if (x >= lenth)
			return true;
		else return false;
		break;
	case DOWN:
		if (x < BOUNDARY - lenth)
			return true;
		else return false;
		break;
	case LEFT:
		if (y >= lenth)
			return true;
		else return false;
	case RIGHT:
		if (y < BOUNDARY - lenth)
			return true;
		else return false;
	case UPRIGHT:
		if (x >= lenth && y < BOUNDARY - lenth)
			return true;
		else return false;
	case DOWNRIGHT:
		if (x < (BOUNDARY - lenth) && y < (BOUNDARY - lenth))
			return true;
		else return false;
	case DOWNLEFT:
		if (x < BOUNDARY - lenth && y >= lenth)
			return true;
		else return false;
	case UPLEFT:
		if (x >= lenth && y >= lenth)
			return true;
		else return false;
	}
	cout << "参数错误";
	return false;
}
int evaluate_point_impliment(const int(*map)[15], int x, int y,bool if_judge_1) {

	int CHA_A, CHA_B;
	if (if_judge_1) {
		CHA_A = 1;
		CHA_B = 2;
	}
	else {
		CHA_A = 2;
		CHA_B = 1;
	}
	
	int summary[16] = { 0 };
	{
		//MATCH_F2(UP, DOWN,upfunc);
		//cout << summary[UP][F2] << endl;
		// **Oa**
		if (is_legal(x, y, 3, UP) && is_legal(x, y, 2, DOWN)) {
			if (up(1) == CHA_A && up(2) == BLANK && up(3) == BLANK && up(-1) == BLANK && up(-2) == BLANK)
				summary[F2]++;
		}
		if (is_legal(x, y, 3, DOWN) && is_legal(x, y, 2, UP)) {
			// **Oa**
			if (down(1) == CHA_A && down(2) == BLANK && down(3) == BLANK && down(-1) == BLANK && down(-2) == BLANK)
				summary[F2]++;
		}if (is_legal(x, y, 3, LEFT) && is_legal(x, y, 2, RIGHT)) {
			// **Oa**
			if (left(1) == CHA_A && left(2) == BLANK && left(3) == BLANK && left(-1) == BLANK && left(-2) == BLANK)
				summary[F2]++;
		}if (is_legal(x, y, 3, RIGHT) && is_legal(x, y, 2, LEFT)) {
			// **Oa**
			if (right(1) == CHA_A && right(2) == BLANK && right(3) == BLANK && right(-1) == BLANK && right(-2) == BLANK)
				summary[F2]++;

		}if (is_legal(x, y, 3, UPRIGHT) && is_legal(x, y, 2, DOWNLEFT)) {
			// **Oa**
			if (upright(1) == CHA_A && upright(2) == BLANK && upright(3) == BLANK && upright(-1) == BLANK && upright(-2) == BLANK)
				summary[F2]++;
		}if (is_legal(x, y, 3, UPLEFT) && is_legal(x, y, 2, DOWNRIGHT)) {
			// **Oa**
			if (upleft(1) == CHA_A && upleft(2) == BLANK && upleft(3) == BLANK && upleft(-1) == BLANK && upleft(-2) == BLANK)
				summary[F2]++;
		}if (is_legal(x, y, 3, DOWNLEFT) && is_legal(x, y, 2, UPRIGHT)) {
			// **Oa**
			if (downleft(1) == CHA_A && downleft(2) == BLANK && downleft(3) == BLANK && downleft(-1) == BLANK && downleft(-2) == BLANK)
				summary[F2]++;
		}if (is_legal(x, y, 3, DOWNRIGHT) && is_legal(x, y, 2, UPLEFT)) {
			// **Oa**
			if (downright(1) == CHA_A && downright(2) == BLANK && downright(3) == BLANK && downright(-1) == BLANK && downright(-2) == BLANK)
				summary[F2]++;
		}
	}
	//-------------------------------------------------------------------------------------
	{
		if (is_legal(x, y, 4, UP) && is_legal(x, y, 1, DOWN)) {
			if (up(1) == BLANK && up(2) == CHA_A && up(3) == BLANK && up(4) == BLANK && up(-1) == BLANK)
				summary[FB2]++;
		}
		if (is_legal(x, y, 4, UP) && is_legal(x, y, 1, DOWN)) {
			if (up(1) == BLANK && up(3) == CHA_A && up(2) == BLANK && up(4) == BLANK && up(-1) == BLANK)
				summary[FC2]++;
		}
		if (is_legal(x, y, 4, DOWN) && is_legal(x, y, 1, UP)) {
			if (down(1) == BLANK && down(2) == CHA_A && down(3) == BLANK && down(4) == BLANK && down(-1) == BLANK)
				summary[FB2]++;
		}
		if (is_legal(x, y, 4, DOWN) && is_legal(x, y, 1, UP)) {
			if (down(1) == BLANK && down(3) == CHA_A && down(2) == BLANK && down(4) == BLANK && down(-1) == BLANK)
				summary[FC2]++;
		}
		if (is_legal(x, y, 4, LEFT) && is_legal(x, y, 1, RIGHT)) {
			if (left(1) == BLANK && left(2) == CHA_A && left(3) == BLANK && left(4) == BLANK && left(-1) == BLANK)
				summary[FB2]++;
		}
		if (is_legal(x, y, 4, LEFT) && is_legal(x, y, 1, RIGHT)) {
			if (left(1) == BLANK && left(3) == CHA_A && left(2) == BLANK && left(4) == BLANK && left(-1) == BLANK)
				summary[FC2]++;
		}
		if (is_legal(x, y, 4, RIGHT) && is_legal(x, y, 1, LEFT)) {
			if (right(1) == BLANK && right(2) == CHA_A && right(3) == BLANK && right(4) == BLANK && right(-1) == BLANK)
				summary[FB2]++;
		}
		if (is_legal(x, y, 4, RIGHT) && is_legal(x, y, 1, LEFT)) {
			if (right(1) == BLANK && right(3) == CHA_A && right(2) == BLANK && right(4) == BLANK && right(-1) == BLANK)
				summary[FC2]++;
		}
		if (is_legal(x, y, 4, UPRIGHT) && is_legal(x, y, 1, DOWNLEFT)) {
			if (upright(1) == BLANK && upright(2) == CHA_A && upright(3) == BLANK && upright(4) == BLANK && upright(-1) == BLANK)
				summary[FB2]++;
		}
		if (is_legal(x, y, 4, UPRIGHT) && is_legal(x, y, 1, DOWNLEFT)) {
			if (upright(1) == BLANK && upright(3) == CHA_A && upright(2) == BLANK && upright(4) == BLANK && upright(-1) == BLANK)
				summary[FC2]++;
		}
		if (is_legal(x, y, 4, UPLEFT) && is_legal(x, y, 1, DOWNRIGHT)) {
			if (upleft(1) == BLANK && upleft(2) == CHA_A && upleft(3) == BLANK && upleft(4) == BLANK && upleft(-1) == BLANK)
				summary[FB2]++;
		}
		if (is_legal(x, y, 4, UPLEFT) && is_legal(x, y, 1, DOWNRIGHT)) {
			if (upleft(1) == BLANK && upleft(3) == CHA_A && upleft(2) == BLANK && upleft(4) == BLANK && upleft(-1) == BLANK)
				summary[FC2]++;
		}
		if (is_legal(x, y, 4, DOWNRIGHT) && is_legal(x, y, 1, UPLEFT)) {
			if (downright(1) == BLANK && downright(2) == CHA_A && downright(3) == BLANK && downright(4) == BLANK && downright(-1) == BLANK)
				summary[FB2]++;
		}
		if (is_legal(x, y, 4, DOWNRIGHT) && is_legal(x, y, 1, UPLEFT)) {
			if (downright(1) == BLANK && downright(3) == CHA_A && downright(2) == BLANK && downright(4) == BLANK && downright(-1) == BLANK)
				summary[FC2]++;
		}
		if (is_legal(x, y, 4, DOWNLEFT) && is_legal(x, y, 1, UPRIGHT)) {
			if (downleft(1) == BLANK && downleft(2) == CHA_A && downleft(3) == BLANK && downleft(4) == BLANK && downleft(-1) == BLANK)
				summary[FB2]++;
		}
		if (is_legal(x, y, 4, DOWNLEFT) && is_legal(x, y, 1, UPRIGHT)) {
			if (downleft(1) == BLANK && downleft(3) == CHA_A && downleft(2) == BLANK && downleft(4) == BLANK && downleft(-1) == BLANK)
				summary[FC2]++;
		}
	}
	//----------------------------------------------------------------------------------------------------
	{
		//  活三	*paa**
		if (is_legal(x, y, 4, UP) && is_legal(x, y, 1, DOWN)) {
			if (up(1) == CHA_A && up(2) == CHA_A && up(3) == BLANK && up(4) == BLANK && up(-1) == BLANK)
				summary[F3]++;
		}
		//  活三2  *apa**
		if (is_legal(x, y, 3, UP) && is_legal(x, y, 2, DOWN)) {
			if (up(1) == CHA_A && up(2) == BLANK && up(3) == BLANK && up(-2) == BLANK && up(-1) == CHA_A)
				summary[F3]++;
		}
		//  活三3  *aap**
		if (is_legal(x, y, 3, UP) && is_legal(x, y, 2, DOWN)) {
			if (up(1) == CHA_A && up(2) == CHA_A && up(3) == BLANK && up(-2) == BLANK && up(-1) == BLANK)
				summary[F3]++;
		}
		//------------
		//  活三	*paa**
		if (is_legal(x, y, 4, DOWN) && is_legal(x, y, 1, UP)) {
			if (down(1) == CHA_A && down(2) == CHA_A && down(3) == BLANK && down(4) == BLANK && down(-1) == BLANK)
				summary[F3]++;
		}
		//  活三2  *apa**
		if (is_legal(x, y, 3, DOWN) && is_legal(x, y, 2, UP)) {
			if (down(1) == CHA_A && down(2) == BLANK && down(3) == BLANK && down(-2) == BLANK && down(-1) == CHA_A)
				summary[F3]++;
		}
		//  活三3  *aap**
		if (is_legal(x, y, 3, DOWN) && is_legal(x, y, 2, UP)) {
			if (down(1) == CHA_A && down(2) == CHA_A && down(3) == BLANK && down(-2) == BLANK && down(-1) == BLANK)
				summary[F3]++;
		}
		//----------------------------
		//  活三	*paa**
		if (is_legal(x, y, 4, LEFT) && is_legal(x, y, 1, RIGHT)) {
			if (left(1) == CHA_A && left(2) == CHA_A && left(3) == BLANK && left(4) == BLANK && left(-1) == BLANK)
				summary[F3]++;
		}
		//  活三2  *apa**
		if (is_legal(x, y, 3, LEFT) && is_legal(x, y, 2, RIGHT)) {
			if (left(1) == CHA_A && left(2) == BLANK && left(3) == BLANK && left(-2) == BLANK && left(-1) == CHA_A)
				summary[F3]++;
		}
		//  活三3  *aap**
		if (is_legal(x, y, 3, LEFT) && is_legal(x, y, 2, RIGHT)) {
			if (left(1) == CHA_A && left(2) == CHA_A && left(3) == BLANK && left(-2) == BLANK && left(-1) == BLANK)
				summary[F3]++;
		}
		//----------------------------
		//  活三	*paa**
		if (is_legal(x, y, 4, RIGHT) && is_legal(x, y, 1, LEFT)) {
			if (right(1) == CHA_A && right(2) == CHA_A && right(3) == BLANK && right(4) == BLANK && right(-1) == BLANK)
				summary[F3]++;
		}
		//  活三2  *apa**
		if (is_legal(x, y, 3, RIGHT) && is_legal(x, y, 2, LEFT)) {
			if (right(1) == CHA_A && right(2) == BLANK && right(3) == BLANK && right(-2) == BLANK && right(-1) == CHA_A)
				summary[F3]++;
		}
		//  活三3  *aap**
		if (is_legal(x, y, 3, RIGHT) && is_legal(x, y, 2, LEFT)) {
			if (right(1) == CHA_A && right(2) == CHA_A && right(3) == BLANK && right(-2) == BLANK && right(-1) == BLANK)
				summary[F3]++;
		}
		//----------------------------
		//  活三	*paa**
		if (is_legal(x, y, 4, UPRIGHT) && is_legal(x, y, 1, DOWNLEFT)) {
			if (upright(1) == CHA_A && upright(2) == CHA_A && upright(3) == BLANK && upright(4) == BLANK && upright(-1) == BLANK)
				summary[F3]++;
		}
		//  活三2  *apa**
		if (is_legal(x, y, 3, UPRIGHT) && is_legal(x, y, 2, DOWNLEFT)) {
			if (upright(1) == CHA_A && upright(2) == BLANK && upright(3) == BLANK && upright(-2) == BLANK && upright(-1) == CHA_A)
				summary[F3]++;
		}
		//  活三3  *aap**
		if (is_legal(x, y, 3, UPRIGHT) && is_legal(x, y, 2, DOWNLEFT)) {
			if (upright(1) == CHA_A && upright(2) == CHA_A && upright(3) == BLANK && upright(-2) == BLANK && upright(-1) == BLANK)
				summary[F3]++;
		}
		//----------------------------
		//  活三	*paa**
		if (is_legal(x, y, 4, DOWNLEFT) && is_legal(x, y, 1, UPRIGHT)) {
			if (downleft(1) == CHA_A && downleft(2) == CHA_A && downleft(3) == BLANK && downleft(4) == BLANK && downleft(-1) == BLANK)
				summary[F3]++;
		}
		//  活三2  *apa**
		if (is_legal(x, y, 3, DOWNLEFT) && is_legal(x, y, 2, UPRIGHT)) {
			if (downleft(1) == CHA_A && downleft(2) == BLANK && downleft(3) == BLANK && downleft(-2) == BLANK && downleft(-1) == CHA_A)
				summary[F3]++;
		}
		//  活三3  *aap**
		if (is_legal(x, y, 3, DOWNLEFT) && is_legal(x, y, 2, UPRIGHT)) {
			if (downleft(1) == CHA_A && downleft(2) == CHA_A && downleft(3) == BLANK && downleft(-2) == BLANK && downleft(-1) == BLANK)
				summary[F3]++;
		}
		//----------------------------
		//  活三	*paa**
		if (is_legal(x, y, 4, UPLEFT) && is_legal(x, y, 1, DOWNRIGHT)) {
			if (upleft(1) == CHA_A && upleft(2) == CHA_A && upleft(3) == BLANK && upleft(4) == BLANK && upleft(-1) == BLANK)
				summary[F3]++;
		}
		//  活三2  *apa**
		if (is_legal(x, y, 3, UPLEFT) && is_legal(x, y, 2, DOWNRIGHT)) {
			if (upleft(1) == CHA_A && upleft(2) == BLANK && upleft(3) == BLANK && upleft(-2) == BLANK && upleft(-1) == CHA_A)
				summary[F3]++;
		}
		//  活三3  *aap**
		if (is_legal(x, y, 3, UPLEFT) && is_legal(x, y, 2, DOWNRIGHT)) {
			if (upleft(1) == CHA_A && upleft(2) == CHA_A && upleft(3) == BLANK && upleft(-2) == BLANK && upleft(-1) == BLANK)
				summary[F3]++;
		}
		//----------------------------
		//  活三	*paa**
		if (is_legal(x, y, 4, DOWNRIGHT) && is_legal(x, y, 1, UPLEFT)) {
			if (downright(1) == CHA_A && downright(2) == CHA_A && downright(3) == BLANK && downright(4) == BLANK && downright(-1) == BLANK)
				summary[F3]++;
		}
		//  活三2  *apa**
		if (is_legal(x, y, 3, DOWNRIGHT) && is_legal(x, y, 2, UPLEFT)) {
			if (downright(1) == CHA_A && downright(2) == BLANK && downright(3) == BLANK && downright(-2) == BLANK && downright(-1) == CHA_A)
				summary[F3]++;
		}
		//  活三3  *aap**
		if (is_legal(x, y, 3, DOWNRIGHT) && is_legal(x, y, 2, UPLEFT)) {
			if (downright(1) == CHA_A && downright(2) == CHA_A && downright(3) == BLANK && downright(-2) == BLANK && downright(-1) == BLANK)
				summary[F3]++;
		}
	}
	//------------------------------------------------------------------------------------////

	{
		//	`*p*aa* 
		if (is_legal(x, y, 4, UP) && is_legal(x, y, 1, DOWN)) {
			if (up(1) == BLANK && up(2) == CHA_A && up(3) == CHA_A && up(4) == BLANK && up(-1) == BLANK)
				summary[FA3]++;
		}

		//	` *ap*a* 
		if (is_legal(x, y, 3, UP) && is_legal(x, y, 2, DOWN)) {
			if (up(1) == BLANK && up(2) == CHA_A && up(3) == BLANK && up(-1) == CHA_A && up(-2) == BLANK)
				summary[FA3]++;
		}

		//	*a*ap*`
		if (is_legal(x, y, 4, UP) && is_legal(x, y, 1, DOWN)) {
			if (up(1) == CHA_A && up(2) == BLANK && up(3) == CHA_A && up(4) == BLANK && up(-1) == BLANK)
				summary[FA3]++;
		}
		//********************
		//	`*p*aa* 
		if (is_legal(x, y, 4, DOWN) && is_legal(x, y, 1, UP)) {
			if (down(1) == BLANK && down(2) == CHA_A && down(3) == CHA_A && down(4) == BLANK && down(-1) == BLANK)
				summary[FA3]++;
		}

		//	` *ap*a* 
		if (is_legal(x, y, 3, DOWN) && is_legal(x, y, 2, UP)) {
			if (down(1) == BLANK && down(2) == CHA_A && down(3) == BLANK && down(-1) == CHA_A && down(-2) == BLANK)
				summary[FA3]++;
		}

		//	*a*ap*`
		if (is_legal(x, y, 4, DOWN) && is_legal(x, y, 1, UP)) {
			if (down(1) == CHA_A && down(2) == BLANK && down(3) == CHA_A && down(4) == BLANK && down(-1) == BLANK)
				summary[FA3]++;
		}
		//*****-*-*-*-*-*-*-*-*-*
		//	`*p*aa* 
		if (is_legal(x, y, 4, LEFT) && is_legal(x, y, 1, RIGHT)) {
			if (left(1) == BLANK && left(2) == CHA_A && left(3) == CHA_A && left(4) == BLANK && left(-1) == BLANK)
				summary[FA3]++;
		}

		//	` *ap*a* 
		if (is_legal(x, y, 3, LEFT) && is_legal(x, y, 2, RIGHT)) {
			if (left(1) == BLANK && left(2) == CHA_A && left(3) == BLANK && left(-1) == CHA_A && left(-2) == BLANK)
				summary[FA3]++;
		}

		//	*a*ap*`
		if (is_legal(x, y, 4, LEFT) && is_legal(x, y, 1, RIGHT)) {
			if (left(1) == CHA_A && left(2) == BLANK && left(3) == CHA_A && left(4) == BLANK && left(-1) == BLANK)
				summary[FA3]++;
		}
		//------------------------------------------------
		//	`*p*aa* 
		if (is_legal(x, y, 4, RIGHT) && is_legal(x, y, 1, LEFT)) {
			if (right(1) == BLANK && right(2) == CHA_A && right(3) == CHA_A && right(4) == BLANK && right(-1) == BLANK)
				summary[FA3]++;
		}

		//	` *ap*a* 
		if (is_legal(x, y, 3, RIGHT) && is_legal(x, y, 2, LEFT)) {
			if (right(1) == BLANK && right(2) == CHA_A && right(3) == BLANK && right(-1) == CHA_A && right(-2) == BLANK)
				summary[FA3]++;
		}

		//	*a*ap*`
		if (is_legal(x, y, 4, RIGHT) && is_legal(x, y, 1, LEFT)) {
			if (right(1) == CHA_A && right(2) == BLANK && right(3) == CHA_A && right(4) == BLANK && right(-1) == BLANK)
				summary[FA3]++;
		}

		//----------------------------
		//	`*p*aa* 
		if (is_legal(x, y, 4, UPRIGHT) && is_legal(x, y, 1, DOWNLEFT)) {
			if (upright(1) == BLANK && upright(2) == CHA_A && upright(3) == CHA_A && upright(4) == BLANK && upright(-1) == BLANK)
				summary[FA3]++;
		}

		//	` *ap*a* 
		if (is_legal(x, y, 3, UPRIGHT) && is_legal(x, y, 2, DOWNLEFT)) {
			if (upright(1) == BLANK && upright(2) == CHA_A && upright(3) == BLANK && upright(-1) == CHA_A && upright(-2) == BLANK)
				summary[FA3]++;
		}

		//	*a*ap*`
		if (is_legal(x, y, 4, UPRIGHT) && is_legal(x, y, 1, DOWNLEFT)) {
			if (upright(1) == CHA_A && upright(2) == BLANK && upright(3) == CHA_A && upright(4) == BLANK && upright(-1) == BLANK)
				summary[FA3]++;
		}
		//------------------------------------------------

		//	`*p*aa* 
		if (is_legal(x, y, 4, DOWNLEFT) && is_legal(x, y, 1, UPRIGHT)) {
			if (downleft(1) == BLANK && downleft(2) == CHA_A && downleft(3) == CHA_A && downleft(4) == BLANK && downleft(-1) == BLANK)
				summary[FA3]++;
		}

		//	` *ap*a* 
		if (is_legal(x, y, 3, DOWNLEFT) && is_legal(x, y, 2, UPRIGHT)) {
			if (downleft(1) == BLANK && downleft(2) == CHA_A && downleft(3) == BLANK && downleft(-1) == CHA_A && downleft(-2) == BLANK)
				summary[FA3]++;
		}

		//	*a*ap*`
		if (is_legal(x, y, 4, DOWNLEFT) && is_legal(x, y, 1, UPRIGHT)) {
			if (downleft(1) == CHA_A && downleft(2) == BLANK && downleft(3) == CHA_A && downleft(4) == BLANK && downleft(-1) == BLANK)
				summary[FA3]++;
		}
		//------------------------------------------------

		//	`*p*aa* 
		if (is_legal(x, y, 4, UPLEFT) && is_legal(x, y, 1, DOWNRIGHT)) {
			if (upleft(1) == BLANK && upleft(2) == CHA_A && upleft(3) == CHA_A && upleft(4) == BLANK && upleft(-1) == BLANK)
				summary[FA3]++;
		}

		//	` *ap*a* 
		if (is_legal(x, y, 3, UPLEFT) && is_legal(x, y, 2, DOWNRIGHT)) {
			if (upleft(1) == BLANK && upleft(2) == CHA_A && upleft(3) == BLANK && upleft(-1) == CHA_A && upleft(-2) == BLANK)
				summary[FA3]++;
		}

		//	*a*ap*`
		if (is_legal(x, y, 4, UPLEFT) && is_legal(x, y, 1, DOWNRIGHT)) {
			if (upleft(1) == CHA_A && upleft(2) == BLANK && upleft(3) == CHA_A && upleft(4) == BLANK && upleft(-1) == BLANK)
				summary[FA3]++;
		}
		//------------------------------------------------

		//	`*p*aa* 
		if (is_legal(x, y, 4, DOWNRIGHT) && is_legal(x, y, 1, UPLEFT)) {
			if (downright(1) == BLANK && downright(2) == CHA_A && downright(3) == CHA_A && downright(4) == BLANK && downright(-1) == BLANK)
				summary[FA3]++;
		}

		//	` *ap*a* 
		if (is_legal(x, y, 3, DOWNRIGHT) && is_legal(x, y, 2, UPLEFT)) {
			if (downright(1) == BLANK && downright(2) == CHA_A && downright(3) == BLANK && downright(-1) == CHA_A && downright(-2) == BLANK)
				summary[FA3]++;
		}

		//	*a*ap*`
		if (is_legal(x, y, 4, DOWNRIGHT) && is_legal(x, y, 1, UPLEFT)) {
			if (downright(1) == CHA_A && downright(2) == BLANK && downright(3) == CHA_A && downright(4) == BLANK && downright(-1) == BLANK)
				summary[FA3]++;
		}
	}
	//---------------------------------------------------------------------------//////////////
	{
		// 死三 **paab
		if (is_legal(x, y, 3, UP) && is_legal(x, y, 2, DOWN)) {
			if (up(1) == CHA_A && up(2) == CHA_A && up(3) == CHA_B && up(-1) == BLANK && up(-2) == BLANK)
				summary[S3]++;
		}

		//  *p*aab
		if (is_legal(x, y, 4, UP) && is_legal(x, y, 1, DOWN)) {
			if (up(1) == BLANK && up(2) == CHA_A && up(3) == CHA_A && up(4) == CHA_B && up(-1) == BLANK)
				summary[SA3]++;
		}
		//------------------------
		if (is_legal(x, y, 3, DOWN) && is_legal(x, y, 2, UP)) {
			if (down(1) == CHA_A && down(2) == CHA_A && down(3) == CHA_B && down(-1) == BLANK && down(-2) == BLANK)
				summary[S3]++;
		}

		//  *p*aab
		if (is_legal(x, y, 4, DOWN) && is_legal(x, y, 1, UP)) {
			if (down(1) == BLANK && down(2) == CHA_A && down(3) == CHA_A && down(4) == CHA_B && down(-1) == BLANK)
				summary[SA3]++;
		}
		//----------------------
		if (is_legal(x, y, 3, RIGHT) && is_legal(x, y, 2, LEFT)) {
			if (right(1) == CHA_A && right(2) == CHA_A && right(3) == CHA_B && right(-1) == BLANK && right(-2) == BLANK)
				summary[S3]++;
		}

		//  *p*aab
		if (is_legal(x, y, 4, RIGHT) && is_legal(x, y, 1, LEFT)) {
			if (right(1) == BLANK && right(2) == CHA_A && right(3) == CHA_A && right(4) == CHA_B && right(-1) == BLANK)
				summary[SA3]++;
		}
		//-------------------------
		if (is_legal(x, y, 3, LEFT) && is_legal(x, y, 2, RIGHT)) {
			if (left(1) == CHA_A && left(2) == CHA_A && left(3) == CHA_B && left(-1) == BLANK && left(-2) == BLANK)
				summary[S3]++;
		}

		//  *p*aab
		if (is_legal(x, y, 4, LEFT) && is_legal(x, y, 1, RIGHT)) {
			if (left(1) == BLANK && left(2) == CHA_A && left(3) == CHA_A && left(4) == CHA_B && left(-1) == BLANK)
				summary[SA3]++;
		}
		//---------------------------
		if (is_legal(x, y, 3, UPRIGHT) && is_legal(x, y, 2, DOWNLEFT)) {
			if (upright(1) == CHA_A && upright(2) == CHA_A && upright(3) == CHA_B && upright(-1) == BLANK && upright(-2) == BLANK)
				summary[S3]++;
		}

		//  *p*aab
		if (is_legal(x, y, 4, UPRIGHT) && is_legal(x, y, 1, DOWNLEFT)) {
			if (upright(1) == BLANK && upright(2) == CHA_A && upright(3) == CHA_A && upright(4) == CHA_B && upright(-1) == BLANK)
				summary[SA3]++;
		}
		//----------------------------
		if (is_legal(x, y, 3, DOWNLEFT) && is_legal(x, y, 2, UPRIGHT)) {
			if (downleft(1) == CHA_A && downleft(2) == CHA_A && downleft(3) == CHA_B && downleft(-1) == BLANK && downleft(-2) == BLANK)
				summary[S3]++;
		}

		//  *p*aab
		if (is_legal(x, y, 4, DOWNLEFT) && is_legal(x, y, 1, UPRIGHT)) {
			if (downleft(1) == BLANK && downleft(2) == CHA_A && downleft(3) == CHA_A && downleft(4) == CHA_B && downleft(-1) == BLANK)
				summary[SA3]++;
		}
		//----------------------------
		if (is_legal(x, y, 3, DOWNRIGHT) && is_legal(x, y, 2, UPLEFT)) {
			if (downright(1) == CHA_A && downright(2) == CHA_A && downright(3) == CHA_B && downright(-1) == BLANK && downright(-2) == BLANK)
				summary[S3]++;
		}

		//  *p*aab
		if (is_legal(x, y, 4, DOWNRIGHT) && is_legal(x, y, 1, UPLEFT)) {
			if (downright(1) == BLANK && downright(2) == CHA_A && downright(3) == CHA_A && downright(4) == CHA_B && downright(-1) == BLANK)
				summary[SA3]++;
		}
		//----------------------------
		if (is_legal(x, y, 3, UPLEFT) && is_legal(x, y, 2, DOWNRIGHT)) {
			if (upleft(1) == CHA_A && upleft(2) == CHA_A && upleft(3) == CHA_B && upleft(-1) == BLANK && upleft(-2) == BLANK)
				summary[S3]++;
		}

		//  *p*aab
		if (is_legal(x, y, 4, UPLEFT) && is_legal(x, y, 1, DOWNRIGHT)) {
			if (upleft(1) == BLANK && upleft(2) == CHA_A && upleft(3) == CHA_A && upleft(4) == CHA_B && upleft(-1) == BLANK)
				summary[SA3]++;
		}
	}
	//-------------------------------------------------------******************-----------------------///
	{//活四 `*paaa*` 
		if (is_legal(x, y, 4, UP) && is_legal(x, y, 1, DOWN)) {
			if (up(1) == CHA_A && up(2) == CHA_A && up(3) == CHA_A && up(4) == BLANK && up(-1) == BLANK)
				summary[F4]++;
		}

		//`*apaa*`
		if (is_legal(x, y, 3, UP) && is_legal(x, y, 2, DOWN)) {
			if (up(1) == CHA_A && up(2) == CHA_A && up(3) == BLANK && up(-1) == CHA_A && up(-2) == BLANK)
				summary[F4]++;
		}
		//活四 `*paaa*`/////////////----------------------------- 
		if (is_legal(x, y, 4, DOWN) && is_legal(x, y, 1, UP)) {
			if (down(1) == CHA_A && down(2) == CHA_A && down(3) == CHA_A && down(4) == BLANK && down(-1) == BLANK)
				summary[F4]++;
		}

		//`*apaa*`
		if (is_legal(x, y, 3, DOWN) && is_legal(x, y, 2, UP)) {
			if (down(1) == CHA_A && down(2) == CHA_A && down(3) == BLANK && down(-1) == CHA_A && down(-2) == BLANK)
				summary[F4]++;
		}
		//活四 `*paaa*` --------------------------------------
		if (is_legal(x, y, 4, RIGHT) && is_legal(x, y, 1, LEFT)) {
			if (right(1) == CHA_A && right(2) == CHA_A && right(3) == CHA_A && right(4) == BLANK && right(-1) == BLANK)
				summary[F4]++;
		}

		//`*apaa*`
		if (is_legal(x, y, 3, RIGHT) && is_legal(x, y, 2, LEFT)) {
			if (right(1) == CHA_A && right(2) == CHA_A && right(3) == BLANK && right(-1) == CHA_A && right(-2) == BLANK)
				summary[F4]++;
		}
		//活四 `*paaa*` -----------------------------------
		if (is_legal(x, y, 4, LEFT) && is_legal(x, y, 1, RIGHT)) {
			if (left(1) == CHA_A && left(2) == CHA_A && left(3) == CHA_A && left(4) == BLANK && left(-1) == BLANK)
				summary[F4]++;
		}

		//`*apaa*`
		if (is_legal(x, y, 3, LEFT) && is_legal(x, y, 2, RIGHT)) {
			if (left(1) == CHA_A && left(2) == CHA_A && left(3) == BLANK && left(-1) == CHA_A && left(-2) == BLANK)
				summary[F4]++;
		}
		//活四 `*paaa*` -----------------------------------
		if (is_legal(x, y, 4, UPRIGHT) && is_legal(x, y, 1, DOWNLEFT)) {
			if (upright(1) == CHA_A && upright(2) == CHA_A && upright(3) == CHA_A && upright(4) == BLANK && upright(-1) == BLANK)
				summary[F4]++;
		}

		//`*apaa*`
		if (is_legal(x, y, 3, UPRIGHT) && is_legal(x, y, 2, DOWNLEFT)) {
			if (upright(1) == CHA_A && upright(2) == CHA_A && upright(3) == BLANK && upright(-1) == CHA_A && upright(-2) == BLANK)
				summary[F4]++;
		}
		//活四 `*paaa*` ---------------------------------
		if (is_legal(x, y, 4, UPLEFT) && is_legal(x, y, 1, DOWNRIGHT)) {
			if (upleft(1) == CHA_A && upleft(2) == CHA_A && upleft(3) == CHA_A && upleft(4) == BLANK && upleft(-1) == BLANK){
				summary[F4]++;
			/*for (int i = 0; i < 15; i++) {
				for (int j = 0; j < 15; j++) {
					cout << map[i][j] << " ";
				}
				cout << endl;
			}
			cout << DOWNRIGHT << endl;
			cout << (x < (BOUNDARY - 1) && y < (BOUNDARY -1))<< endl;
			cout << is_legal(x, y, 1, DOWNRIGHT);
			cout << endl;
			*/
			}
		}

		//`*apaa*`
		if (is_legal(x, y, 3, UPLEFT) && is_legal(x, y, 2, DOWNRIGHT)) {
			if (upleft(1) == CHA_A && upleft(2) == CHA_A && upleft(3) == BLANK && upleft(-1) == CHA_A && upleft(-2) == BLANK)
				summary[F4]++;
		}
		//活四 `*paaa*` --------------------------------------
		if (is_legal(x, y, 4, DOWNLEFT) && is_legal(x, y, 1, UPRIGHT)) {
			if (downleft(1) == CHA_A && downleft(2) == CHA_A && downleft(3) == CHA_A && downleft(4) == BLANK && downleft(-1) == BLANK)
 				summary[F4]++;
		}

		//`*apaa*`
		if (is_legal(x, y, 3, DOWNLEFT) && is_legal(x, y, 2, UPRIGHT)) {
			if (downleft(1) == CHA_A && downleft(2) == CHA_A && downleft(3) == BLANK && downleft(-1) == CHA_A && downleft(-2) == BLANK)
				summary[F4]++;
		}
		//活四 `*paaa*` ---------------------------------------
		if (is_legal(x, y, 4, DOWNRIGHT) && is_legal(x, y, 1, UPLEFT)) {
			if (downright(1) == CHA_A && downright(2) == CHA_A && downright(3) == CHA_A && downright(4) == BLANK && downright(-1) == BLANK)
				summary[F4]++;
		}

		//`*apaa*`
		if (is_legal(x, y, 3, DOWNRIGHT) && is_legal(x, y, 2, UPLEFT)) {
			if (downright(1) == CHA_A && downright(2) == CHA_A && downright(3) == BLANK && downright(-1) == CHA_A && downright(-2) == BLANK)
				summary[F4]++;
		}
	}
	{
		//p*aaa
		if (is_legal(x, y, 4, UP)) {
			if (up(1) == BLANK && up(2) == CHA_A && up(3) == CHA_A && up(4) == CHA_A)
				summary[SA4]++;
		}
		if (is_legal(x, y, 4, DOWN)) {
			if (down(1) == BLANK && down(2) == CHA_A && down(3) == CHA_A && down(4) == CHA_A)
				summary[SA4]++;
		}
		if (is_legal(x, y, 4, LEFT)) {
			if (left(1) == BLANK && left(2) == CHA_A && left(3) == CHA_A && left(4) == CHA_A)
				summary[SA4]++;
		}
		if (is_legal(x, y, 4, RIGHT)) {
			if (right(1) == BLANK && right(2) == CHA_A && right(3) == CHA_A && right(4) == CHA_A)
				summary[SA4]++;
		}
		if (is_legal(x, y, 4, UPLEFT)) {
			if (upleft(1) == BLANK && upleft(2) == CHA_A && upleft(3) == CHA_A && upleft(4) == CHA_A)
				summary[SA4]++;
		}
		if (is_legal(x, y, 4, UPRIGHT)) {
			if (upright(1) == BLANK && upright(2) == CHA_A && upright(3) == CHA_A && upright(4) == CHA_A)
				summary[SA4]++;
		}
		if (is_legal(x, y, 4, DOWNLEFT)) {
			if (downleft(1) == BLANK && downleft(2) == CHA_A && downleft(3) == CHA_A && downleft(4) == CHA_A)
				summary[SA4]++;
		}
		if (is_legal(x, y, 4, DOWNRIGHT)) {
			if (downright(1) == BLANK && downright(2) == CHA_A && downright(3) == CHA_A && downright(4) == CHA_A)
				summary[SA4]++;
		}


	}

	////------------------------------------------------**********************-----------------------////
	{//`baaap*`
		if (is_legal(x, y, 4, UP) && is_legal(x, y, 1, DOWN)) {
			if (up(1) == CHA_A && up(2) == CHA_A && up(3) == CHA_A && up(4) == CHA_B && up(-1) == BLANK)
				summary[S4]++;
		}

		//`baapa*`
		if (is_legal(x, y, 3, UP) && is_legal(x, y, 2, DOWN)) {
			if (up(1) == CHA_A && up(2) == CHA_A && up(3) == CHA_B && up(-1) == CHA_A && up(-2) == BLANK)
				summary[SA4]++;
		}
		///------------------------------------------------
		if (is_legal(x, y, 4, DOWN) && is_legal(x, y, 1, UP)) {
			if (down(1) == CHA_A && down(2) == CHA_A && down(3) == CHA_A && down(4) == CHA_B && down(-1) == BLANK)
				summary[S4]++;
		}

		//`baapa*`
		if (is_legal(x, y, 3, DOWN) && is_legal(x, y, 2, UP)) {
			if (down(1) == CHA_A && down(2) == CHA_A && down(3) == CHA_B && down(-1) == CHA_A && down(-2) == BLANK)
				summary[SA4]++;
		}
		//---///------------------------------------------
		if (is_legal(x, y, 4, LEFT) && is_legal(x, y, 1, RIGHT)) {
			if (left(1) == CHA_A && left(2) == CHA_A && left(3) == CHA_A && left(4) == CHA_B && left(-1) == BLANK)
				summary[S4]++;
		}

		//`baapa*`
		if (is_legal(x, y, 3, LEFT) && is_legal(x, y, 2, RIGHT)) {
			if (left(1) == CHA_A && left(2) == CHA_A && left(3) == CHA_B && left(-1) == CHA_A && left(-2) == BLANK)
				summary[SA4]++;
		}
		//----------------------------
		if (is_legal(x, y, 4, RIGHT) && is_legal(x, y, 1, LEFT)) {
			if (right(1) == CHA_A && right(2) == CHA_A && right(3) == CHA_A && right(4) == CHA_B && right(-1) == BLANK)
				summary[S4]++;
		}

		//`baapa*`
		if (is_legal(x, y, 3, RIGHT) && is_legal(x, y, 2, LEFT)) {
			if (right(1) == CHA_A && right(2) == CHA_A && right(3) == CHA_B && right(-1) == CHA_A && right(-2) == BLANK)
				summary[SA4]++;
		}
		//----------------------------
		if (is_legal(x, y, 4, UPLEFT) && is_legal(x, y, 1, DOWNRIGHT)) {
			if (upleft(1) == CHA_A && upleft(2) == CHA_A && upleft(3) == CHA_A && upleft(4) == CHA_B && upleft(-1) == BLANK)
				summary[S4]++;
		}

		//`baapa*`
		if (is_legal(x, y, 3, UPLEFT) && is_legal(x, y, 2, DOWNRIGHT)) {
			if (upleft(1) == CHA_A && upleft(2) == CHA_A && upleft(3) == CHA_B && upleft(-1) == CHA_A && upleft(-2) == BLANK)
				summary[SA4]++;
		}
		//---------------------------
		if (is_legal(x, y, 4, UPRIGHT) && is_legal(x, y, 1, DOWNLEFT)) {
			if (upright(1) == CHA_A && upright(2) == CHA_A && upright(3) == CHA_A && upright(4) == CHA_B && upright(-1) == BLANK)
				summary[S4]++;
		}

		//`baapa*`
		if (is_legal(x, y, 3, UPRIGHT) && is_legal(x, y, 2, DOWNLEFT)) {
			if (upright(1) == CHA_A && upright(2) == CHA_A && upright(3) == CHA_B && upright(-1) == CHA_A && upright(-2) == BLANK)
				summary[SA4]++;
		}
		//-----------------------
		if (is_legal(x, y, 4, DOWNRIGHT) && is_legal(x, y, 1, UPLEFT)) {
			if (downright(1) == CHA_A && downright(2) == CHA_A && downright(3) == CHA_A && downright(4) == CHA_B && downright(-1) == BLANK)
				summary[S4]++;
		}

		//`baapa*`
		if (is_legal(x, y, 3, DOWNRIGHT) && is_legal(x, y, 2, UPLEFT)) {
			if (downright(1) == CHA_A && downright(2) == CHA_A && downright(3) == CHA_B && downright(-1) == CHA_A && downright(-2) == BLANK)
				summary[SA4]++;
		}
		//------------------------
		if (is_legal(x, y, 4, DOWNLEFT) && is_legal(x, y, 1, UPRIGHT)) {
			if (downleft(1) == CHA_A && downleft(2) == CHA_A && downleft(3) == CHA_A && downleft(4) == CHA_B && downleft(-1) == BLANK)
				summary[S4]++;
		}

		//`baapa*`
		if (is_legal(x, y, 3, DOWNLEFT) && is_legal(x, y, 2, UPRIGHT)) {
			if (downleft(1) == CHA_A && downleft(2) == CHA_A && downleft(3) == CHA_B && downleft(-1) == CHA_A && downleft(-2) == BLANK)
				summary[SA4]++;
		}

	}
	///----------------------------------------------------------------------------------------------

	{//`aapaa`
		if (is_legal(x, y, 2, UP) && is_legal(x, y, 2, DOWN)) {
			if (up(1) == CHA_A && up(2) == CHA_A && up(-1) == CHA_A && up(-2) == CHA_A)
				summary[WIN5]++;
		}

		//`apaaa`
		if (is_legal(x, y, 3, UP) && is_legal(x, y, 1, DOWN)) {
			if (up(1) == CHA_A && up(2) == CHA_A && up(3) == CHA_A && up(-1) == CHA_A)
				summary[WIN5]++;
		}

		//`paaaa`
		if (is_legal(x, y, 4, UP)) {
			if (up(1) == CHA_A && up(2) == CHA_A && up(3) == CHA_A && up(4) == CHA_A)
				summary[WIN5]++;
		}
		//--------------------------------------
		//`aapaa`
		if (is_legal(x, y, 2, DOWN) && is_legal(x, y, 2, UP)) {
			if (down(1) == CHA_A && down(2) == CHA_A && down(-1) == CHA_A && down(-2) == CHA_A)
				summary[WIN5]++;
		}

		//`apaaa`
		if (is_legal(x, y, 3, DOWN) && is_legal(x, y, 1, UP)) {
			if (down(1) == CHA_A && down(2) == CHA_A && down(3) == CHA_A && down(-1) == CHA_A)
				summary[WIN5]++;
		}

		//`paaaa`
		if (is_legal(x, y, 4, DOWN)) {
			if (down(1) == CHA_A && down(2) == CHA_A && down(3) == CHA_A && down(4) == CHA_A)
				summary[WIN5]++;
		}
		//--------------------------------------
		//`aapaa`
		if (is_legal(x, y, 2, LEFT) && is_legal(x, y, 2, RIGHT)) {
			if (left(1) == CHA_A && left(2) == CHA_A && left(-1) == CHA_A && left(-2) == CHA_A)
				summary[WIN5]++;
		}

		//`apaaa`
		if (is_legal(x, y, 3, LEFT) && is_legal(x, y, 1, RIGHT)) {
			if (left(1) == CHA_A && left(2) == CHA_A && left(3) == CHA_A && left(-1) == CHA_A)
				summary[WIN5]++;
		}

		//`paaaa`
		if (is_legal(x, y, 4, LEFT)) {
			if (left(1) == CHA_A && left(2) == CHA_A && left(3) == CHA_A && left(4) == CHA_A)
				summary[WIN5]++;
		}
		//------------------------------------------
		//`aapaa`
		if (is_legal(x, y, 2, RIGHT) && is_legal(x, y, 2, LEFT)) {
			if (right(1) == CHA_A && right(2) == CHA_A && right(-1) == CHA_A && right(-2) == CHA_A)
				summary[WIN5]++;
		}

		//`apaaa`
		if (is_legal(x, y, 3, RIGHT) && is_legal(x, y, 1, LEFT)) {
			if (right(1) == CHA_A && right(2) == CHA_A && right(3) == CHA_A && right(-1) == CHA_A)
				summary[WIN5]++;
		}

		//`paaaa`
		if (is_legal(x, y, 4, RIGHT)) {
			if (right(1) == CHA_A && right(2) == CHA_A && right(3) == CHA_A && right(4) == CHA_A)
				summary[WIN5]++;
		}
		//----------------------------------------
		//`aapaa`
		if (is_legal(x, y, 2, UPRIGHT) && is_legal(x, y, 2, DOWNLEFT)) {
			if (upright(1) == CHA_A && upright(2) == CHA_A && upright(-1) == CHA_A && upright(-2) == CHA_A)
				summary[WIN5]++;
		}

		//`apaaa`
		if (is_legal(x, y, 3, UPRIGHT) && is_legal(x, y, 1, DOWNLEFT)) {
			if (upright(1) == CHA_A && upright(2) == CHA_A && upright(3) == CHA_A && upright(-1) == CHA_A)
				summary[WIN5]++;
		}

		//`paaaa`
		if (is_legal(x, y, 4, UPRIGHT)) {
			if (upright(1) == CHA_A && upright(2) == CHA_A && upright(3) == CHA_A && upright(4) == CHA_A)
				summary[WIN5]++;
		}
		//---------------------------------------
		//`aapaa`
		if (is_legal(x, y, 2, UPLEFT) && is_legal(x, y, 2, DOWNRIGHT)) {
			if (upleft(1) == CHA_A && upleft(2) == CHA_A && upleft(-1) == CHA_A && upleft(-2) == CHA_A)
				summary[WIN5]++;
		}

		//`apaaa`
		if (is_legal(x, y, 3, UPLEFT) && is_legal(x, y, 1, DOWNRIGHT)) {
			if (upleft(1) == CHA_A && upleft(2) == CHA_A && upleft(3) == CHA_A && upleft(-1) == CHA_A)
				summary[WIN5]++;
		}

		//`paaaa`
		if (is_legal(x, y, 4, UPLEFT)) {
			if (upleft(1) == CHA_A && upleft(2) == CHA_A && upleft(3) == CHA_A && upleft(4) == CHA_A)
				summary[WIN5]++;
		}
		//-----------------------------------------
		//`aapaa`
		if (is_legal(x, y, 2, DOWNLEFT) && is_legal(x, y, 2, UPRIGHT)) {
			if (downleft(1) == CHA_A && downleft(2) == CHA_A && downleft(-1) == CHA_A && downleft(-2) == CHA_A)
				summary[WIN5]++;
		}

		//`apaaa`
		if (is_legal(x, y, 3, DOWNLEFT) && is_legal(x, y, 1, UPRIGHT)) {
			if (downleft(1) == CHA_A && downleft(2) == CHA_A && downleft(3) == CHA_A && downleft(-1) == CHA_A)
				summary[WIN5]++;
		}

		//`paaaa`
		if (is_legal(x, y, 4, DOWNLEFT)) {
			if (downleft(1) == CHA_A && downleft(2) == CHA_A && downleft(3) == CHA_A && downleft(4) == CHA_A)
				summary[WIN5]++;
		}
		//---------------------------
		//`aapaa`
		if (is_legal(x, y, 2, DOWNRIGHT) && is_legal(x, y, 2, UPLEFT)) {
			if (downright(1) == CHA_A && downright(2) == CHA_A && downright(-1) == CHA_A && downright(-2) == CHA_A)
				summary[WIN5]++;
		}

		//`apaaa`
		if (is_legal(x, y, 3, DOWNRIGHT) && is_legal(x, y, 1, UPLEFT)) {
			if (downright(1) == CHA_A && downright(2) == CHA_A && downright(3) == CHA_A && downright(-1) == CHA_A)
				summary[WIN5]++;
		}

		//`paaaa`
		if (is_legal(x, y, 4, DOWNRIGHT)) {
			if (downright(1) == CHA_A && downright(2) == CHA_A && downright(3) == CHA_A && downright(4) == CHA_A)
				summary[WIN5]++;
		}
	}
	//------------------------------------------------------------------------

	int free2 = summary[F2],
		freeB2 = summary[FB2],
		freeC2 = summary[FC2],
		sleep2 = summary[S2],
		dead2 = summary[D2],
		free3 = summary[F3],
		freeA3 = summary[FA3],
		sleep3 = summary[S3],
		sleepA3 = summary[SA3],
		win4 = summary[F4],
		win5 = summary[WIN5],
		sleep4 = summary[S4],
		sleepA4 = summary[SA4];

	if (win5)
		return  50000;
	else if (win4) 
		return 4320;
	else if (free3+freeA3>=2)
		return 4000;
	else return SUM(free2) + SUM(freeB2) + SUM(freeC2) + SUM(sleep2) + SUM(dead2) +
		SUM(free3) + SUM(freeA3) + SUM(sleep3) + SUM(sleepA3) + SUM(win4) + SUM(win5) +
		SUM(sleep4) + SUM(sleepA4);
										    
}	
#endif