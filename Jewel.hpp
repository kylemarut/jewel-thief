#ifndef JEWEL_H
#define JEWEL_H

using namespace std;
#include <iostream>
#include <fstream>
#include <fstream>
#include <vector>
#include "City.hpp"
#include "Coordinate.h"

class Jewel
{
private:
	int value;
	Coordinate ogCoord;
	Coordinate coord;
	//int coord[2];
	//int x;
	//int y;

public:
	//Jewel();
	Jewel(const int value, const int xPos, const int yPos);
	void operator*=(const int&JEWEL_FACTOR);
	friend Jewel operator*(const Jewel & left, const int&JEWEL_FACTOR);
	int getValue();
	void setCoord(int x, int y);
	Coordinate getCoord() {return coord;}
	Coordinate getOgCoord() { return ogCoord; }
};

void Jewel::setCoord(int x, int y)
{
  coord.x = x;
  coord.y = y;
}



Jewel::Jewel(const int value = 0, const int xPos = rand()%17, const int yPos = rand()%10)
{
	this->value = value;

	coord = {xPos,yPos};
	ogCoord = coord;
	//coord[0] = xPos;
	//coord[1] = yPos;

	//x = xPos;
	//y = yPos;
}

Jewel operator*(const Jewel&left, const int&JEWEL_FACTOR)
{
	Jewel result(left.value*JEWEL_FACTOR,left.coord.x, left.coord.y);

	return result;
}

void Jewel::operator*=(const int&JEWEL_FACTOR)
{
	*this = *this * JEWEL_FACTOR;
}

int Jewel::getValue()
{
	return value;
}

#endif