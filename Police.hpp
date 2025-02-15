#ifndef POLICE_H
#define POLICE_H

using namespace std;
#include <iostream>
#include <fstream>
#include <vector>
#include "Coordinate.h"
#include "Robber.hpp"



extern const int JEWEL_FACTOR;

class Police {
private:
	int id;
	Coordinate coord;
	static int staticID;
	//int coord[2];
	//int x;
	//int y;
	int count;
	int robbersCaught = 0;
	static int totalCaught;
	static Coordinate direction;

public:
	
	//static int caught;
	void arrest(Robber<Jewel> &r, bool multiple);
	void move();
	Police(int xVal,int yVal);
	void split(Police&other);
	Coordinate getCoord() {return coord;}
	static Coordinate getDirection() { return direction; }
	static void resetDirection() {direction = {-1,-1};}
	int getCount() {return count;}
	int getCaught() {return robbersCaught;}
	int getID() { return id; }
	static bool allArrested();
};



Police::Police(int xVal, int yVal)
{
	id = staticID;
	staticID++;
	coord = {xVal, yVal};
	//coord[0] = rand()%17;
	//coord[1] = rand()%10;

	//x = rand()%17;
	//y = rand()%10;
	count=0;
}

int Police::staticID = 1;
//int Police::caught = 0;
Coordinate Police::direction = {-1,-1};
int Police::totalCaught = 0;


void Police::move()
{
	int r = rand()%8;
	if (direction.x == -1 || (direction.x == coord.x && direction.y == coord.y))
	{
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
  		if (coord.y<17)
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
  		if (coord.x<10)
  	  {
  	    coord.x++;
  	  }
  		else
  		{
  		  coord.x--;
  		}
  	}
	}
	else
	{
	  if(direction.x > coord.x)
	  {
	    coord.x++;
	  }
	  else if(direction.x < coord.x)
	  {
	    coord.x--;
	  }
	  if(direction.y > coord.y)
	  {
	    coord.y++;
	  }
	  else if(direction.y < coord.y)
	  {
	    coord.y--;
	  }
	}
}


void Police::arrest(Robber<Jewel> &r, bool multiple = false)
{
	Jewel j;
	if(multiple)
	{
	  while(r.getCount()>0)
  	{
  		j = r--;
  		j*=JEWEL_FACTOR;
  		count+=j.getValue();
  	}
	}
	else
	{
  	while(r.getCount()>0)
  	{
  		j = r--;
  		j = j*JEWEL_FACTOR;
  		count+=j.getValue();
  	}
	}
	r.setActive(false);
	robbersCaught++;
	totalCaught++;
}


void Police::split(Police & other)
{
	int avg = (count + other.count)/2;
	count = avg;
	other.count = avg;
}

bool Police::allArrested()
{
  bool result = false;
  if (totalCaught == Robber<Jewel>::getNoRobbers())
  {
    result = true;
  }
  return result;
}



#endif