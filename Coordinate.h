#ifndef COORDINATE_H
#define COORDINATE_H

using namespace std;
#include <iostream>
#include <fstream>
#include <fstream>
#include <vector>

struct Coordinate
{
	int x;
	int y;
};

bool operator==(const Coordinate& left, const Coordinate& right)
{
	bool result = false;
	if (left.x == right.x && left.y == right.y)
	{
		result = true;
	}
	return result;

}


#endif