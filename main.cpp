#include "job.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void algoBowlInput();
bool outputTester();

int main() {
  cout << "Hello, world!" << endl;
  algoBowlInput();
  outputTester();
  return 0;
}

//function to test output files

bool outputTester(){
    //TODO: No jobs overlapping at a single station
    
    int sum1(0), sum2(0), sum3(0), jobNumber(0), workstationNumber(0), completionTime(0);
    
    //open input file as ifin, open solution file as ofin
    ifstream ifin, ofin;
    ifin.open("test2stations.txt");
    ofin.open("twoStationOut.txt");
    if(!ifin.is_open()) cout << "Error opening input file" << endl;
    if(!ofin.is_open()) cout << "Error opening solution file" << endl;
    
    //store job number, total workstations, and completion time
    ifin >> jobNumber >> workstationNumber;
    ofin >> completionTime;
    
    int availTime(0), work1(0), work2(0), st1(0), st2(0);
    vector<int> startTimes(jobNumber);
    
    for(int i = 0; i < jobNumber; i++){
        ifin >> availTime >> work1 >> work2;
        ofin >> st1 >> st2;
        
        //No job working both stations at the same time
        int a = min(st1, st2);
        if(a == st1 && (st1 + work1) >= st2){ cout << "Invalid: jobs overlap" << endl; return false;}
        if(a == st2 && (st2 + work2) >= st1){ cout << "Invalid: jobs overlap b" << endl; return false;}
        
        //job start time at each station >= job available time
        if(st1 < availTime || st2 < availTime) {  cout << "Ivalid: Job starts before available" << endl; return false;}
        startTimes[i] = availTime;
        sum1 += work1;
        sum2 += work2;
    }
    
    //cout << completionTime << " " << sum1 << " " << sum2 << endl;
    //for(int z : startTimes){cout << z << endl;}
    
    //overall completion time >= max(sum job-times at each work station)
    if(completionTime < sum1 || completionTime < sum2){ cout << "Invalid: completed before slowest station time" << endl; return false;}
    
    
    ifin.close();
    ofin.close();
    
    cout <<  "Valid solution" << endl;
    
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
        startTime = rand() % 51;            //start time can range from zero to fifty
        station1 = (rand() % 50) + 1;       //add 1 after the modulus to prevent job time of 0
        station2 = (rand() % 50) + 1;
        station3 = (rand() % 50) + 1;
        fout  << '\n' << startTime << " " << station1 << " " << station2 << " " << station3;
    }

    fout.close();
}
