#ifndef DRONE_H
#define DRONE_H

using namespace std;
#include <iostream>
#include <fstream>
#include <vector>

class Drone
{
private:
	int id;
	Coordinate coord;
	//int coord[2];
	//int x;
	//int y;
	static int staticID;

public:
	
	void move();
	void scan(vector<Robber<Jewel>> &arr);
	Drone(int xVal, int yVal);
	Coordinate getCoord() {return coord;}
};




Drone::Drone(int xVal, int yVal)
{
	id = staticID;
	staticID++;
	coord = {xVal, yVal};
	//coord[0] = rand()%17;
	//coord[1] = rand()%10;

	//x = rand()%17;
	//y = rand()%10;
}

int Drone::staticID = 0;

void Drone::move()
{
	int r = rand()%8;
	if (r<3)
	{
	  if (coord.y>0)
	  {
	    coord.y--;
	  }
		else
		{
		  coord.y++;
		}
	}
	else if(r>4)
	{
		if (coord.y<9)
	  {
	    coord.y++;
	  }
		else
		{
		  coord.y--;
		}
	}
	if (r == 0 || r == 3 || r == 5)
	{
		if (coord.x>0)
	  {
	    coord.x--;
	  }
		else
		{
		  coord.x++;
		}
	}
	else if (r == 2 || r == 4 || r == 7)
	{
		if (coord.x<16)
	  {
	    coord.x++;
	  }
		else
		{
		  coord.x--;
		}
	}
}

void Drone::scan(vector<Robber<Jewel>> &arr)
{
	Coordinate tester = {0,coord.y};

	for(int i = 0; i < 17; i++)
	{
		tester.x = i;
		for(int k = 0; k < Robber<Jewel>::getNoRobbers(); k++)
		{
			if (tester == arr[k].getCoord() && arr[k].getActive() && Police::getDirection().x == -1)
			{
				Police::getDirection() = arr[k].getCoord();;
			}
		}
	}
	tester = {coord.x,0};
	for(int i = 0; i < 10; i++)
	{
		tester.y = i;
		for(int k = 0; k < Robber<Jewel>::getNoRobbers(); k++)
		{
			if (tester == arr[k].getCoord() && arr[k].getActive()&& (Police::getDirection().x == -1))
			{
				Police::getDirection() = arr[k].getCoord();;
			}
		}
	}

}


#endif