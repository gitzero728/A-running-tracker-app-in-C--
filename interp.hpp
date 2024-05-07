#ifndef INTERP_H_
#define INTERP_H_

#include <valarray>

using namespace std;

int locate(valarray<double>& xi, double x, bool uniform=true);
double Lagrange_Nk(int k, valarray<double>& xi, double x);
double Lagrange_N(valarray<double>& xi, valarray<double>& yi, double x);

#endif // INTERP_H_
