#include <iostream>
#pragma once
using namespace std;

class job {
private:

  int availableTime;
  int stationTimes[3];
  bool completedStations[3] = {false, false, false};
  //int currentJob;
  int stationCompTimes[3] = {100000000, 100000000, 100000000}; //Time Job was completed on a given station

public:
  //void setAvailableTime(int time);
  //void setStationTimes(int *times);
  job();
  job(int t, int st1, int st2, int st3);
  int getAvailableTime();
  int *getStationTimes();
  //int getStationTime(int station);
  bool *getCompletedStations();
  //bool getCompletedStation(int station);
  //int getCurrentJob();
};
