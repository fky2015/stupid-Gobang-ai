#include "ChessMap.h"

#define WIN 5
#define LOSE -5
#define UNFIND 0
//		 所有的输赢都是相对于AI来讲的
int move_generator(const int(*map)[15], ChessMap & chess, point * point_list, int depth)
{
	int num = 0;
	if ((DEPTH + 200 - depth) & 1) {	//		对方回合
		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 15; j++) {
				if (map[i][j])
					continue;
				int ret1 = evaluate_double_F3_black(chess.get_chessmap(), i, j);
				int ret2 = evaluate_double_F3_white(chess.get_chessmap(), i, j);
				if (ret2 == LOSE) {

					point_list[0].x = i;
					point_list[0].y = j;
					point_list[0].value = LOSE;
					return 1;		//		此时白方已经赢了
				}
				else if (ret1 == 5 || ret2) {	// 白方要走黑房要成5或者   白方要成5 的地方(白方已经胜利，因为这部该白方下）
					point_list[num].x = i;
					point_list[num].y = j;
					point_list[num].value = 5;
					num++;
				}
			}
		}
		sort(point_list, point_list + num, point_cmp_odd);
	}
	else {
		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 15; j++) {
				if (map[i][j])
					continue;
				int ret1 = evaluate_double_F3_black(chess.get_chessmap(), i, j);

				if (!ret1) continue;
				else {
					point_list[num].x = i;
					point_list[num].y = j;
					point_list[num].value = ret1;
					num++;
				}
			}
		}
		sort(point_list, point_list + num, point_cmp_even); // 解决了最短路径的问题
	}
	return num;
}

point MaxCheckmate(ChessMap & chess, int depth)
{
	point best, temp;
	if (depth <= 0)return point(UNFIND, UNFIND, UNFIND);
	point movelist[100];

	int lenofmovelist = move_generator(chess.get_chessmap(), chess, movelist, depth);
	for (int i = 0; i < lenofmovelist; i++) {		//		便利极大优势点
		int x = movelist[i].x, y = movelist[i].y;

		if (movelist[i].value == WIN)
			return movelist[i];
		chess.take_a_step(x, y);

		temp = MinCheckmate(chess, depth - 1);

		chess.undo_a_step();
		if (temp.value == LOSE)
			continue;
		if (temp.value == WIN) {
			return point(x, y, 5);
		}
	}
	return point(0, 0, LOSE);
}

point MinCheckmate(ChessMap & chess, int depth)
{
	point best(0, 0, 0), temp;
	if (depth <= 0)return point(0, 0, 0);
	point movelist[100];
	int lenofmovelist = move_generator(chess.get_chessmap(), chess, movelist, depth);
	//		如果value==5 大于等于两个，黑棋已经赢了，但是还是继续判断一下吧
	for (int i = 0; i < lenofmovelist; i++) {		//		便利极大优势点
		int x = movelist[i].x, y = movelist[i].y;
		if (movelist[i].value == LOSE)
			return movelist[i];

		chess.take_a_step(x, y);

		temp = MaxCheckmate(chess, depth - 1);

		chess.undo_a_step();
		if (temp.value == LOSE) continue;
		if (temp.value == WIN)return temp;
		if (temp.value >= best.value)
		{
			best = temp;
		}
	}
	return best;
}
