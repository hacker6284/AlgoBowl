#include <iostream>
#pragma once
using namespace std;

class job {
private:

  int availableTime; //time the job becomes available for all stations
  int stationTimes[3]; //Time the job takes on a given station
  bool completedStations[3] = {false, false, false}; //Whether a job has been completed on a given station
  //int currentJob;
  int stationCompTimes[3] = {-1, -1, -1}; //Time Job was started on a given station

public:
  void setCompletedStations(int station, bool status);
  void setStationCompTimes(int station, int comptime);
  job();
  job(int t, int st1, int st2, int st3);
  int getAvailableTime();
  int *getStationTimes();
  int *getStationCompTimes();
  bool *getCompletedStations();
  //bool getCompletedStation(int station);
  //int getCurrentJob();
};
