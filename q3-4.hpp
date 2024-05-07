#ifndef Q3_H_
#define Q3_H_

#include <iostream>
#include <cmath>
#include <valarray>

/* Definitions of constants */
#define R_EARTH 6371000.0L  // Earth's radius in meters
#define M_EARTH 5.9722E+24  // Earth's mass in kg
#define M_MOON 7.342E+22    // Lunar mass in kg
#define G_SI 6.67430E-11    // Newton's constant in SI units
#define C_SI 299792458.0L   // Speed of light in SI units (m/s)

using namespace std;

/* Define initial coordinates of SatA and SatB in units of Earth
 * radii so that the numerical values of our data are of order 1. */
const double XA_DATA[2] = {26378100.0L/R_EARTH, 0.0L};
const double XB_DATA[2] = {0.0L, 26378100.0L/R_EARTH};

/* Measured time delays dt for SatA and SatB */
const double DTA_DATA = 0.0765834L;
const double DTB_DATA = 0.0725505L;

/* Initial velocity vectors for SatA and SatB in m/s */
const double VA_DATA[2] = {0.0L, 3887.3L};
const double VB_DATA[2] = {3887.3L, 0.0L};

/* Define coordinates of the Moon in meters */
const double XL_DATA[2] = {384400000.0L, 0.0L};

/* Useful functions for diagnostics */
void print_mat(double M[2][2]);
void print_vec(double v[2]);


/* You will need to implement the following functions */

/* q3.cpp */

void f(double (&fx)[2],               // to be filled in with components of \vec{f}(x,y)
       double x[2],                   // input coordinate vector (x,y)
       const double xA[2]=XA_DATA,    // location of SatA
       const double dtA=DTA_DATA,     // time delay measured by SatA
       const double xB[2]=XB_DATA,    // location of SatB
       const double dtB=DTB_DATA);    // time delay measured by SatB

void f_Jac(double (&Jx)[2][2],          // 2x2 array to be filled in with components of Jacobian
           double x[2],                 // input coordinate vector (x,y)
           const double xA[2]=XA_DATA,  // location of SatA
           const double xB[2]=XB_DATA); // location of SatB


/* newton-raphson.cpp */

void mat_inv_2x2(double (&Minv)[2][2], double M[2][2]);
int newton_raphson(double (&xi)[2], double x0[2], int Nmax=100, double TOL=1e-6);

/* q4.cpp */

valarray<double> rhs(double t, valarray<double> yvec);
valarray<double> euler(double t0, valarray<double> y0, double h, double tf);
valarray<double> rungeKutta4(double t0, valarray<double> y0, double h, double tf);

#endif // Q3_H_
