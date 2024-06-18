#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <cstdlib>
#include <complex>
#include <cassert>
#include "DSP.h"
using namespace std;
extern const double PI;

// Programmer: Connor Fricke (cd.fricke23@gmail.com)
// File: filter_design.cpp
// Latest Revision: 7-June-2024
// Synopsis: Short program for testing software implementation of filter designs, as well as my DSP library.

// ** MAIN PROGRAM **
int main()
{
    // parameters
    bool FIR = false;                       // decides which filter is applied. Both have two taps chosen by alpha
    double alpha = 0.125;                   // filter coeffs are {a, 1-a}
    double SIGNAL_DURATION = 50.0;          // generated signal duration in seconds. we want this to be long to improve DFT result
    double SAMPLING_RATE = 1.0;
    double SAMPLING_PERIOD = 1.0 / SAMPLING_RATE;
    double NYQUIST = SAMPLING_RATE / 2.0;

    // *** SAMPLING CONTROL ***
    vector<double> t_Samples;
    for (double i = 0.0; i < SIGNAL_DURATION; i += SAMPLING_PERIOD) t_Samples.push_back(i);
    int N = t_Samples.size();

    // *** USER-CREATED SIGNAL ***
    // to create a signal with sine wave components, you need a vector of SignalComponents,
    // and a vector of discrete t values which tells us where the samples of the signal are.
    // The SignalComponent initialized as {0.1, 5.0} corresponds to 0.2sin(5.0t) in the Fourier series, for example.
    vector<SignalComponent> components{{0.5, 0.2}};
    for (SignalComponent c : components)
    {
        assert(c.freq < NYQUIST);
    }
    vector<double> x = generateSignal(t_Samples, components);
    

    // RANDOM SIGNAL (NOT PERIODIC)
    //vector<double> x = generateSignal(t_Samples);

    // UNITY SIGNAL
    // vector<double> x(100, 1.0);

    // *** DFT OF INPUT SIGNAL ***
    // set frequency discretization for DFT
    vector<int> k_vals;
    for (int i = -N/2; i < N/2; i++)
    {
        k_vals.push_back(i);
    }
    vector<dcomp> transformedSignal = DFT(x, k_vals);

    // *** FILTERED SIGNAL ***
    vector<double> y0;
    if (FIR) y0 = LOWPASS_FIR(x, alpha);
    else y0 = AVERAGER_IIR(x, alpha);

    // *** IMPULSE RESPONSE ***
    vector<double> impulse(20, 0); // fifty zeros
    impulse[0] = 1;
    vector<double> h; 
    if (FIR)
        h = LOWPASS_FIR(impulse, alpha);
    else
        h = AVERAGER_IIR(impulse, alpha);

    // *** FREQUENCY RESPONSE ***
    dcomp I = -1;
    I = sqrt(I);
    // take DFT over range of k_vals, store result in Freq_response vector
    vector<dcomp> Freq_Response = DFT(h, k_vals);

    // *** SAVE DATA ***
    ofstream fout;
    fout.open("data/input.dat");
    for (int i = 0; i < x.size(); i++) fout << t_Samples[i] << ' ' << x[i] << endl;
    fout.close();
    fout.open("data/input_DFT.dat");
    for (int i = 0; i < transformedSignal.size(); i++) fout << k_vals[i]/float(N) * SAMPLING_RATE << ' ' << abs(transformedSignal[i]) << endl;
    fout.close();
    fout.open("data/output.dat");
    for (int i = 0; i < y0.size(); i++) fout << t_Samples[i] << ' ' << y0[i] << endl;
    fout.close();
    fout.open("data/IR.dat");
    for (int i = 0; i < h.size(); i++) fout << i << ' ' << h[i] << endl;
    fout.close();
    fout.open("data/freq_response.dat");
    for (int i = 0; i < k_vals.size(); i++) fout << k_vals[i]/NYQUIST << ' ' << abs(Freq_Response[i]) << endl;
    fout.close();

    // *** PLOT WITH GNUPLOT ***
    system("gnuplot --persist \"input.plt\"");
    system("gnuplot --persist \"output.plt\"");
    system("gnuplot --persist \"input_DFT.plt\"");
    system("gnuplot --persist \"moving_avg.plt\"");
    system("gnuplot --persist \"IR.plt\"");
    system("gnuplot --persist \"freq_response.plt\"");

    return EXIT_SUCCESS;
}