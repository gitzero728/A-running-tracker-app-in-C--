#include "run.hpp"
#include <iostream>

using namespace std;

int main() {
    Run run(1704067200.0); // Start time: 00:00 1 Jan 2024

    // Add GPS data to the run
    valarray<double> t_data = {1704067200.0, 1704067201.0, 1704067202.0, 1704067205.0, 1704067206.0, 1704067207.0};
    valarray<double> lat_data = {45.0, 45.1, 45.2, 45.2, 45.3, 45.3};
    valarray<double> lon_data = {-93.0, -93.1, -93.2, -93.2, -93.3, -93.3};
    run.addGPSData(t_data, lat_data, lon_data);

    // Pause the run for 3 seconds
    run.pauseRun();
    t_data = {1704067207.0, 1704067210.0, 1704067211.0, 1704067212.0};
    lat_data = {45.3, 45.3, 45.4, 45.4};
    lon_data = {-93.3, -93.3, -93.4, -93.4};
    run.addGPSData(t_data, lat_data, lon_data);
    run.resumeRun();

    // End the run
    run.endRun();
    run.printRunInfo();

    return 0;
}