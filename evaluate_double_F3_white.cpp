#if 1
//		基于点评估的估值函数
#include "ChessMap.h"

#define F3 1
#define FA3 2
#define F4 3
#define SA4 5
#define WIN5 4

#define CHA_A 2
#define CHA_B 1
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


const int w_free3 = 100;
const int w_freeA3 = 100;
const int w_sleep3 = 10;
const int w_sleepA3 = 10;
const int w_win4 = 10000;
const int w_win5 = 10000;
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
	case DOWN:
		if (x < BOUNDARY - lenth)
			return true;
		else return false;
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
		if (x < BOUNDARY - lenth && y < BOUNDARY - lenth)
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
int evaluate_double_F3_white(const int(*map)[15], int x, int y) {
	//if (map[x][y] != 2) return 0;// 如果有子直接退出 ，以后还会再优化吧

	int summary[6] = { 0 };
	int d_summary[9][6] = { 0 };
	{

		{
			//  活三	*paa*
			if (is_legal(x, y, 3, UP) && is_legal(x, y, 1, DOWN)) {
				if (up(1) == CHA_A && up(2) == CHA_A && up(3) == BLANK && up(-1) == BLANK)
					summary[F3]++;
			}
			//  活三2  *apa*
			if (is_legal(x, y, 2, UP) && is_legal(x, y, 2, DOWN)) {
				if (up(1) == CHA_A && up(2) == BLANK && up(-2) == BLANK && up(-1) == CHA_A)
					summary[F3]++;
			}
			//------------
			//  活三	*paa*
			if (is_legal(x, y, 3, DOWN) && is_legal(x, y, 1, UP)) {
				if (down(1) == CHA_A && down(2) == CHA_A && down(3) == BLANK && down(-1) == BLANK)
					summary[F3]++;
			}
			//----------------------------
			//  活三	*paa*
			if (is_legal(x, y, 3, LEFT) && is_legal(x, y, 1, RIGHT)) {
				if (left(1) == CHA_A && left(2) == CHA_A && left(3) == BLANK && left(-1) == BLANK)
					summary[F3]++;
			}
			//  活三2  *apa*
			if (is_legal(x, y, 2, LEFT) && is_legal(x, y, 2, RIGHT)) {
				if (left(1) == CHA_A && left(2) == BLANK && left(-2) == BLANK && left(-1) == CHA_A)
					summary[F3]++;
			}

			//----------------------------
			//  活三	*paa*
			if (is_legal(x, y, 3, RIGHT) && is_legal(x, y, 1, LEFT)) {
				if (right(1) == CHA_A && right(2) == CHA_A && right(3) == BLANK && right(-1) == BLANK)
					summary[F3]++;
			}

			//----------------------------
			//  活三	*paa*
			if (is_legal(x, y, 3, UPRIGHT) && is_legal(x, y, 1, DOWNLEFT)) {
				if (upright(1) == CHA_A && upright(2) == CHA_A && upright(3) == BLANK && upright(-1) == BLANK)
					summary[F3]++;
			}
			//  活三2  *apa**
			if (is_legal(x, y, 2, UPRIGHT) && is_legal(x, y, 2, DOWNLEFT)) {
				if (upright(1) == CHA_A && upright(2) == BLANK && upright(-2) == BLANK && upright(-1) == CHA_A)
					summary[F3]++;
			}

			//----------------------------
			//  活三	*paa*
			if (is_legal(x, y, 3, DOWNLEFT) && is_legal(x, y, 1, UPRIGHT)) {
				if (downleft(1) == CHA_A && downleft(2) == CHA_A && downleft(3) == BLANK && downleft(-1) == BLANK)
					summary[F3]++;
			}

			//----------------------------
			//  活三	*paa*
			if (is_legal(x, y, 3, UPLEFT) && is_legal(x, y, 1, DOWNRIGHT)) {
				if (upleft(1) == CHA_A && upleft(2) == CHA_A && upleft(3) == BLANK && upleft(-1) == BLANK)
					summary[F3]++;
			}
			//  活三2  *apa*
			if (is_legal(x, y, 2, UPLEFT) && is_legal(x, y, 2, DOWNRIGHT)) {
				if (upleft(1) == CHA_A && upleft(2) == BLANK && upleft(-2) == BLANK && upleft(-1) == CHA_A)
					summary[F3]++;
			}

			//----------------------------
			//  活三	*paa*
			if (is_legal(x, y, 3, DOWNRIGHT) && is_legal(x, y, 1, UPLEFT)) {
				if (downright(1) == CHA_A && downright(2) == CHA_A && downright(3) == BLANK && downright(-1) == BLANK)
					summary[F3]++;
			}
		}
		//------------------------------------------------------------------------------------////

		{
			//	`*p*aa* 
			if (is_legal(x, y, 4, UP) && is_legal(x, y, 1, DOWN)) {
				if (up(1) == BLANK && up(2) == CHA_A && up(3) == CHA_A && up(4) == BLANK && up(-1) == BLANK)
					d_summary[UP][FA3] = 1;
			}

			//	` *ap*a* 
			if (is_legal(x, y, 3, UP) && is_legal(x, y, 2, DOWN)) {
				if (up(1) == BLANK && up(2) == CHA_A && up(3) == BLANK && up(-1) == CHA_A && up(-2) == BLANK)
					d_summary[UP][FA3] = 1;
			}

			//	*a*ap*`
			if (is_legal(x, y, 4, UP) && is_legal(x, y, 1, DOWN)) {
				if (up(1) == CHA_A && up(2) == BLANK && up(3) == CHA_A && up(4) == BLANK && up(-1) == BLANK)
					d_summary[UP][FA3] = 1;
			}
			//********************
			//	`*p*aa* 
			if (is_legal(x, y, 4, DOWN) && is_legal(x, y, 1, UP)) {
				if (down(1) == BLANK && down(2) == CHA_A && down(3) == CHA_A && down(4) == BLANK && down(-1) == BLANK)
					d_summary[DOWN][FA3] = 1;
			}

			//	` *ap*a* 
			if (is_legal(x, y, 3, DOWN) && is_legal(x, y, 2, UP)) {
				if (down(1) == BLANK && down(2) == CHA_A && down(3) == BLANK && down(-1) == CHA_A && down(-2) == BLANK)
					d_summary[DOWN][FA3] = 1;
			}

			//	*a*ap*`
			if (is_legal(x, y, 4, DOWN) && is_legal(x, y, 1, UP)) {
				if (down(1) == CHA_A && down(2) == BLANK && down(3) == CHA_A && down(4) == BLANK && down(-1) == BLANK)
					d_summary[DOWN][FA3] = 1;
			}
			//*****-*-*-*-*-*-*-*-*-*
			//	`*p*aa* 
			if (is_legal(x, y, 4, LEFT) && is_legal(x, y, 1, RIGHT)) {
				if (left(1) == BLANK && left(2) == CHA_A && left(3) == CHA_A && left(4) == BLANK && left(-1) == BLANK)
					d_summary[LEFT][FA3] = 1;
			}

			//	` *ap*a* 
			if (is_legal(x, y, 3, LEFT) && is_legal(x, y, 2, RIGHT)) {
				if (left(1) == BLANK && left(2) == CHA_A && left(3) == BLANK && left(-1) == CHA_A && left(-2) == BLANK)
					d_summary[LEFT][FA3] = 1;
			}

			//	*a*ap*`
			if (is_legal(x, y, 4, LEFT) && is_legal(x, y, 1, RIGHT)) {
				if (left(1) == CHA_A && left(2) == BLANK && left(3) == CHA_A && left(4) == BLANK && left(-1) == BLANK)
					d_summary[LEFT][FA3] = 1;
			}
			//------------------------------------------------
			//	`*p*aa* 
			if (is_legal(x, y, 4, RIGHT) && is_legal(x, y, 1, LEFT)) {
				if (right(1) == BLANK && right(2) == CHA_A && right(3) == CHA_A && right(4) == BLANK && right(-1) == BLANK)
					d_summary[RIGHT][FA3] = 1;
			}

			//	` *ap*a* 
			if (is_legal(x, y, 3, RIGHT) && is_legal(x, y, 2, LEFT)) {
				if (right(1) == BLANK && right(2) == CHA_A && right(3) == BLANK && right(-1) == CHA_A && right(-2) == BLANK)
					d_summary[RIGHT][FA3] = 1;
			}

			//	*a*ap*`
			if (is_legal(x, y, 4, RIGHT) && is_legal(x, y, 1, LEFT)) {
				if (right(1) == CHA_A && right(2) == BLANK && right(3) == CHA_A && right(4) == BLANK && right(-1) == BLANK)
					d_summary[RIGHT][FA3] = 1;
			}

			//----------------------------
			//	`*p*aa* 
			if (is_legal(x, y, 4, UPRIGHT) && is_legal(x, y, 1, DOWNLEFT)) {
				if (upright(1) == BLANK && upright(2) == CHA_A && upright(3) == CHA_A && upright(4) == BLANK && upright(-1) == BLANK)
					d_summary[UPRIGHT][FA3] = 1;
			}

			//	` *ap*a* 
			if (is_legal(x, y, 3, UPRIGHT) && is_legal(x, y, 2, DOWNLEFT)) {
				if (upright(1) == BLANK && upright(2) == CHA_A && upright(3) == BLANK && upright(-1) == CHA_A && upright(-2) == BLANK)
					d_summary[UPRIGHT][FA3] = 1;
			}

			//	*a*ap*`
			if (is_legal(x, y, 4, UPRIGHT) && is_legal(x, y, 1, DOWNLEFT)) {
				if (upright(1) == CHA_A && upright(2) == BLANK && upright(3) == CHA_A && upright(4) == BLANK && upright(-1) == BLANK)
					d_summary[UPRIGHT][FA3] = 1;
			}
			//------------------------------------------------

			//	`*p*aa* 
			if (is_legal(x, y, 4, DOWNLEFT) && is_legal(x, y, 1, UPRIGHT)) {
				if (downleft(1) == BLANK && downleft(2) == CHA_A && downleft(3) == CHA_A && downleft(4) == BLANK && downleft(-1) == BLANK)
					d_summary[DOWNLEFT][FA3] = 1;
			}

			//	` *ap*a* 
			if (is_legal(x, y, 3, DOWNLEFT) && is_legal(x, y, 2, UPRIGHT)) {
				if (downleft(1) == BLANK && downleft(2) == CHA_A && downleft(3) == BLANK && downleft(-1) == CHA_A && downleft(-2) == BLANK)
					d_summary[DOWNLEFT][FA3] = 1;
			}

			//	*a*ap*`
			if (is_legal(x, y, 4, DOWNLEFT) && is_legal(x, y, 1, UPRIGHT)) {
				if (downleft(1) == CHA_A && downleft(2) == BLANK && downleft(3) == CHA_A && downleft(4) == BLANK && downleft(-1) == BLANK)
					d_summary[DOWNLEFT][FA3] = 1;
			}
			//------------------------------------------------

			//	`*p*aa* 
			if (is_legal(x, y, 4, UPLEFT) && is_legal(x, y, 1, DOWNRIGHT)) {
				if (upleft(1) == BLANK && upleft(2) == CHA_A && upleft(3) == CHA_A && upleft(4) == BLANK && upleft(-1) == BLANK)
					d_summary[UPLEFT][FA3] = 1;
			}

			//	` *ap*a* 
			if (is_legal(x, y, 3, UPLEFT) && is_legal(x, y, 2, DOWNRIGHT)) {
				if (upleft(1) == BLANK && upleft(2) == CHA_A && upleft(3) == BLANK && upleft(-1) == CHA_A && upleft(-2) == BLANK)
					d_summary[UPLEFT][FA3] = 1;
			}

			//	*a*ap*`
			if (is_legal(x, y, 4, UPLEFT) && is_legal(x, y, 1, DOWNRIGHT)) {
				if (upleft(1) == CHA_A && upleft(2) == BLANK && upleft(3) == CHA_A && upleft(4) == BLANK && upleft(-1) == BLANK)
					d_summary[UPLEFT][FA3] = 1;
			}
			//------------------------------------------------

			//	`*p*aa* 
			if (is_legal(x, y, 4, DOWNRIGHT) && is_legal(x, y, 1, UPLEFT)) {
				if (downright(1) == BLANK && downright(2) == CHA_A && downright(3) == CHA_A && downright(4) == BLANK && downright(-1) == BLANK)
					d_summary[DOWNRIGHT][FA3] = 1;
			}

			//	` *ap*a* 
			if (is_legal(x, y, 3, DOWNRIGHT) && is_legal(x, y, 2, UPLEFT)) {
				if (downright(1) == BLANK && downright(2) == CHA_A && downright(3) == BLANK && downright(-1) == CHA_A && downright(-2) == BLANK)
					d_summary[DOWNRIGHT][FA3] = 1;
			}

			//	*a*ap*`
			if (is_legal(x, y, 4, DOWNRIGHT) && is_legal(x, y, 1, UPLEFT)) {
				if (downright(1) == CHA_A && downright(2) == BLANK && downright(3) == CHA_A && downright(4) == BLANK && downright(-1) == BLANK)
					d_summary[DOWNRIGHT][FA3] = 1;
			}
		}

		//p*aaa
		if (is_legal(x, y, 4, UP)) {
			if (up(1) == BLANK && up(2) == CHA_A && up(3) == CHA_A && up(4) == CHA_A)
				d_summary[UP][SA4]++;
		}
		if (is_legal(x, y, 4, DOWN)) {
			if (down(1) == BLANK && down(2) == CHA_A && down(3) == CHA_A && down(4) == CHA_A)
				d_summary[DOWN][SA4]++;
		}
		if (is_legal(x, y, 4, LEFT)) {
			if (left(1) == BLANK && left(2) == CHA_A && left(3) == CHA_A && left(4) == CHA_A)
				d_summary[LEFT][SA4]++;
		}
		if (is_legal(x, y, 4, RIGHT)) {
			if (right(1) == BLANK && right(2) == CHA_A && right(3) == CHA_A && right(4) == CHA_A)
				d_summary[RIGHT][SA4]++;
		}
		if (is_legal(x, y, 4, UPLEFT)) {
			if (upleft(1) == BLANK && upleft(2) == CHA_A && upleft(3) == CHA_A && upleft(4) == CHA_A)
				d_summary[UPLEFT][SA4]++;
		}
		if (is_legal(x, y, 4, UPRIGHT)) {
			if (upright(1) == BLANK && upright(2) == CHA_A && upright(3) == CHA_A && upright(4) == CHA_A)
				d_summary[UPRIGHT][SA4]++;
		}
		if (is_legal(x, y, 4, DOWNLEFT)) {
			if (downleft(1) == BLANK && downleft(2) == CHA_A && downleft(3) == CHA_A && downleft(4) == CHA_A)
				d_summary[DOWNLEFT][SA4]++;
		}
		if (is_legal(x, y, 4, DOWNRIGHT)) {
			if (downright(1) == BLANK && downright(2) == CHA_A && downright(3) == CHA_A && downright(4) == CHA_A)
				d_summary[DOWNRIGHT][SA4]++;
		}


	}
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
			if (upleft(1) == CHA_A && upleft(2) == CHA_A && upleft(3) == CHA_A && upleft(4) == BLANK && upleft(-1) == BLANK)
				summary[F4]++;
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
	//-------------------------------------------------------------------------------
	{//`baaap*`
	if (is_legal(x, y, 4, UP) && is_legal(x, y, 1, DOWN)) {
		if (up(1) == CHA_A && up(2) == CHA_A && up(3) == CHA_A && up(4) == CHA_B && up(-1) == BLANK)
			d_summary[UP][SA4]++;
	}

	//`baapa*`
	if (is_legal(x, y, 3, UP) && is_legal(x, y, 2, DOWN)) {
		if (up(1) == CHA_A && up(2) == CHA_A && up(3) == CHA_B && up(-1) == CHA_A && up(-2) == BLANK)
			d_summary[UP][SA4]++;
	}
	///------------------------------------------------
	if (is_legal(x, y, 4, DOWN) && is_legal(x, y, 1, UP)) {
		if (down(1) == CHA_A && down(2) == CHA_A && down(3) == CHA_A && down(4) == CHA_B && down(-1) == BLANK)
			d_summary[DOWN][SA4]++;
	}

	//`baapa*`
	if (is_legal(x, y, 3, DOWN) && is_legal(x, y, 2, UP)) {
		if (down(1) == CHA_A && down(2) == CHA_A && down(3) == CHA_B && down(-1) == CHA_A && down(-2) == BLANK)
			d_summary[DOWN][SA4]++;
	}
	//---///------------------------------------------
	if (is_legal(x, y, 4, LEFT) && is_legal(x, y, 1, RIGHT)) {
		if (left(1) == CHA_A && left(2) == CHA_A && left(3) == CHA_A && left(4) == CHA_B && left(-1) == BLANK)
			d_summary[LEFT][SA4]++;
	}

	//`baapa*`
	if (is_legal(x, y, 3, LEFT) && is_legal(x, y, 2, RIGHT)) {
		if (left(1) == CHA_A && left(2) == CHA_A && left(3) == CHA_B && left(-1) == CHA_A && left(-2) == BLANK)
			d_summary[LEFT][SA4]++;
	}
	//----------------------------
	if (is_legal(x, y, 4, RIGHT) && is_legal(x, y, 1, LEFT)) {
		if (right(1) == CHA_A && right(2) == CHA_A && right(3) == CHA_A && right(4) == CHA_B && right(-1) == BLANK)
			d_summary[RIGHT][SA4]++;
	}

	//`baapa*`
	if (is_legal(x, y, 3, RIGHT) && is_legal(x, y, 2, LEFT)) {
		if (right(1) == CHA_A && right(2) == CHA_A && right(3) == CHA_B && right(-1) == CHA_A && right(-2) == BLANK)
			d_summary[RIGHT][SA4]++;
	}
	//----------------------------
	if (is_legal(x, y, 4, UPLEFT) && is_legal(x, y, 1, DOWNRIGHT)) {
		if (upleft(1) == CHA_A && upleft(2) == CHA_A && upleft(3) == CHA_A && upleft(4) == CHA_B && upleft(-1) == BLANK)
			d_summary[UPLEFT][SA4]++;
	}

	//`baapa*`
	if (is_legal(x, y, 3, UPLEFT) && is_legal(x, y, 2, DOWNRIGHT)) {
		if (upleft(1) == CHA_A && upleft(2) == CHA_A && upleft(3) == CHA_B && upleft(-1) == CHA_A && upleft(-2) == BLANK)
			d_summary[UPLEFT][SA4]++;
	}
	//---------------------------
	if (is_legal(x, y, 4, UPRIGHT) && is_legal(x, y, 1, DOWNLEFT)) {
		if (upright(1) == CHA_A && upright(2) == CHA_A && upright(3) == CHA_A && upright(4) == CHA_B && upright(-1) == BLANK)
			d_summary[UPRIGHT][SA4]++;
	}

	//`baapa*`
	if (is_legal(x, y, 3, UPRIGHT) && is_legal(x, y, 2, DOWNLEFT)) {
		if (upright(1) == CHA_A && upright(2) == CHA_A && upright(3) == CHA_B && upright(-1) == CHA_A && upright(-2) == BLANK)
			d_summary[UPRIGHT][SA4]++;
	}
	//-----------------------
	if (is_legal(x, y, 4, DOWNRIGHT) && is_legal(x, y, 1, UPLEFT)) {
		if (downright(1) == CHA_A && downright(2) == CHA_A && downright(3) == CHA_A && downright(4) == CHA_B && downright(-1) == BLANK)
			d_summary[DOWNRIGHT][SA4]++;
	}

	//`baapa*`
	if (is_legal(x, y, 3, DOWNRIGHT) && is_legal(x, y, 2, UPLEFT)) {
		if (downright(1) == CHA_A && downright(2) == CHA_A && downright(3) == CHA_B && downright(-1) == CHA_A && downright(-2) == BLANK)
			d_summary[DOWNRIGHT][SA4]++;
	}
	//------------------------
	if (is_legal(x, y, 4, DOWNLEFT) && is_legal(x, y, 1, UPRIGHT)) {
		if (downleft(1) == CHA_A && downleft(2) == CHA_A && downleft(3) == CHA_A && downleft(4) == CHA_B && downleft(-1) == BLANK)
			d_summary[DOWNLEFT][SA4]++;
	}

	//`baapa*`
	if (is_legal(x, y, 3, DOWNLEFT) && is_legal(x, y, 2, UPRIGHT)) {
		if (downleft(1) == CHA_A && downleft(2) == CHA_A && downleft(3) == CHA_B && downleft(-1) == CHA_A && downleft(-2) == BLANK)
			d_summary[DOWNLEFT][SA4]++;
	}

	}
	//------------------------------------------------------------------------
	if (d_summary[DOWN][FA3])d_summary[UP][FA3] = 0;
	if (d_summary[LEFT][FA3])d_summary[RIGHT][FA3] = 0;
	if (d_summary[UPLEFT][FA3])d_summary[DOWNRIGHT][FA3] = 0;
	if (d_summary[UPRIGHT][FA3])d_summary[DOWNLEFT][FA3] = 0;
	if (d_summary[DOWN][SA4])d_summary[UP][SA4] = 0;
	if (d_summary[LEFT][SA4])d_summary[RIGHT][SA4] = 0;
	if (d_summary[UPLEFT][SA4])d_summary[DOWNRIGHT][SA4] = 0;
	if (d_summary[UPRIGHT][SA4])d_summary[DOWNLEFT][SA4] = 0;
	int
		free3 = summary[F3],
		freeA3 = d_summary[UP][FA3] + d_summary[DOWN][FA3] + d_summary[LEFT][FA3] + d_summary[RIGHT][FA3]
		+ d_summary[UPRIGHT][FA3] + d_summary[UPLEFT][FA3] + d_summary[DOWNRIGHT][FA3] + d_summary[DOWNLEFT][FA3],
		sleepA4 = d_summary[UP][SA4] + d_summary[DOWN][SA4] + d_summary[LEFT][SA4] + d_summary[RIGHT][SA4]
		+ d_summary[UPRIGHT][SA4] + d_summary[UPLEFT][SA4] + d_summary[DOWNRIGHT][SA4] + d_summary[DOWNLEFT][SA4],
		win4 = summary[F4],
		win5 = summary[WIN5];

	if (win5)		//		Win5
		return -5;
	if (win4)
		return -4;
	return 0;


}
#endif