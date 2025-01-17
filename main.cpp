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
bool compareJobStartTimes(job *job1, job *job2);

string inputFile = "test101.txt";
string solutionFile = "solution.txt";

int main() {
  cout << "Hello, world!" << endl;

  //Generate New Inputs of Length 1000
  //algoBowlInput();

  //Reading In Info
  ifstream ifin;
  ifin.open(inputFile);
  if(!ifin.is_open()) cout << "Error opening input file initial" << endl;
  int numJobs;
  int numStations;
  ifin >> numJobs;
  ifin >> numStations;
  int startTimes[numJobs];
  int workStation1Duration[numJobs];
  int workStation2Duration[numJobs];
  int workStation3Duration[numJobs];
  for(int i = 0; i < numJobs; i++){
    ifin >> startTimes[i];
    ifin >> workStation1Duration[i];
    ifin >> workStation2Duration[i];
    ifin >> workStation3Duration[i];
    //cout << startTimes[i] << " " << workStation1Duration[i] << " " << workStation2Duration[i] << endl;
  }
  ifin.close();


  //Creating an array of jobs
  job *jobArray = new job[numJobs];
  for(int i = 0; i < numJobs; i++){
    job newJob(startTimes[i], workStation1Duration[i], workStation2Duration[i], workStation3Duration[i]);
    jobArray[i] = newJob;
    //cout << jobArray[i].getAvailableTime();
  }

  //Solution Generator
  int solnTime = algoBowlSolution(jobArray, numJobs);

  //Solution Printer
    ofstream fout;
    fout.open(solutionFile);
    if (!fout.is_open()) cout << "Error opening output file" << endl;

  //double nested loop
  fout << solnTime << endl;
  for (int i = 0; i < numJobs; i++){
    for (int j = 0; j < 3; j++){
      fout << jobArray[i].getStationCompTimes()[j] << " ";
    }
    fout << endl;
  }

  //Verifier
  outputTester();

  delete [] jobArray;
  return 0;
}

//Function to compare job start times
bool compareJobStartTimes(job *job1,job *job2){
  if(job1->getAvailableTime()<job2->getAvailableTime()){
    return true;
  }
  else{
    return false;
  }
}

//Solution Generator, returns the time to completion and edits the array of vector of jobs
int algoBowlSolution(job *jobArrayUnsorted, int length){

  vector<job*> jobArraySorted(length);

  for (int i = 0; i < length; i++){
    jobArraySorted[i] = &jobArrayUnsorted[i];
  }
  sort(jobArraySorted.begin(), jobArraySorted.end(), compareJobStartTimes);

  int workstations[3] = {0, 0, 0};

  while (jobArraySorted.size() > 0){
    int currentStation = 0;
    if (workstations[0] <= workstations[1] && workstations[0] <= workstations[2]){
      currentStation = 1;
    }
    else if(workstations[1]<=workstations[2]){
      currentStation = 2;
    }
    else{
      currentStation = 3;
    }

    bool noJobs = true;
    for (int m = 0; m < jobArraySorted.size(); m++){
      job *j = jobArraySorted[m];
      //Make sure available
      if (j->getAvailableTime() > workstations[currentStation-1]){
        //job not available yet.
        continue;
      }

      //Make sure not completed
      else if (j->getCompletedStations()[currentStation - 1]){
        //job has been completed at this station
        continue;
      }

      //Make sure no overlaps
      bool overlap = false;
      for (int k = 0; k < 3; k++){
        int now = workstations[currentStation -1];
        if (j->getStationCompTimes()[k] != -1 && workstations[currentStation - 1] >= j->getStationCompTimes()[k] && workstations[currentStation - 1] < j->getStationCompTimes()[k] + j->getStationTimes()[k]){
          //job will start at a time where it is being worked on at anothe station
          overlap = true;
          break;
        }
        else if (j->getStationCompTimes()[k] != -1 && workstations[currentStation - 1] + j->getStationTimes()[currentStation -1] > j->getStationCompTimes()[k] && workstations[currentStation -1] + j->getStationTimes()[currentStation -1] <= j->getStationCompTimes()[k] + j->getStationTimes()[k]){
          //job will finish after it is started on another station
          overlap = true;
          break;
        }
        else if (j->getStationCompTimes()[k] != -1 && workstations[currentStation - 1] >= j->getStationCompTimes()[k] && workstations[currentStation - 1] + j->getStationTimes()[currentStation - 1] <= j->getStationCompTimes()[k] + j->getStationTimes()[k]){
          //job will be entirely contained within another job
          overlap = true;
          break;
        }
        else if (j->getStationCompTimes()[k] != -1 && workstations[currentStation -1] <= j->getStationCompTimes()[k] && workstations[currentStation - 1] + j->getStationTimes()[currentStation -1] >= j->getStationCompTimes()[k]){
          //job will contain another job.
          overlap = true;
          break;
        }
      }
      if (overlap){
        //job overlaps
        continue;
      }
      else{
        //we can do this job
        j->setCompletedStations(currentStation-1, true);
        j->setStationCompTimes(currentStation-1, workstations[currentStation - 1]);
        workstations[currentStation-1] = workstations[currentStation-1]+j->getStationTimes()[currentStation - 1];
        bool allDone = true;
        for (int b = 0; b < 3; b++){
          if (j->getCompletedStations()[b] == false){
            allDone = false;
          }
        }
        if (allDone){
          jobArraySorted.erase(jobArraySorted.begin()+m);
        }
      }
    }
    if (noJobs){
      workstations[currentStation - 1]++;
    }
  }

  int timeToComplete = 0;
  for (int i = 0; i < 3; i++){
    if (workstations[i] > timeToComplete){
      timeToComplete = workstations[i];
    }
  }
  return timeToComplete - 1;
  //wrong line for testing below
  //return timeToComplete;
}


