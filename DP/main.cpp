
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


int main() {
  int cities = 3;
  int numMonths = 12;
  int opCost[3][12] = {
    {8,3,10,43,15,48,5,40,20,30,28,24},
    {18,1,35,18,10,19,18,10,8,5,8,20},
    {40,5,8,13,21,12,4,27,25,10,5,15}
  };
  int relCost[3][3] = {
    {0,20,15},
    {20,0,10},
    {15,10,0}
  };
  int solnCost[3][12];
  int traceBack[3][12];
  for(int i = 0; i < numMonths; ++i){
    for(int j=0; j < cities; ++j){
      int min = 100000;
      int chosenCity = 9;
      for(int k=0; k < cities; ++k){
        int cost = relCost[j][k]+opCost[j][i]+solnCost[k][i-1];
        if(cost < min){
          min = cost;
          chosenCity = k;
        }
      }
      solnCost[j][i]=min;
      traceBack[j][i]=chosenCity;

    }

  }

//establish minimium value & return, establish end city
int currCity = 1;
int solnList[12];
solnList[11] = currCity;
for(int j=numMonths-1; j>=0; --j){
  if (traceBack[currCity][j] == 0){
    currCity = 0;
    solnList[j] = currCity;
  }
  if (traceBack[currCity][j] == 1){
    currCity = 1;
    solnList[j] = currCity;
  }
  if (traceBack[currCity][j] == 2){
    currCity = 2;
    solnList[j] = currCity;
  }
}

int minCost = solnCost[0][numMonths - 1];
for (int i = 0; i < cities; i++){
  if (solnCost[i][numMonths - 1] < minCost) {
    minCost = solnCost[i][numMonths - 1];
  }
}

cout << minCost << endl;

for(int i = 0; i <numMonths; ++i){
  if (solnList[i] == 0){
    cout << "NY ";
  }
  if (solnList[i] == 1){
    cout << "LA ";
  }
  if (solnList[i] == 2){
    cout << "DEN ";
  }
}
/*
cout << endl << endl;
for(int i =0; i <cities; ++i){
  for(int j=0; j<numMonths; ++j){
    cout << traceBack[i][j] << ", ";
  }
  cout << endl;
}
cout << endl << endl;
for(int i =0; i <cities; ++i){
  for(int j=0; j<numMonths; ++j){
    cout << solnCost[i][j] << ", ";
  }
  cout << endl;
}
*/
  cout << endl;
 return 0;
}
