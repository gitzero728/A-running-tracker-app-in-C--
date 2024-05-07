//q2.cpp
#include <iostream>
#include <iomanip>
#include <valarray>
#include <string>
#include <sstream>
#include <fstream>
#include "interp.hpp"

using namespace std;

/* Read a file with GPS data formatted in 3 space-separated columns:
 * timestamp latitude longitude
 * and return the numerical data in the form of a single
 * valarray of size N*3. The data is read line-by line,
 * so that the value of row i and column j is stored in
 * the (3*i + j)-th component of the valarray
 */
valarray<double> read_gps_data(const string& filename, int N) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return valarray<double>(); // Return empty valarray on error
    }

    valarray<double> data(N * 3);

    string line;
    int row = 0;
    while (getline(file, line) && row < N) {
        stringstream ss(line);
        string cell;
        int col=0;
        while (getline(ss, cell, ' ') && col < 3) {
            try {
                data[row * 3 + col] = stod(cell);
            } catch (const invalid_argument& e) {
                cerr << "Error: Invalid data in file " << filename << " at row " << row << endl;
                return valarray<double>(); // Return empty valarray on error
            }
            ++col;
        }
        ++row;
    }
    return data;
}

/* Interpolate the coordinate data (latitude or longitude) at a given time t
   using Lagrange interpolation with piecewise quadratic polynomials */
double interp_coords(valarray<double>& t_varr, valarray<double>& coord_varr, double t) {
    int idx = locate(t_varr, t);
    if (idx < 0) {
        cerr << "Error: Time t = " << t << " is outside the data range." << endl;
        return 0.0;
    }

    valarray<double> xi(3);
    valarray<double> yi(3);

    if (idx == 0) {
        // Use the first three points for the interpolation
        xi[0] = t_varr[idx];
        xi[1] = t_varr[idx + 1];
        xi[2] = t_varr[idx + 2];
        yi[0] = coord_varr[idx];
        yi[1] = coord_varr[idx + 1];
        yi[2] = coord_varr[idx + 2];
    } else if (idx == t_varr.size() - 1) {
        // Use the last three points for the interpolation
        xi[0] = t_varr[idx - 2];
        xi[1] = t_varr[idx - 1];
        xi[2] = t_varr[idx];
        yi[0] = coord_varr[idx - 2];
        yi[1] = coord_varr[idx - 1];
        yi[2] = coord_varr[idx];
    } else {
        // Use the three surrounding points for the interpolation
        xi[0] = t_varr[idx - 1];
        xi[1] = t_varr[idx];
        xi[2] = t_varr[idx + 1];
        yi[0] = coord_varr[idx - 1];
        yi[1] = coord_varr[idx];
        yi[2] = coord_varr[idx + 1];
    }

    return Lagrange_N(xi, yi, t);
}