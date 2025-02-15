#ifndef CITY_H
#define CITY_H

using namespace std;
#include <iostream>
#include <fstream>
#include <fstream>
#include <vector>
#include "Jewel.hpp"
#include "Robber.hpp"
#include "Police.hpp"
#include "Drone.hpp"
#include "Coordinate.h"

//const int JEWEL_FACTOR = 2;

class City
{
private:
	char grid[17][10];
	int count = 0;
	//int robberCount = 4;
	int turnCount = 0;
	bool usingDrones;
	vector <Jewel> jVect;
	vector <Robber<Jewel>> rVect;
	vector <Police> pVect;
	vector <Drone> dVect;

public:
	City(bool usingDrones);
	string print();
	void defaultArr();
	void updateGrid();
	void turn();
	void robberTurn(Robber<Jewel>&rObj, int index);
	void newRobber(Robber<Jewel>&other);
	void trip(Robber<Jewel>&other);
	void loseHalf(Robber <Jewel>&other);
	string gameSummary();

};

City::City(bool usingDrones)
{
  this->usingDrones = usingDrones;
	defaultArr();
	int x = -1;
	int y = -1;
	int value = 0;
	//initalizing jewels
	for(int i = 0; i < 70; i++)
	{
		x = -1;
		while(x == -1)
		{
			x = rand()%17;
			y = rand()%10;
			if(grid[x][y] == ' ')
			{
				grid[x][y] = 'j';
				value = (x + y)*(x+y);
				jVect.push_back(Jewel(value,x,y));
				count++;
			}
			else
			{
				x = -1;
			}
		}
	}
	//initializing police
	for(int i = 0; i < 3; i++)
	{
		x = -1;
		while(x == -1)
		{
			x = rand()%17;
			y = rand()%10;
			if(grid[x][y] == ' ')
			{
				grid[x][y] = 'p';
				//value = (x + y)*(x+y);
				pVect.push_back(Police(x,y));
				//count++;
			}
			else
			{
				x = -1;
			}
		}
	}

	//initializing drone
	if(usingDrones)
	{
	  for(int i = 0; i < 3; i++)
  	{
  		x = -1;
  		while(x == -1)
  		{
  			x = rand()%17;
  			y = rand()%10;
  			if(grid[x][y] == ' ')
  			{
  				grid[x][y] = 'd';
  				//value = (x + y)*(x+y);
  				dVect.push_back(Drone(x,y));
  				//count++;
  			}
  			else
  			{
  				x = -1;
  			}
  		}
  	}
	}

	//initializing robbers
	for(int i = 0; i < 4; i++)
	{
		x = -1;
		while(x == -1)
		{
			x = rand()%17;
			y = rand()%10;
			if(grid[x][y] == ' ')
			{
				grid[x][y] = 'r';
				value = (x + y)*(x+y);
				if (i < 2)
				{
					rVect.push_back(Robber<Jewel>(x,y,true));
				}
				else
				{
					rVect.push_back(Robber<Jewel>(x,y,false));
				}
				//count++;
			}
			else
			{
				x = -1;
			}
		}
	}
}


string City::print()
{
  string result ="";
	for (int i = 0; i < 10; i++)
	{
		for (int k = 0; k < 17; k++)
		{
			result+=grid[k][i];
		}
		result+="\n";
	}
	//cout<<count<<endl;
	result+="----------------------\n";
	return result;
}

void City::defaultArr()
{

	for (int i = 0; i < 17; i++)
	{
		for (int k = 0; k < 10; k++)
		{
			grid[i][k] = ' ';
		}
	}

}


