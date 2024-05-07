#include <cassert>
#include <iostream>
#include <stddef.h>
#include <valarray>
#include <cstdlib>
#include <cstdio>
#include <cmath>

using namespace std;


/* Given an array of coordinates xi for an
 * ordered uniform grid of size n and a
 * value x, locate the index i for which
 * x \in [xi[i], xi[i+1]). (We assume that
 * the grid is given in incremental order
 * i.e. xi[i+1] - xi[i] > 0) */
int locate(valarray<double>& xi, double x, bool uniform=true) {

    size_t n = xi.size();
    int idx;
    double a, b, dx;

    /* assign edge values of interpolation interval */
    a = xi[0];
    b = xi[n-1];

    if (uniform) {
      /* Calculate step size */
      dx = (b - a) / (n - 1);

      /* Special treatment if x=b */
      if (x == b)
        return n - 1;

      /* Check that x \in [a,b] */
      if (x < a || x > b) {
        cerr << "ERROR: Cannot locate index. Coordinate x=" << x
             << " lies outside the interpolation interval";
        cerr << "[" << xi[0] << ", " << xi[n - 1] << "]." << endl;
        return -1;
      }

      /* Find index assuming uniform grid */
      idx = floor((x - a) / dx);
    } else {
        cerr << "Non-uniform version of locate() not implemented yet" << endl;
        return -1;
    }

    return idx;
}

/* Given an array xi of n grid points, calculate
 * the k-th Lagrange polynomial of degree n-1 that
 * has roots at each grid point except for xi[k]
 * and that is normalised so that its value on
 * xi[k] is 1.0. */
double Lagrange_Nk(int k, valarray<double>& xi, double x) {

    size_t n = xi.size();
    double prod = 1.0;

    /* For loop that calculates the product
     * of Eq.(7) from the Lecture Notes */
    for (size_t i=0;i<n;i++) {
        if (i==k) continue;
        prod *= (x - xi[i])/(xi[k] - xi[i]);
    }

    return prod;
}

/* Given an array xi of n grid points, and an array
 * yi of n values, calculate the Lagrange interpolant
 * that passes from all data points (xi[i],yi[i]) and
 * return its value at a given point x in [xi[0],xi[n-1]]. */
double Lagrange_N(valarray<double>& xi, valarray<double>& yi, double x) {

    size_t n = xi.size();
    assert(yi.size() == n);

    int k;
    double sum = 0.0;

    /* Perform the linear superposition of all L_Nk(x) */
    for (k=0;k<n;k++) {
        sum += yi[k] * Lagrange_Nk(k, xi, x);
    }

    return sum;
}


