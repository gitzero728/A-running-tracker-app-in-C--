#ifndef Q2_H
#define Q2_H

#include <valarray>
#include <string>

std::valarray<double> read_gps_data(const std::string& filename, int N);
double interp_coords(std::valarray<double>& t_varr, std::valarray<double>& coord_varr, double t);

#endif  // Q2_H