void City::updateGrid()
{
  defaultArr();
  for (int i = 0; i < 17; i++)
	{
		for (int k = 0; k < 10; k++)
		{
			grid[i][k] = ' ';
		}
	}
  
  for(int i = 0; i < count; i++)
  {
    grid[jVect[i].getCoord().x][jVect[i].getCoord().y] = 'j';
  }
  for(int i = 0; i < 3; i++)
	{
	  if(usingDrones)
	  {
	    grid[dVect[i].getCoord().x][dVect[i].getCoord().y] = 'd';
	  }
	  
	  grid[pVect[i].getCoord().x][pVect[i].getCoord().y] = 'p';
	}
	for (int i = 0; i < Robber<Jewel>::getNoRobbers(); i ++)
	{
		if(!rVect[i].getActive())
		{
			grid[rVect[i].getCoord().x][rVect[i].getCoord().y] = 'A';
		}
		else
		{
		  grid[rVect[i].getCoord().x][rVect[i].getCoord().y] = 'r';
		}
	}
	
	
	for (int i = 0; i < 2; i ++)
	{
		for (int k = i+1; k < 3; k++)
		{
			if(pVect[i].getCoord()==pVect[k].getCoord())
			{

				grid[pVect[i].getCoord().x][pVect[i].getCoord().y] = 'P';
			}
		}
	}
	for (int i = 0; i < Robber<Jewel>::getNoRobbers()-1; i++)
	{
		for (int k = i+1; k < Robber<Jewel>::getNoRobbers(); k++)
		{
			if(rVect[i].getCoord()==rVect[k].getCoord())
			{
			  
				grid[rVect[i].getCoord().x][rVect[i].getCoord().y] = 'R';
			}
		}
	}
	for(int i = 0; i < 3; i++)
	{
		for(int k = 0; k < Robber<Jewel>::getNoRobbers(); k++)
		{
			if(pVect[i].getCoord()==rVect[k].getCoord())
			{
				grid[rVect[k].getCoord().x][rVect[k].getCoord().y] = 'Q';
			}
		}
	}
}

void City::turn()
{
  //int turnCount = 0;
  int arrests = 0;
  //bool foundLoot = false;
  bool foundCop = true;
  vector <int> arrestsInd;
  //robbers turn
  //greedy robbers
  for (int i = 0; i < Robber<Jewel>::getNoRobbers(); i ++)
  {
    if(rVect[i].getGreedy())
    {
      robberTurn(rVect[i],i);
    }
  }
  for (int i = 0; i < Robber<Jewel>::getNoRobbers(); i ++)
  {
    if(rVect[i].getGreedy()==false)
    {
      robberTurn(rVect[i],i);
    }
  }
  
	
  //police turn
  for(int i = 0; i < 3; i++)
	{
	  foundCop = true;
	  while(foundCop)
	  {
	    foundCop = false;
	    //cout<<pVect[i].getCoord().x<<' '<<pVect[i].getCoord().y<<endl;
  	  pVect[i].move();
  	  //cout<<pVect[i].getCoord().x<<' '<<pVect[i].getCoord().y<<endl;
  	  for(int k = 0; k < count; k++)
  	  {
  	    if(jVect[k].getCoord()==pVect[i].getCoord())
  	    {
  	      jVect.erase(jVect.begin()+k);
  	      k--;
  	      count--;
  	    }
  	  }
  	  
  	  //cout<<arrests<<endl;
  	  //cout<<robberCount<<endl;
  	  for(int j = 0; j < Robber<Jewel>::getNoRobbers(); j++)
  	    {
  	      if(pVect[i].getCoord()==rVect[j].getCoord())
  	      {
  	        //arrestVect.push_back(rVect[j]);
  	        if(rVect[j].getActive())
  	        {
  	          //cout<<i<<endl;
  	          //pVect[i].arrest(rVect[j],1);
    	        arrestsInd.push_back(j);
    	        arrests++;
  	        }
  	      }
  	    }
  	  for(int j = 0; j < arrests; j++)
  	    {
  	      pVect[i].arrest(rVect[arrestsInd[j]],arrests-1);
  	    }
  	    arrests = 0;
  	    arrestsInd.clear();
  	    
  	    for (int k = 0; k < 3; k++)
  	    {
  	      if (i != k && pVect[i].getCoord()==pVect[k].getCoord())
  	      {
  	        foundCop = true;
  	      }
  	    }
	  }
	}
	Police::resetDirection();
	
	
	//drone turn
	if(usingDrones)
	{
	  for(int i = 0; i < 3; i++)
  	{
  	  dVect[i].move();
  	  dVect[i].scan(rVect);
  	}
	}
}

void City::newRobber(Robber<Jewel>&other)
{
  int x = -1;
  int y = -1;
  
  //robberCount++;
  if(Robber<Jewel>::getNoRobbers() < 25)
  {
    rVect.push_back(Robber<Jewel>(other));
    for(int i = 0; i < 3; i++)
  	{
  		while(x == -1)
  		{
  			x = rand()%17;
  			y = rand()%10;
  			if(grid[x][y] == ' ')
  			{
  				grid[x][y] = 'r';
  				rVect.back().setCoord(x,y);
  				//count++;
  			}
  			else
  			{
  				x = -1;
  			}
  		}
  	}
  }
  
}


