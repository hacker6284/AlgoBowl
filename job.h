#include <iostream>

using namespace std;

class job{
private:
  int availableTime;
  int *stationTimes;
  bool *completedStations;
  int currentJob;

public:
  void setAvailableTime(int time);
  void setStationTimes(int *times);

  int getAvailableTime();
  int *getStationTimes();
  int getStationTime(int station);
  bool *getCompletedStations();
  bool getCompletedStation(int station);
  int getCurrentJob();
};
