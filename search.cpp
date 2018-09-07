#include "ChessMap.h"

point root_AlphaBetasearch(ChessMap&chess, int depth) {

	point VCF = MaxCheckmate(chess,VCFDEPTH);
	if (VCF.value == 5) {
		cout << "=v= VCF QAQ" << endl;
		return point(VCF.x, VCF.y, 1234321);
	}
	int max = -2000000000; int max_x_index = 0, max_y_index = 0;
	int alpha = -INF, beta = INF; bool fFoundPv = false; int val = 0;


	//--------------------------------------------------------------------------------------------
	point point_for_search[200];
	int num_of_point_for_search;
	//int neighborhood[15][15] = { 0 };
	//num_of_point_for_search = findneibour_point(che.get_chessmap(), point_for_search);	
	num_of_point_for_search = findneibour_point_update(chess.get_chessmap(), chess, point_for_search, depth);	//		��С����
																									//		�޸�һ�£������е����������������鳤�ȣ������forѭ����Ϊ�������

	const int  total_times = num_of_point_for_search; int count = 0;
	printf("total : %3d\n", total_times);

	//int count_sao = 10; //	ɧ���� 

	for (point*present = point_for_search; present != point_for_search + num_of_point_for_search; present++) {
		//		��ԭ��������forѭ���滻��
		//-------------------------------------------------------------------------------------------
		int i = present->x, j = present->y;
		int present_val;
		if ((DEPTH - depth) & 1) {
			present_val = evaluate_point_impliment(chess.get_chessmap(), i, j, 0);
			//present_val += evaluate_point_impliment(chess.get_chessmap(), i, j, 1)*0.2;
		}
		else {
			present_val = evaluate_point_impliment(chess.get_chessmap(), i, j, 1);
			//present_val += evaluate_point_impliment(chess.get_chessmap(), i, j, 0)*0.2;
		}

		if (present_val >= 5000) {		//			�����ض�
			/*chess.undo_a_step();*/
			return point(i, j, present_val);
		}

		printf("\r%.2f%%", 100.0*(++count) / total_times);
		if (chess.take_a_step(i, j) == SUCCESS) {
			if (fFoundPv) {	//		PVS 
				val = -AlphaBetasearch_update(chess, depth - 1, -alpha - 1, -alpha, -present_val); // PVS
				if ((val > alpha) && (val < beta)) {		// ���ʧ��
					val = -AlphaBetasearch_update(chess, depth - 1, -beta, -alpha, -present_val);	//    
				}
			}
			else
			{
				val = -AlphaBetasearch_update(chess, depth - 1, -beta, -alpha, -present_val);	//	ԭ����
			}
			if (val > max) {			//			depth = 3  ʱ����Ȼ��СֵΪ���Ž�
				max = val;
				max_x_index = i;
				max_y_index = j;
			}
			if (val > alpha) {
				alpha = val;
				fFoundPv = true;
			}
			//	debug use
			cout << '(' << i + 1 << ',' << j + 1 << ")--->" << val << endl;

			chess.undo_a_step(i, j);
		}

	}
	cout << endl;

	return point(max_x_index, max_y_index, val);
}


int AlphaBetasearch_update(ChessMap & chess, int depth, int alpha, int beta, int value)
{

	if (depth == 0) {		//		�ŵ�ǰ�����Ч��
	/*	point VCF = MaxCheckmate(chess, 10);
		if (VCF.value == 5) {
			return 60000;
		}*/
		return value;
	}
	point point_for_search[200];	bool fFoundPv = false; // PVS
	int num_of_point_for_search;

	num_of_point_for_search = findneibour_point_update(chess.get_chessmap(), chess, point_for_search, depth);
	//		�޸�һ�£������е����������������鳤�ȣ������forѭ����Ϊ�������

	//int count_sao =30; //	ɧ���� 
	for (point*present = point_for_search; present != point_for_search + num_of_point_for_search; present++) {

		int i = present->x, j = present->y;
		int val = 0;


		if (chess.take_a_step(i, j) == INPUT_ERROR)
			continue;
		int present_val;
		if ((DEPTH - depth) & 1) {	//	��������
			present_val = evaluate_point_impliment(chess.get_chessmap(), i, j, 0);
			//present_val += evaluate_point_impliment(chess.get_chessmap(), i, j, 1)*0.3;
			if (present_val >= 4320)		//			�����ض�
			{
				chess.undo_a_step();
				return present_val;
			}
		}
		else {	//		�ҷ�����
			present_val = evaluate_point_impliment(chess.get_chessmap(), i, j, 1);
			//present_val += evaluate_point_impliment(chess.get_chessmap(), i, j, 0)*0.3;
			if (present_val >=5000)		//			�����ض�
			{
				chess.undo_a_step();
				return present_val;
			}
		}
		
		
		present_val += value;
		
		if (fFoundPv) {	//		PVS 


			val = -AlphaBetasearch_update(chess, depth - 1, -alpha - 1, -alpha, -present_val); // PVS
			if ((val > alpha) && (val < beta)) {		// ���ʧ��
				val = -AlphaBetasearch_update(chess, depth - 1, -beta, -alpha, -present_val);	//    
			}

		}
		else
		{
			val = -AlphaBetasearch_update(chess, depth - 1, -beta, -alpha, -present_val);	//	ԭ����
		}
		chess.undo_a_step(i, j);
		if (val >= beta) {
			return beta;
		}
		if (val > alpha) {
			alpha = val;
			fFoundPv = true; //		PVS
		}
	}
	return alpha;
}




int findneibour_point_update(const int(*map)[15], ChessMap&chess, point* point_list, int depth) { // ��ǿ�棬����������
	int n = 0;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (map[i][j])
				continue;
			int flag = 0;
			for (int delta_i = -1; delta_i < 2; delta_i++) {			//  ԭ���� [-2,+2]
				for (int delta_j = -1; delta_j < 2; delta_j++) {
					if (!check(i + delta_i, j + delta_j)) {
						continue;
					}
					if (map[i + delta_i][j + delta_j]) {
						point_list[n].x = i;
						point_list[n].y = j;
						point_list[n].value = Evaluate_point(chess, i, j);
						n++;
						goto k;
					}
				}
			}
		k:;
		}
	}

	/*for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			cout << map[i][j] << " ";
		}
		cout << endl;
	}*/
	sort(point_list, point_list + n, point_cmp_even);
	return n;
}



inline bool check(int x, int y) {
	if (x < 0 || y < 0 || x >= 15 || y >= 15)
		return 0;
	return 1;
}