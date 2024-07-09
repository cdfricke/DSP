/*
Programmer: Connor Fricke (cd.fricke23@gmail.com)
File: DSP.h
Latest Revision: 18-June-2024
Synopsis: Header File for DSP function library
*/

#ifndef DSP_H
#define DSP_H

#include <random>
#include <complex>
#include <vector>
using namespace std;

struct SignalComponent
{
    double coeff;
    double freq;
};

typedef complex<double> dcomp;

// getRandomFloat(const double, const double):
// Simply returns a single random number generated with the Mersenne Twister (mt19937)
// over a uniform distribution between the upper and lower bounds parameters.
// @@ parameters:
//  - const double lower: lower bound to uniform distribution
//  - const double upper: upper bound to uniform distribution
double getRandomFloat(const double lower, const double upper);


// generateSignal(vector<double>&, const int):
// creates a signal using random walk behavior for the purposes of filter behavior analysis
// step size randomly distributed between 0 and 0.05 for each step
// step direction chosen by 50-50 probability.
// @@ parameters:
//  - const vector<double>& t_Samples: function generates signal until the resulting vector is of equal size
// @@ return:
//  - vector<double> signal: output of function, i.e. the randomly generated signal
vector<double> generateSignal(const vector<double> t_Samples);


// generateSignal(vector<double>& signal, const vector<SignalComponent>&):
// creates a signal with a Fourier sine series expansion method from frequency and coefficients 
// stored by the vector parameter. Discretizes output signal over x_values vector parameter.
// @@ parameters:
//  - const vector<double>& x_values: discretization vector, i.e. calculate the signal value at these x_values
//  - const vector<SignalComponent>& components: sine wave signal components, with their frequency and coefficient stored in a struct
// @@ return:
// 
vector<double> generateSignal(const vector<double> &x_values, const vector<SignalComponent> &components);


// LOWPASS_FIR(const vectro<double>&, vector<double>&, const double):
// Takes in an input vector and output vector as parameters. Applies an FIR Filter
// to the input vector characterized by the difference equation:
//   y[n] = a*x[n] + (1-a)*x[n-1]
// @@ parameters:
//  - const vector<double>& input: represents an unfiltered signal
//  - const double alpha: defines both taps (coefficients) of the FIR filter via {a, 1-a}.
// @@ return:
//  - vector<double> output: resulting filtered signal
vector<double> LOWPASS_FIR(const vector<double> &input, const double alpha);


// AVERAGER_IIR(const vector<double>&, vector<double>&, const double):
// Takes in an input vector and output vector as parameters. Applies an IIR Filter
// to the input vector characterized by the difference equation:
//   y[n] = a*x[n] + (1-a)*y[n-1]
// This filter corresponds to a lowpass filter with two taps defined by the third parameter value.
// It is well known as an exponential averaging filter.
// @@ parameters:
//  - const vector<double>& input: represents an unfiltered signal
//  - const double alpha: defines both taps (coefficients) of the IIR filter via {a, 1-a}
// @@ return:
//  - vector<double>& output: resulting filtered signal
vector<double> AVERAGER_IIR(const vector<double>& input, const double alpha);


// DFT(const vector<double>&, const vector<double>&, vector<dcomp> out):
// Takes the discrete Fourier Transform of a signal for discrete k values.
// @@ parameters:
//  - const vector<double>& x: input signal to be transformed
//  - const vector<int>& k_range: represents the discrete values of k for the DFT to be calculated over. must range from -N/2 to N/2
// @@ return:
//  - vector<complex<double>>& output: resulting transformed signal. each value is a complex number with real and imaginary components.
vector<dcomp> DFT(const vector<double>& x, const vector<int>& k_range);


// goertzelFilter_1(const vector<double>&, const int):
// Performs the 1st - order recursive implementation of a Goertzel Filter for a single integer k-value 
// of an input signal to calculate X(k) = y[N] where y is the output signal of the filter.
// y_k[n] = exp(i * 2 * PI * k / N)*y[n-1]
vector<complex<double>> goertzelFilter_1(const vector<double>& input, const int k);

// goertzelFilter_2(const vector<double>&, const int):
// Performs the 2nd - order recursive implementation of a Goertzel Filter for a single integer k-value
// of n input signal to calculate X(k) = y[N] where y is the output signal of the filter, and N is the
// final element in the digital signal.
// y[n] = x[n] - W_Nk*x[n-1] + 2cos(2PIk/N)*y[n-1] - y[n-2]
vector<dcomp> goertzelFilter_2(const vector<double> &input, const int k);

#endif