void City:: loseHalf(Robber<Jewel>&other)
{
  int x =-1;
  int y = -1;
  int half = other.getCount()/2;
  //cout<<half<<endl;
  for(int i = 0; i < half; i ++)
  {
    jVect.push_back(other--);
    x = jVect[count].getOgCoord().x;
    y = jVect[count].getOgCoord().y;
    while(grid[x][y] !=' ')
    {
      x = rand()%17;
      y = rand()%10;
    }
    jVect[count].setCoord(x,y);
    grid[x][y] = 'j';
    count++;
    //cout<<x<<' '<<y<<endl;
  }
}




void City::trip(Robber<Jewel> &other)
{
  int x = other.getCoord().x;
  int y = other.getCoord().y;
  int distance = 1;
  if(other.getCount()>0)
  {
    while(x==other.getCoord().x && y == other.getCoord().y)
    {
      for(int i = 0-distance; i <= distance; i ++)
      {
        for(int k = 0-distance; k <= distance; k++)
        {
          if(x+i >= 0 && x+i <17 && y+k >=0 && y+k < 10 &&grid[x+i][y+k] == ' ' 
          && x==other.getCoord().x && y == other.getCoord().y)
          {
            x += i;
            y += k;
            jVect.push_back(other--);
            jVect[count].setCoord(x,y);
            count++;
          }
        }
      }
      distance++;
    }
  }
}


string City::gameSummary()
{
  string result = "Summary of the chase:\n";
  if(Police::allArrested())
  {
    result+="The police win the chase after arresting all robbers\n";
  }
  else if(Robber<Jewel>::overThreshold())
  {
    result+="The robbers win the chase by bribing the police\n";
  }
  else
  {
    result+="The robbers win the chase because maximum turns have been reached\n";
  }
  
  
  
  
  for(int i = 0; i < 3; i++)
  {
    result+="Police ID: "+to_string(pVect[i].getID())
    +"\n\tConfiscated jewels amount: $"+to_string(pVect[i].getCount())
    +"\n\tFinal number of robbers caught: "+to_string(pVect[i].getCaught()) + "\n";
  }
  for(int i = 0; i < Robber<Jewel>::getNoRobbers(); i ++)
  {
    if(rVect[i].getGreedy())
    {
      result+="Greedy ";
    }
    else
    {
      result+="Ordinary ";
    }
    result+="Robber ID: "+to_string(rVect[i].getID())
    +"\n\tFnal number of jewels: "+to_string(rVect[i].getCount())
    +"\n\tTotal jewel worth: $"+to_string(rVect[i].getBag())+"\n";
  }
  return result;
}

void City::robberTurn(Robber<Jewel>&rObj, int index)
{
  int turnCount = 0;
  bool foundLoot = false;
	  while(turnCount < 3 && rObj.getActive())
	  {
	    foundLoot = false;
	    
  	  if(rObj.getWithoutLoot() < 5)
  	  {
    		rObj.move();
    		//cout<<i<<" moved"<<rVect[i].getCoord().x<<' '<<rVect[i].getCoord().y<<endl;
    		if (rand()%10 < 6 && rObj.getActive())
    		{
    		  //cout<<rVect[i].getBag()<<endl;
    		  trip(rObj);
    		  //cout<<"trip"<<rVect[i].getCoord().x<<' '<<rVect[i].getCoord().y<<endl;
    		}
    		for(int k = 0; k < count; k++)
    	  {
    	    if(jVect[k].getCoord()==rObj.getCoord() && rObj.getCount()<20)
    	    {
    	      rObj.pickUpLoot(jVect[k]);
    	      jVect.erase(jVect.begin()+k);
    	      count--;
    	      k--;
    	      foundLoot = true;
    	    }
    	  }
    	  if(!foundLoot)
    	  {
    	    turnCount = 3;
    	    rObj.setWithoutLoot();
    	  }
    	  if(rObj.getGreedy())
    	  {
    	    for(int k = 0; k < Robber<Jewel>::getNoRobbers(); k++)
      	  {
      	    if(index!=k && rObj.getCoord()==rVect[k].getCoord() && rVect[k].getActive())
      	    {
      	      loseHalf(rObj);
      	    }
      	  }
    	  }
    	  if(rObj.getBag()>=400 && rObj.getSpawn())
    	  {
    	    newRobber(rObj);
    	  }
  	  }
  	  else if(rObj.getWithoutLoot()<7)
  	  {
  	    rObj.setWithoutLoot();
  	  }
  	  else
  	  {
  	    rObj.setWithoutLoot(0);
  	  }
  	 turnCount++;
  	 foundLoot = false;
	  }
	
}

#endif