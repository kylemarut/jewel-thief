//Programmer: Kyle Marut
//Date: 11-22-24
//File: jewelHeist.cpp
//Assignment: Jewel Heist "Final Programming Project"
//Purpose: this file contains the main function of the program which acts as a sort of cops vs. robbers game across a city grid

using namespace std;
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "City.hpp"
#include "Jewel.hpp"
#include "Robber.hpp"
#include "Police.hpp"
#include "Drone.hpp"
#include "Coordinate.h"

const int JEWEL_FACTOR = 2;

int main()
{
  //ofstream fout("simulation_with_drones.txt");
  ofstream fout("simulation_without_drones.txt");
  srand(time(0));
  
  //City c1(true);
  City c1(false);
  fout<<c1.print();
  int i = 0;
  while (!(Police::allArrested() || Robber<Jewel>::overThreshold()) && i < 100)
  {
    c1.turn();
    c1.updateGrid();
    fout<<endl;
    fout<<c1.print();
    i++;
  }
  
 fout<<"finished after "<<i<<" turns"<<endl;
 fout<<c1.gameSummary();
 fout.close();
 

  
  
  
  return 0;
}
