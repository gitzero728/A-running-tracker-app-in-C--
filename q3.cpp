//q3.cpp
#include <cmath>
#include <valarray>
#include "q3-4.hpp"

using namespace std;

const double earthRadius = 6371000.0; // Earth's radius in meters

valarray<double> coords_to_distances(valarray<double>& lat, valarray<double>& lon) {
    size_t N = lat.size();
    if (N < 1 || lon.size() != N) {
        cerr << "Error: Invalid input arrays." << endl;
        exit(-1);
    }

    valarray<double> dlat(N - 1);
    valarray<double> dlon(N - 1);

    for (size_t i = 0; i < N - 1; i++) {
        dlat[i] = lat[i + 1] - lat[i];
        dlon[i] = lon[i + 1] - lon[i];
    }

    valarray<double> dl(N - 1);
    for (size_t i = 0; i < N - 1; i++) {
        double Cos = cos(lat[i] * M_PI / 180.0), dist = earthRadius * 2.0 * M_PI / 360.0;
		dl[i] = dist * sqrt(dlat[i] * dlat[i] + Cos * Cos * dlon[i] * dlon[i]);
    }

    return dl;
}