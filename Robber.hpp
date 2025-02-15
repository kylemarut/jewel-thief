#ifndef ROBBER_H
#define ROBBER_H

using namespace std;
#include <iostream>
#include <fstream>
#include <fstream>
#include <vector>
#include "City.hpp"
#include "Coordinate.h"

template <class T>
class Robber
{
private:
	Coordinate coord;
	//int coord[2];
	//int x;
	//int y;
	T bag[20];
	int count;
	bool active;
	bool greedy;
	int id;
	bool spawn;
	int withoutLoot = 0;
	static int noRobbers;
	static int staticID;
	static int totalCount;
	static int totalValue;


public:
	Robber(int xVal, int yVal, bool greedy);
	Robber(Robber<T>& other);
	Robber(Robber<T>&& other) noexcept;
	void pickUpLoot(T item);
	T operator--(int);
	void move();
	int getCount();
	int getx();
	int gety();
	Coordinate getCoord() {return coord;}
	int getID() {return id;}
	bool getActive() {return active;}
	void setActive(bool val) {active = val;}
	int getBag();
	bool getGreedy() {return greedy;}
	bool getSpawn() {return spawn;}
	int getWithoutLoot() {return withoutLoot; }
	void setWithoutLoot(int i) {withoutLoot = i;}
	void setWithoutLoot() {withoutLoot++;}
	static int getNoRobbers() {return noRobbers;}
	static bool overThreshold();
	

  void setCoord(int x, int y) { coord.x = x; coord.y = y;}
};

template <class T>
int Robber<T>::getBag()
{
  int total = 0;
  for(int i = 0; i < count; i ++)
  {
    total+=bag[i].getValue();
  }
  return total;
}


template <class T>
Robber<T>::Robber(int xVal, int yVal, bool greedy)
{
	id = staticID;
	staticID++;
	noRobbers++;
	spawn = true;

	coord = {xVal, yVal};
	//coord[0] = rand()%17;
	//coord[1] = rand()%10;

	//x = rand()%17;
	//y = rand()%10;
	active = true;
	count = 0;
	this->greedy = greedy;
	/*
	if (rand()%2)
	{
	  greedy = true;
	}
	else
	{
	  greedy = false;
	}*/
}

template <class T>
Robber<T>::Robber(Robber<T>&& other) noexcept {
	id = other.id;
	coord = other.coord;
	count = other.count;
	active = other.active;
	greedy = other.greedy;
	spawn = other.spawn;

	for (int i = 0; i < 20; ++i) {
		bag[i] = std::move(other.bag[i]);
	}

	// Mark the source object as invalid
	other.active = false;
}


template<class T>
Robber<T>::Robber(Robber<T>& other)
{
	//int r;
	id = staticID;
	staticID++;
	noRobbers++;
	spawn = true;
	other.spawn = false;

	coord = other.coord;

	//x = other.x;
	//y = other.y;
	active = other.active;
	greedy = other.greedy;
	count = 0;
	for (int i = 0; i < other.count; i++)
	{
		if (rand()%2)
		{
			bag[count] = other.bag[i];
			count++;
			other.count--;
			for(int k = i; k < other.count; k++)
			{
				other.bag[k] = other.bag[k+1];
			}
		}
	}
	/*
	for(int i = 0; i < 20; i++)
	{
	  r = rand()%2;
	  if (r && other.array[i]!=NULL)
	  {
	    bag[i] = other.bag[i];
	    other.bag[i] = NULL;
	  }
	}*/
}

template<class T>
int Robber<T>::staticID = 1;

template<class T>
int Robber<T>::totalCount = 0;

template<class T>
int Robber<T>::noRobbers = 0;

template<class T>
int Robber<T>::totalValue = 0;

template<class T>
void Robber<T>::pickUpLoot(T item)
{
  if (count<20)
  {
	bag[count] = item;
	count++;
	totalCount++;
	totalValue+=item.getValue();
  }
}


template <class T>
T Robber<T>::operator--(int)
{
	if (count>0)
	{
		count--;
		totalCount--;
		totalValue-=bag[count].getValue();
	}
	return bag[count];
}

template <class T>
void Robber<T>::move()
{

	int r = rand()%8;
	if(active)
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
	/*
	if (r < 6)
	{
		ptr = (*this)--;
	}*/
}

//template <class T>






template <class T>
int Robber<T>::getCount()
{
	return count;
}

template <class T>
int Robber<T>::getx()
{
	return coord.x;
}

template <class T>
int Robber<T>::gety()
{
	return coord.y;
}

template <class T>
bool Robber<T>::overThreshold()
{
  bool result = false;
  if(totalValue >= 5000)
  {
    result = true;
  }
  return result;
}

#endif