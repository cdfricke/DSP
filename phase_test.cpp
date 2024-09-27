/*
Programmer: Connor Fricke (cd.fricke23@gmail.com)
File: phase_test.cpp
Latest Revision: 19-Aug-2024
Description: Main program for generating multiple equal-frequency signals of various phase shifts,
then passing each signal through the Goertzel filter in order to create a plot of the real
and imaginary components of X(k) for k = 21, N = 126 for various phase shifts.
*/

#include "DSP.h"
#include <fstream>
#include <cstdlib>
#include <iostream>
extern const double PI;

int main() {

    const int N = 126;
    const int k = 21;
    const double SAMPLING_RATE = 100.0e6;

    ofstream fout("data/phase_test.dat");

    // *** SAMPLING CONTROL ***
    vector<double> t_Samples = generateTiming(SAMPLING_RATE, N);

    vector<double> signal;
    for (double phi = 0.0; phi < 2*PI; phi += 0.1)
    {
        vector<SignalComponent> components = {{1.0, (SAMPLING_RATE / 6.0), phi}};
        signal = generateSignal(t_Samples, components);
        dcomp Xk = goertzel_IIR(signal, k);
        fout << phi << " " << Xk.real() << " " << Xk.imag() << endl;
    }

    int EXIT = system("gnuplot \"plt/phase_test.plt\"");
    if (EXIT) cerr << "Failed to plot phase test results." << endl;

    return 0;
}