#include "job.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void algoBowlInput();
bool outputTester();

int main() {
  cout << "Hello, world!" << endl;
  algoBowlInput();
  return 0;
}

//function to test output files

bool outputTester(){
    //TODO: overall completion time >= max(sum job-times at each work station)
    //TODO: job start time at each station >= job available time
    //TODO: job working time at each station is unique, i.e. no overlaps
    
    return true;
}


//generate random input files

void algoBowlInput(){
    int n, startTime, station1, station2, station3;
    int m(3);
    string fn;
    srand(time(NULL));

    cout << "enter name for input file" << endl;
    cin >> fn;

    n = 1000;

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
