/*
Programmer: Connor Fricke (cd.fricke23@gmail.com)
File: DSP.h
Latest Revision: 11-June-2024
Synopsis: Header File for DSP function library
*/

#ifndef DSP_H
#define DSP_H

#include <random>
#include <complex>
using namespace std;

typedef complex<double> dcomp;

// getRandomFloat():
// Simply returns a single random number generated with the Mersenne Twister (mt19937)
// over a uniform distribution between the upper and lower bounds parameters.
// @@ parameters:
//  - const double lower: lower bound to uniform distribution
//  - const double upper: upper bound to uniform distribution
double getRandomFloat(const double lower, const double upper);


// generateSignal():
// creates a signal using random walk behavior for the purposes of filter analysis
// step size randomly distributed between 0 and 0.05 for each step
// step direction chosen by 50-50 probability.
// @@ parameters:
//  - vector<double>& signal: output of function, i.e. the randomly generated signal
//  - const int TARGET_LENGTH: function generates signal until the resulting vector is of size = TARGET_LENGTH
void generateSignal(vector<double>& signal, const int TARGET_LENGTH);

// LOWPASS_FIR():
// Takes in an input vector and output vector as parameters. Applies an FIR Filter
// to the input vector characterized by the difference equation:
//   y[n] = a*x[n] + (1-a)*x[n-1]
// @@ parameters:
//  - const vector<double>& input: represents an unfiltered signal
//  - vector<double>& output: resulting filtered signal
//  - const double alpha: defines both taps (coefficients) of the FIR filter via {a, 1-a}.
void LOWPASS_FIR(const vector<double>& input, vector<double> &output, const double alpha);


// AVERAGER_IIR():
// Takes in an input vector and output vector as parameters. Applies an IIR Filter
// to the input vector characterized by the difference equation:
//   y[n] = a*x[n] + (1-a)*y[n-1]
// This filter corresponds to a lowpass filter with two taps defined by the third parameter value.
// It is well known as an exponential averaging filter.
// @@ parameters:
//  - const vector<double>& input: represents an unfiltered signal
//  - vector<double>& output: resulting filtered signal
//  - const double alpha: defines both taps (coefficients) of the IIR filter via {a, 1-a}
void AVERAGER_IIR(const vector<double>& input, vector<double> &output, const double alpha);


// DFT:
// Takes the discrete Fourier Transform of a signal for discrete k values.
// @@ parameters:
//  - const vector<double>& x: input signal to be transformed
//  - const vector<double>& k_range: represents the discrete values of k for the DFT to be calculated over
//  - vector<complex<double>>& output: resulting transformed signal. each value is a complex number with real and imaginary components.
void DFT(const vector<double>& x, const vector<double>& k_range, vector<complex<double>>& output);

#endif