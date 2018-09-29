#include "job.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void algoBowlInput();
bool outputTester();
int algoBowlSolution(job *jobArrayUnsorted, int length);
bool compareJobStartTimes(job *job1,job *job2);

int main() {
  cout << "Hello, world!" << endl;

  //Generate New Inputs of Length 1000
  //algoBowlInput();

  //Reading In Info
  ifstream ifin;
  ifin.open("test3stations.txt");
  if(!ifin.is_open()) cout << "Error opening input file" << endl;
  int numJobs;
  int numStations;
  ifin >> numJobs;
  ifin >> numStations;
  int startTimes[numJobs];
  int workStation1Duration[numJobs];
  int workStation2Duration[numJobs];
  int workStation3Duration[numJobs];
  for(int i = 1; i <= numJobs; i++){
    ifin >> startTimes[i];
    ifin >> workStation1Duration[i];
    ifin >> workStation2Duration[i];
    ifin >> workStation3Duration[i];
    //cout << startTimes[i] << " " << workStation1Duration[i] << " " << workStation2Duration[i] << endl;
  }
  ifin.close();


  //Creating an array of jobs
  job jobArray[numJobs];
  for(int i = 1; i < numJobs; i++){
    job newJob(startTimes[i], workStation1Duration[i], workStation2Duration[i], workStation3Duration[i]);
    jobArray[i] = newJob;
    //cout << jobArray[i].getAvailableTime();
  }

  //Solution Generator
  int solnTime = algoBowlSolution(jobArray, numJobs-1);

  //Solution Printer
  //double nested loop

  //Verifier
  outputTester();

  return 0;
}

bool compareJobStartTimes(job *job1,job *job2){
  if(job1->getAvailableTime()<job2->getAvailableTime()){
    return true;
  }
  else{
    return false;
  }
}

int algoBowlSolution(job *jobArrayUnsorted, int length){

  vector<job*> jobArraySorted(length);

  for (int i = 0; i < length; i++){
    jobArraySorted[i] = &jobArrayUnsorted[i];
  }
  sort(jobArraySorted.begin(), jobArraySorted.end(), compareJobStartTimes);

  for(int i = 0; i < 100; i++){
    cout << jobArraySorted[i] << " vs. " << jobArraySorted[i]->getAvailableTime() << endl;
  }

  int timeToComplete = 0;
  return timeToComplete;
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
