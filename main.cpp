#include "job.cpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void algoBowlInput();
bool outputTester();

int main() {
  cout << "Hello, world!" << endl;
  //algoBowlInput();


  //Reading In Info
  ifstream ifin;
  ifin.open("test2stations.txt");
  if(!ifin.is_open()) cout << "Error opening input file" << endl;
  int numJobs;
  int numStations;
  ifin >> numJobs;
  ifin >> numStations;
  int startTimes[numJobs];
  int workStation1Duration[numJobs];
  int workStation2Duration[numJobs];
  for(int i = 1; i <= numJobs; i++){
    ifin >> startTimes[i];
    ifin >> workStation1Duration[i];
    ifin >> workStation2Duration[i];
    //cout << startTimes[i] << " " << workStation1Duration[i] << " " << workStation2Duration[i] << endl;
  }
  ifin.close();


  //Creating an array of jobs
  job jobArray[numJobs-1];
  for(int i = 1; i <= numJobs; i++){
    job newJob(startTimes[i], workStation1Duration[i], workStation2Duration[i]);
    jobArray[i] = newJob;
    //cout << jobArray[i].getAvailableTime();
  }

  //algoBowlSolution();
  return 0;
}




//function to test output files

bool outputTester(){
    //TODO: overall completion time >= max(sum job-times at each work station)
    int sum1(0), sum2(0), sum3(0);
    ifstream ifin, ofin;
    ifin.open("test2stations.txt");
    ofin.open("twoStationOut.txt");
    if(!ifin.is_open()) cout << "Error opening input file" << endl;
    if(!ofin.is_open()) cout << "Error opening solution file" << endl;


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
        startTime = rand() % 51;            //start time can range from zero to fifty
        station1 = (rand() % 50) + 1;       //add 1 after the modulus to prevent job time of 0
        station2 = (rand() % 50) + 1;
        station3 = (rand() % 50) + 1;
        fout  << '\n' << startTime << " " << station1 << " " << station2 << " " << station3;
    }

    fout.close();
}
