#include <iostream>
#include <fstream>
#include <cstdlib> // for system()
#include <cassert>
#include "DSP.h"

using namespace std;
extern const double PI;

// Programmer: Connor Fricke (cd.fricke23@gmail.com)
// File: goertzel_tb.cpp
// Latest Revision: 26-July-2024
// Synopsis: Short program for testing Goertzel algorithm model.
// See Goertzel Algorithm Wiki: https://en.wikipedia.org/wiki/Goertzel_algorithm

// ** MAIN PROGRAM **
int main()
{
    // parameters
    bool FIR = false;                 // decides which filter is applied. Both have two taps chosen by alpha
    double alpha = 0.125;             // filter coeffs are {a, 1-a}
    double SAMPLING_RATE = 100.0e+06; // 100 MHz Arty A7 clock frequency
    double SAMPLING_PERIOD = 1.0 / SAMPLING_RATE;
    double NYQUIST = SAMPLING_RATE / 2.0;
    int N = 60; 

    // *** USER-CREATED SIGNAL ***
    // to create a signal with sine wave components, you need a vector of SignalComponents,
    // and a vector of discrete t values which tells us where the samples of the signal are.
    // The SignalComponent initialized as {0.1, 5.0} corresponds to 0.2sin(5.0t) in the Fourier series, for example.
    // if we create a signal with all frequencies from zero to nyquist, we should get an impulsive signal
    vector<SignalComponent> components = {{1.0, (100.0e6 / 6.0)}};

    // find minimum and maximum components
    double minFreq = components[0].freq;
    double maxFreq = components[0].freq;
    for (SignalComponent c : components)
    {
        if (c.freq < minFreq)
            minFreq = c.freq;
        if (c.freq > maxFreq)
            maxFreq = c.freq;
    }
    assert(maxFreq < NYQUIST);

    // *** SAMPLING CONTROL ***
    vector<double> t_Samples;
    double t = 0.0;
    while (t_Samples.size() < N)
    {
        t_Samples.push_back(t);
        t += SAMPLING_PERIOD;
    }
    // once we have the signal components and sampling control set, we can call generateSignal()
    vector<double> x = generateSignal(t_Samples, components);

    // *** FREQUENCY (k) DISCRETIZATION ***
    vector<int> k_vals;
    for (int i = -N / 2; i < (N / 2) + 1; i++)
        k_vals.push_back(i);

    ofstream fout;
    fout.open("data/goertzel.dat");
    for (int i = 0; i < N; i++)
    {
        int k = k_vals[i];
        fout << k << " " << double(k)*SAMPLING_RATE / double(N) << " " << abs(goertzel_IIR_FIR(x,k)) << endl;
    }
    fout.close();

    int EXIT = system("gnuplot --persist \"plt/goertzel.plt\"");

    return EXIT_SUCCESS;
}