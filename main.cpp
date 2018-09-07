#include "ChessMap.h"
#include <cstring>
#include <iostream>
#include <stack>
#include <cstdlib>

using namespace std;
ChessMap che;



int main()
{

	che.take_a_step(13, 7);

	che.print_chess();
	while (true) {
		cout << "请输入一个坐标" << endl;
		int x, y;
		cin >> x >> y;
		if (!cin.fail())
		{
			if (x == 0 && y >= 0) //	undo function
			{
				if (y == 0) {
					che.undo_a_step();
					che.print_chess();
				}
				else {
					while (y--) {
						che.undo_a_step();
						
					}
					che.print_chess();
				}
				continue;
			}
			else if (x == 0 && y == -1) {
				che.print_history();
			}
			if (x <= 0 || y <= 0 || x > 15 || y > 15)
			{
				cout << "请输入正确的坐标\n";
				continue;
			}
			if (che.take_a_step(x - 1, y - 1) == SUCCESS)
			{
			cout << "result: " << Evaluate_point(che,x-1,y-1) << endl;


			/*
			DWORD t1,t2;
			t1 = timeGetTime();
			foo();//dosomething
			t2 = timeGetTime();
			printf("Use Time:%f\n",(t2-t1)*1.0/1000);
			*/
				long long  t_start, t_end;
				t_start = clock();
				//	AI------start---------------
				point bestmove = root_AlphaBetasearch(che, DEPTH);
				che.take_a_step(bestmove.x,bestmove.y);
				che.print_chess();

				t_end = clock();
				cout << '(' << bestmove.x + 1 << ',' << bestmove.y + 1 << ')' << endl;
				cout << "value = " << bestmove.value << endl;
				//	AI-------end---------------

				cout <<"time spent: "<<( t_end - t_start )<<"ms"<< endl;
			}
		}
		else {
			cout << "输入类型错误，程序即将退出\n\n\n";
			system("pause");
			return 0;
		}
	}
}
	


