#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <cstdlib>
#include <complex>
#include <cmath>
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
    bool FIR = false;
    int SIGNAL_LENGTH = 1000;

    // NOISY SIGNAL
    vector<double> x;
    generateSignal(x, SIGNAL_LENGTH);

    // UNITY SIGNAL
    // vector<double> x(100, 1.0);

    // *** FILTERED SIGNAL ***
    vector<double> y0;
    double alpha = 0.125;                 
    if (FIR) LOWPASS_FIR(x, y0, alpha);
    else AVERAGER_IIR(x, y0, alpha);

    // *** IMPULSE RESPONSE ***
    vector<double> impulse(10, 0);
    impulse[0] = 1;

    vector<double> h;
    if (FIR) LOWPASS_FIR(impulse, h, alpha);
    else AVERAGER_IIR(impulse, h, alpha);

    // *** FREQUENCY RESPONSE ***
    dcomp I = -1;
    I = sqrt(I);
    // set frequency range
    vector<double> k_vals;
    vector<dcomp> Freq_Response;
    for (double i = 0.0; i < 2*PI; i += 0.1)
    {
        k_vals.push_back(i);
    }
    // take DFT over range of k_vals, store result in Freq_response vector
    DFT(h, k_vals, Freq_Response);

    // *** SAVE DATA ***
    ofstream fout;
    fout.open("data/input.dat");
    for (int i = 0; i < x.size(); i++) fout << i << ' ' << x[i] << endl;
    fout.close();
    fout.open("data/output.dat");
    for (int i = 0; i < y0.size(); i++) fout << i << ' ' << y0[i] << endl;
    fout.close();
    fout.open("data/IR.dat");
    for (int i = 0; i < h.size(); i++) fout << i << ' ' << h[i] << endl;
    fout.close();
    fout.open("data/freq_response.dat");
    for (int i = 0; i < k_vals.size(); i++) fout << k_vals[i] << ' ' << abs(Freq_Response[i]) << endl;
    fout.close();

    // *** PLOT WITH GNUPLOT ***
    system("gnuplot --persist \"input.plt\"");
    system("gnuplot --persist \"output.plt\"");
    system("gnuplot --persist \"moving_avg.plt\"");
    system("gnuplot --persist \"IR.plt\"");
    system("gnuplot --persist \"freq_response.plt\"");

    return EXIT_SUCCESS;
}