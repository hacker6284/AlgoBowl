#include "job.h"

using namespace std;

job::job(int t, int st1, int st2, int st3){
  availableTime = t;
  stationTimes[0] = st1;
  stationTimes[1] = st2;
  stationTimes[2] = st3;
}

job::job(){
}

int job::getAvailableTime(){
  return availableTime;
}

int* job::getStationTimes(){
  return stationTimes;
}

bool* job::getCompletedStations(){
  return completedStations;
}