//function to test output files
bool outputTester(){

    int lastJobFinishTime = 0;

    int sum1(0), sum2(0), sum3(0), jobNumber(0), workstationNumber(0), completionTime(0);

    //open input file as ifin, open solution file as ofin
    ifstream ifin, ofin;
    ifin.open(inputFile);
    ofin.open(solutionFile);
    if(!ifin.is_open()) cout << "Error opening input file verify" << endl;
    if(!ofin.is_open()) cout << "Error opening solution file" << endl;

    //store job number, total workstations, and completion time
    ifin >> jobNumber >> workstationNumber;
    ofin >> completionTime;

    int availTime(0), work1(0), work2(0), work3(0), st1(0), st2(0), st3(0);
    vector<vector<int>> stStation1(jobNumber, vector<int> (2));
    vector<vector<int>> stStation2(jobNumber, vector<int> (2));
    vector<vector<int>> stStation3(jobNumber, vector<int> (2));

    for(int i = 0; i < jobNumber; i++){
        ifin >> availTime >> work1 >> work2 >> work3;
        ofin >> st1 >> st2 >> st3;

        if (st1 + work1 > lastJobFinishTime){
          lastJobFinishTime = st1 + work1;
        }
        if (st2 + work2 > lastJobFinishTime){
          lastJobFinishTime = st2 + work2;
        }
        if (st3 + work3 > lastJobFinishTime){
          lastJobFinishTime = st3 + work3;
        }

        //No job working both stations at the same time
        int a = min(st1, st2);
        int b = min(a, st3);
        if(b == st1 && (st1 + work1) > st2){ cout << "Invalid: job " << (i + 1) <<" overlap at station 1 & 2" << endl; return false;}
        if(b == st1 && (st1 + work1) > st3){ cout << "Invalid: job " << (i + 1) <<" overlap at station 1 & 3" << endl; return false;}
        if(b == st2 && (st2 + work2) > st1){ cout << "Invalid: job " << (i + 1) <<" overlap at station 2 & 1" << endl; return false;}
        if(b == st2 && (st2 + work2) > st3){ cout << "Invalid: job " << (i + 1) <<" overlap at station 2 & 3" << endl; return false;}
        if(b == st3 && (st3 + work3) > st1){ cout << "Invalid: job " << (i + 1) <<" overlap at station 3 & 1" << endl; return false;}
        if(b == st3 && (st3 + work3) > st2){ cout << "Invalid: job " << (i + 1) <<" overlap at station 3 & 2" << endl; return false;}


        //job start time at each station >= job available time
        if(st1 < availTime || st2 < availTime || st3 < availTime) {  cout << "Ivalid: Job " << (i + 1) << " starts before available" << endl; return false;}

        //store start times, with corresponding working times, we'll sort these later to make sure no jobs overlap at a single station
        stStation1[i][0] = st1;
        stStation1[i][1] = work1;
        stStation2[i][0] = st2;
        stStation2[i][1] = work2;
        stStation3[i][0] = st3;
        stStation3[i][1] = work3;

        //calcuting the fastest possible time each station
        sum1 += work1;
        sum2 += work2;
        sum3 += work3;
    }

    //sort job list for each statement by start time
    sort(stStation1.begin(), stStation1.end());
    sort(stStation2.begin(), stStation2.end());
    sort(stStation3.begin(), stStation3.end());

    //check to see if a job start time + its working time is greater than the start time of the next job
    for (int i = 0; i < (jobNumber - 1); i++){
        if((stStation1[i][0] + stStation1[i][1]) > stStation1[i+1][0]){cout << "Invalid: Overlapping jobs at Station 1" << endl; return false;}
        if((stStation2[i][0] + stStation2[i][1]) > stStation2[i+1][0]){cout << "Invalid: Overlapping jobs at Station 2" << endl; return false;}
        if((stStation3[i][0] + stStation3[i][1]) > stStation3[i+1][0]){cout << "Invalid: Overlapping jobs at Station 3" << endl; return false;}
    }

    //cout << completionTime << " " << sum1 << " " << sum2 << endl;
    //for(int z : startTimes){cout << z << endl;}

    //overall completion time >= max(sum job-times at each work station)
    if(completionTime < sum1 || completionTime < sum2 || completionTime < sum3){ cout << "Invalid: completed before physically possible based upon work time at each station" << endl; return false;}

    //check for invalid time
    if(completionTime != lastJobFinishTime){
      cout << "Wrong completion time. Got " << completionTime << ", expected " << lastJobFinishTime << endl;
      return false;
    }

    ifin.close();
    ofin.close();

    cout <<  "Valid solution" << endl;

    return true;
}
/*bool outputTester(){
    //THIS IS THE OUPUT TESTER FOR TWO WORK STATIONS

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
}*/


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
