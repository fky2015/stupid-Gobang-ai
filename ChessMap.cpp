#include "ChessMap.h"
#include <cstring>
#include <iostream>
#include <cstdio>
using namespace std;

//  ��CMD�ϴ�ӡ���  TODO

void  ChessMap::print_chess() {
	/*for (int i = 0; i < 16; i++)
	{
		if (i == 0)
		{
			printf("  ");
			for (int j = 1; j < 16; j++)
				printf("%-2d", j);
			printf("\n");
			continue;
		}
		for (int j = 0; j < 16; j++)
		{
			if (j == 0)
			{
				printf("%2d", i);
				continue;
			}

			if (chessMap[i][j] == 1)
				printf("��");
			else if (chessMap[i][j] == 2)
				printf("��");
			else
			{
				judge(i,j);
			}
		}
		printf("\n");
	}
*/
	cout << "   ";
	for (int i = 0; i < 15; i++) {
		printf("%3d", i + 1);
	}
	cout << endl;
	if (myHand == BLACK)
	{
		for (int i = 0; i < 15; i++) {
			printf("%3d  ", i + 1);
			for (int j = 0; j < 15; j++) {
				char output = this->chessMap[i][j];
				output = output ? (output == BLACK ? 'b' : 'w') : '.';
				cout << output << "  ";
			}
			cout << endl;
		}
		cout << endl;
	}
	else {
		for (int i = 0; i < 15; i++) {
			printf("%3d  ", i + 1);
			for (int j = 0; j < 15; j++) {
				char output = this->chessMap[i][j];
				output = output ? (output == BLACK ? 'w' : 'b') : '.';
				cout << output << "  ";
			}
			cout << endl;
		}
		cout << endl;
	}
	cout << "�ܲ���: " << this->total_move<<endl;
}

//  ������ֵ����ã�
MAP ChessMap::get_chessmap() {
	return this->chessMap;
}

//	���ؿ����з�������
MAP ChessMap::get_legalmove() {
	return this->legalmove;
}

void ChessMap::show_chess()
{
}

//  ��������ĺ���������һ����,
int ChessMap::take_a_step(int x, int y) {
	//  ���Բ�����Խ���飬�����ϲ�ʵ��
	if (this->chessMap[x][y] != BLANK) {
		//cout << "����������" << x+1 << "��" << y+1 << "��" << endl;
		return INPUT_ERROR;
	}
	
	this->chessMap[x][y] = presentColor;
	map_stack.push(point(x, y));
	this->change_present_color();
	this->total_move++;
	return SUCCESS;
}


//  Ĭ�Ϲ��캯��
ChessMap::ChessMap() {
	memset(this->chessMap, 0, sizeof(this->chessMap));
	this->presentColor = BLACK;
	this->myHand = BLACK;
	this->total_move = 0;
	ifFirstHand = true;
}

ChessMap::ChessMap(int my_color) {
	memset(this->chessMap, 0, sizeof(this->chessMap));
	this->presentColor = BLACK;
	//this->myHand = (my_color == BLACK) ? BLACK : WHITE;
	this->myHand = BLACK;
	this->total_move = 0;
	ifFirstHand = (my_color == WHITE) ? 0 : 1;
}

ChessMap::ChessMap(int(*map)[15])
{
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			chessMap[i][j] = map[i][j];
		}
	}
	this->presentColor = BLACK;
	this->myHand = BLACK;
	this->total_move = 0;
	ifFirstHand = true;
}



int ChessMap::undo_a_step(int x, int y) {
	//  ���Բ������κμ�飬�����ϲ�ʵ��
	if (this->chessMap[x][y] == BLANK) {
		cout << "û��������" << x + 1 << "��" << y + 1 << "��" << endl;
		return INPUT_ERROR;
	}
	this->chessMap[x][y] = BLANK;
	this->change_present_color();
	this->map_stack.pop();
	this->total_move--;
	return SUCCESS;
}

int ChessMap::undo_a_step() {
	//  ���Բ������κμ�飬�����ϲ�ʵ��
	if (map_stack.empty())return INPUT_ERROR;
	point t = map_stack.top();
	map_stack.pop();
	if (this->chessMap[t.x][t.y] == BLANK) {
		cout << "û��������" << t.x + 1 << "��" << t.y + 1 << "��" << endl;
		return INPUT_ERROR;
	}
	this->chessMap[t.x][t.y] = BLANK;
	this->change_present_color();
	this->total_move--;
	return SUCCESS;
}

int ChessMap::get_myhand()
{
	return myHand;
}

void ChessMap::print_history()
{
	cout <<"--------------------------"<< endl;
	stack<point> temp;
	point t;
	while ( ! map_stack.empty()) {
		t = map_stack.top();
		map_stack.pop();
		temp.push(t);
	}
	while (!temp.empty()) {
		t = temp.top();
		temp.pop();
		cout << t.x + 1 << " " << t.y + 1 << endl;
		map_stack.push(t);
	}
	cout << "--------------------------" << endl;

	return;
}

void ChessMap::change_present_color() {
	this->presentColor = (this->presentColor == BLACK) ? WHITE : BLACK;
}

void const ChessMap::judge(int i, int j)const
{
	if (i == 1 && j == 1)
		printf("�X");
	else if (i == 1 && j == 15)
		printf("�[");
	else if (i == 15 && j == 1)
		printf("�^");
	else if (i == 15 && j == 15)
		printf("�a");
	else if (i == 1 && j != 15 && j != 1)
		printf("��");
	else if (i == 15 && j != 15 && j != 1)
		printf("��");
	else if (j == 1 && i != 15 && i != 1)
		printf("��");
	else if (j == 15 && i != 15 && i != 1)
		printf("��");
	else
		printf("��");
	return;
}