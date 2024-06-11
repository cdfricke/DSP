#ifndef DSP_H
#define DSP_H

#include <random>
#include <complex>

const double PI = 2 * asin(1);

using namespace std;

// ** FUNCTION PROTOTYPES **
double getRandomFloat(const double, const double);
void generateSignal(vector<double> &, const int);
void LOWPASS_FIR(const double input, double &output, const double alpha, double &delay0);
void AVERAGER_IIR(const double input, double &output, const double alpha, double &delay0);
void DFT(vector<double> x, vector<double> k_range, vector<complex<double>> &output);

#endif