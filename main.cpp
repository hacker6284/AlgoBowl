#include "job.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void algoBowlInput();

int main() {
  cout << "Hello, world!" << endl;
  algoBowlInput();
  return 0;
}

//generate random input files
void algoBowlInput(){
    int n, startTime, station1, station2, station3;
    int m(3);
    string fn;
    srand(time(NULL));
    
    cout << "enter name for input file" << endl;
    cin >> fn;
    
    n = rand() % 1000;
    
    ofstream fout;
    fout.open(fn + ".txt");
    if (!fout.is_open()) cout << "Error opening output file" << endl;
    
    fout << n <<  " " << m;
    
    for(int k = 0; k < n; k++){
        startTime = rand() % 50;            //start time can range from zero to fifty
        station1 = (rand() % 50) + 1;       //add 1 after the modulus to prevent job time of 0
        station2 = (rand() % 50) + 1;
        station3 = (rand() % 50) + 1;
        fout  << '\n' << startTime << " " << station1 << " " << station2 << " " << station3;
    }
    
    fout.close();
}
