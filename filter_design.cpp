#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <cstdlib>
#include <complex>
#include <cmath>
#include "DSP.h"
using namespace std;
typedef complex<double> dcomp;

// Programmer: Connor Fricke (cd.fricke23@gmail.com)
// File: filter_design.cpp
// Latest Revision: 7-June-2024
// Synopsis: Short program for testing software implementation of filter designs, as well as my DSP library.

// ** MAIN PROGRAM **
int main()
{
    bool FIR = false;
    // *** RANDOMIZED, NOISY SIGNAL ***
    int SIGNAL_LENGTH = 1000;
    vector<double> x;
    generateSignal(x, SIGNAL_LENGTH);

    // *** FILTERED SIGNAL ***
    vector<double> y0;
    double alpha = 0.125;                 
    // FIRST PASS
    double delay_reg_0 = 0;
    for (int i = 0; i < x.size(); i++)
    {
        double y_i = 0;
        if (FIR) LOWPASS_FIR(x[i], y_i, alpha, delay_reg_0);
        else AVERAGER_IIR(x[i], y_i, alpha, delay_reg_0);
        y0.push_back(y_i);
    }

    // *** IMPULSE RESPONSE ***
    vector<double> impulse(10, 0);
    impulse[0] = 1;

    vector<double> h;
    double delay_reg_1 = 0;
    for (int i = 0; i < impulse.size(); i++)
    {
        double h_i = 0;
        if (FIR) LOWPASS_FIR(impulse[i], h_i, alpha, delay_reg_1);
        else AVERAGER_IIR(impulse[i], h_i, alpha, delay_reg_1);
        h.push_back(h_i);
    }

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
    DFT(h, k_vals, Freq_Response);
    if (k_vals.size() != Freq_Response.size()) return EXIT_FAILURE;
    

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

    return 0;
}