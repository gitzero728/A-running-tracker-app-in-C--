#ifndef RUN_HPP
#define RUN_HPP

#include <valarray>
#include "q3.hpp"

using namespace std;

class Run {
private:
    double t_start;
    double t_end;
    double pause_start;
    double pause_duration;
    int duration;
    double distance;
    valarray<double> t_data;
    valarray<double> lat_data;
    valarray<double> lon_data;
    valarray<double> dl;
    valarray<double> speed;
    bool is_paused;

public:
    Run(double start_time);
    void startRun();
    void pauseRun();
    void resumeRun();
    void endRun();
    void printRunInfo();
    double getAvgPace();
    double getFastestPace();
    void calculateDistances();
    void calculateSpeeds();
    void addGPSData(const valarray<double>& t, const valarray<double>& lat, const valarray<double>& lon);

private:
    bool detect_pause(const valarray<double>& dl, double threshold = 1.0);
    valarray<double> dl_to_speed(const valarray<double>& dl);
};

#endif // RUN_HPP
