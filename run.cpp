#include "run.hpp"
#include <iostream>

using namespace std;

Run::Run(double start_time) {
    t_start = start_time;
    startRun();
}

void Run::startRun() {
    t_data.resize(0);
    lat_data.resize(0);
    lon_data.resize(0);
    t_start = 0.0;
    t_end = 0.0;
    pause_start = 0.0;
    pause_duration = 0.0;
    duration = 0;
    distance = 0.0;
    is_paused = false;
}

void Run::pauseRun() {
    if (!is_paused) {
        pause_start = t_data[t_data.size() - 1];
        is_paused = true;
    }
}

void Run::resumeRun() {
    if (is_paused) {
        pause_duration += t_data[t_data.size() - 1] - pause_start;
        is_paused = false;
    }
}

void Run::endRun() {
    t_end = t_data[t_data.size() - 1];
    duration = static_cast<int>(t_end - t_start - pause_duration);
    calculateDistances();
    calculateSpeeds();

    // Check if a pause was detected
    if (detect_pause(dl, 1.0)) {
        // Pause the run
        std::cout << "Pause detected. Run paused." << std::endl;
        pauseRun();
    }
}

void Run::printRunInfo() {
    cout << "Run Information:" << endl;
    cout << "Start Time: " << t_start << " seconds since Unix epoch" << endl;
    cout << "End Time: " << t_end << " seconds since Unix epoch" << endl;
    cout << "Duration: " << duration << " seconds" << endl;
    cout << "Total Distance: " << distance << " meters" << endl;
    cout << "Average Pace: " << getAvgPace() << " m/s" << endl;
    cout << "Fastest Pace: " << getFastestPace() << " m/s" << endl;
}

double Run::getAvgPace() {
    return distance / duration;
}

double Run::getFastestPace() {
    double minPace = speed[0];
    for (size_t i = 1; i < speed.size(); i++) {
        if (speed[i] < minPace) {
            minPace = speed[i];
        }
    }
    return minPace;
}

void Run::calculateDistances() {
    distance = 0.0;
    dl = coords_to_distances(lat_data, lon_data);
    for (double d : dl) {
        distance += d;
    }
}

void Run::calculateSpeeds() {
    speed = dl_to_speed(dl);
}

void Run::addGPSData(const valarray<double>& t, const valarray<double>& lat, const valarray<double>& lon) {
    t_data = t;
    lat_data = lat;
    lon_data = lon;
}

bool Run::detect_pause(const valarray<double>& dl, double threshold) {
    for (double distance : dl) {
        if (distance < threshold) {
            return true; // Detected a pause
        }
    }
    return false; // No pause detected
}

valarray<double> Run::dl_to_speed(const valarray<double>& dl) {
    valarray<double> speed(dl.size());
    for (size_t i = 0; i < dl.size(); i++) {
        speed[i] = dl[i];
    }
    return speed;
}
