#ifndef CHESS_H_
#define CHESS_H_
#include <string>
#include <iostream>
#include <algorithm>
#include <stack>
#include <ctime>
using namespace std;

#define DEFAULT_OPT 4008123
#define BLACK 1
#define WHITE 2
#define BLANK 0

#define DEPTH 5
#define VCFDEPTH 40
#define MAX_BOUND 14
#define MIN_BOUND 0

#define SUCCESS 0
#define INPUT_ERROR 1

#define INF 1999999999
typedef const int(* MAP)[15];
struct point {
	int x, y;
	int value;
public:
	void change_value(int);
	point(int x, int y) :x(x), y(y) {}
	point(int x, int y, int val) :x(x), y(y), value(val) {}
	point() {}
};
class ChessMap {
private:
	int chessMap[15][15];
	int presentColor;
	int myHand;
	int total_move;
	void change_present_color();
	stack<point>map_stack;
	bool ifFirstHand;
	int legalmove[15][15];
	//
public:	
	void const judge(int i, int j) const;
	ChessMap();
	ChessMap(int my_color);
	ChessMap(int(*map)[15]);
	void print_chess();
	MAP get_chessmap();
	MAP get_legalmove();
	void show_chess();
	int take_a_step(int x, int y);
	int undo_a_step(int, int);
	int undo_a_step();
	int get_myhand();
	void print_history();
};



inline bool check(int x, int y);
int findneibour_point_update(const int(*map)[15], ChessMap&chess, point* point_list,int depth);

int evaluate_point_impliment(const int(*map)[15], int x, int y,bool );
int evaluate_double_F3_white(const int(*map)[15], int x, int y);
int evaluate_double_F3_black(const int(*map)[15], int x, int y);

bool point_cmp_even(point a, point b);
bool point_cmp_odd(point a, point b);

int Evaluate_point(ChessMap &chess, int x, int y);
int AlphaBetasearch_update(ChessMap & chess, int depth, int alpha, int beta);
int AlphaBetasearch_update(ChessMap & chess, int depth, int alpha, int beta, int value); // µ„π¿÷µ

point root_AlphaBetasearch(ChessMap&chess, int depth);

int move_generator(const int(*map)[15], ChessMap&chess, point* point_list, int depth);
point MaxCheckmate(ChessMap &chess,int depth);
point MinCheckmate(ChessMap & chess, int depth);

#endif
