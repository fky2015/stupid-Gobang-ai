#include "ChessMap.h"

void point::change_value(int val) {
	this->value = val;
	return;
}
bool point_cmp_even(point a, point b)
{
	return a.value > b.value;
}
bool point_cmp_odd(point a, point b)
{
	return a.value < b.value;
}