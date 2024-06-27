#include <iostream>
#include <fstream>  
#include <cstdlib>  // for system()
#include <cassert>
#include <chrono>   // for timing with high res clock
#include "DSP.h"

using namespace std;
using chrono::duration_cast, chrono::microseconds, chrono::high_resolution_clock;
extern const double PI;

// Programmer: Connor Fricke (cd.fricke23@gmail.com)
// File: filter_design.cpp
// Latest Revision: 18-June-2024
// Synopsis: Short program for testing software implementation of filter designs, as well as my DSP library.

// ** MAIN PROGRAM **
int main()
{
    // parameters
    bool FIR = false;                       // decides which filter is applied. Both have two taps chosen by alpha
    double alpha = 0.125;                   // filter coeffs are {a, 1-a}
    double SAMPLING_RATE = 12.0e+06;        // 12 MHz CMOD clock frequency
    double SAMPLING_PERIOD = 1.0 / SAMPLING_RATE;
    double NYQUIST = SAMPLING_RATE / 2.0;

    // *** USER-CREATED SIGNAL ***
    // to create a signal with sine wave components, you need a vector of SignalComponents,
    // and a vector of discrete t values which tells us where the samples of the signal are.
    // The SignalComponent initialized as {0.1, 5.0} corresponds to 0.2sin(5.0t) in the Fourier series, for example.
    // if we create a signal with all frequencies from zero to nyquist, we should get an impulsive signal
    vector<SignalComponent> components{{1.0, 500e+03}, {0.5, 1e+06}, {0.25, 2e+06}};
    // find minimum and maximum components
    double minFreq = components[0].freq;
    double maxFreq = components[0].freq;
    for (SignalComponent c : components)
    {
        if (c.freq < minFreq) minFreq = c.freq;
        if (c.freq > maxFreq) maxFreq = c.freq;
    }
    assert(maxFreq < NYQUIST);

    double SIGNAL_DURATION = 2.0 / minFreq; // should be on the order of the period of the lowest freq component in our signal

    // *** SAMPLING CONTROL ***
    vector<double> t_Samples;
    for (double i = 0.0; i < SIGNAL_DURATION; i += SAMPLING_PERIOD) t_Samples.push_back(i);
    int N = t_Samples.size();
    // once we have the signal components and sampling control set, we can call generateSignal()
    vector<double> x = generateSignal(t_Samples, components);

    // *** FREQUENCY (k) DISCRETIZATION ***
    vector<int> k_vals;
    for (int i = -N / 2; i < N / 2; i++) k_vals.push_back(i);

    // *** DFT ***
    auto startDFT = high_resolution_clock::now();

    // *********** BEGIN
    vector<dcomp> transformedSignal0 = DFT(x, k_vals);
    // *********** END

    auto stopDFT = high_resolution_clock::now();    
    auto DFT_duration = duration_cast<microseconds>(stopDFT - startDFT);
    cout << "DFT Duration: " << DFT_duration.count() << " microseconds.\n";

    // *** GOERTZEL ALGORITHM, ALL K VALUES OF DFT ***
    auto startGA = high_resolution_clock::now();

    // *********************************************** BEGIN
    vector<dcomp> transformedSignal;
    for (int k : k_vals)
    {
        vector<dcomp> y_k = goertzelFilter_1(x, k);
        // X(k) is the Nth value in the filtered signal (last value)
        dcomp X = y_k.back();
        transformedSignal.push_back(X);
    }
    // *********************************************** END

    auto stopGA = high_resolution_clock::now();
    auto GA_duration = duration_cast<microseconds>(stopGA - startGA);
    cout << "Goertzel Algorithm Duration, All Frequencies: " << GA_duration.count() << " microseconds.\n";

    // *** GOERTZEL ALGORITHM, ONLY THREE K VALUES OF DFT ***
    
    auto startGA_short = high_resolution_clock::now();

    // ****************************************************** BEGIN
    vector<dcomp> y_5 = goertzelFilter_1(x, 5);
    vector<dcomp> y_6 = goertzelFilter_1(x, 6);
    vector<dcomp> y_7 = goertzelFilter_1(x, 7);
    // ****************************************************** END

    auto stopGA_short = high_resolution_clock::now();
    auto GA_duration_short = duration_cast<microseconds>(stopGA_short - startGA_short);
    cout << "Goertzel Algorithm Duration, 3 Frequencies: " << GA_duration_short.count() << " microseconds.\n";

    // *** FILTERED SIGNAL ***
    vector<double> y0;
    if (FIR) y0 = LOWPASS_FIR(x, alpha);
    else y0 = AVERAGER_IIR(x, alpha);

    // *** IMPULSE RESPONSE ***
    // impulse signal duration = 100
    vector<double> impulse(100, 0);
    impulse[0] = 1;
    vector<double> h; 
    if (FIR)
        h = LOWPASS_FIR(impulse, alpha);
    else
        h = AVERAGER_IIR(impulse, alpha);

    // *** FREQUENCY RESPONSE ***
    dcomp I = -1;
    I = sqrt(I);
    vector<dcomp> Freq_Response = DFT(h, k_vals);

    // *** SAVE DATA ***
    ofstream fout;
    fout.open("data/input.dat");
    for (int i = 0; i < x.size(); i++) fout << t_Samples[i] << ' ' << x[i] << endl;
    fout.close();
    fout.open("data/input_DFT.dat");
    for (int i = 0; i < transformedSignal.size(); i++) fout << k_vals[i]/double(N) * SAMPLING_RATE << ' ' << abs(transformedSignal[i]) << endl;
    fout.close();
    fout.open("data/output.dat");
    for (int i = 0; i < y0.size(); i++) fout << t_Samples[i] << ' ' << y0[i] << endl;
    fout.close();
    fout.open("data/IR.dat");
    for (int i = 0; i < h.size(); i++) fout << i << ' ' << h[i] << endl;
    fout.close();
    fout.open("data/freq_response.dat");
    for (int i = 0; i < k_vals.size(); i++) fout << k_vals[i]/(double(N)*NYQUIST) << ' ' << abs(Freq_Response[i]) << endl;
    fout.close();

    // *** PLOT WITH GNUPLOT, SYSTEM() SHOULD RETURN 0 ***
    int EXIT;

    EXIT = system("gnuplot --persist \"input.plt\"");
    if (EXIT) cerr << "Failed to plot input.\n";

    EXIT = system("gnuplot --persist \"output.plt\"");
    if (EXIT) cerr << "Failed to plot output.\n";

    EXIT = system("gnuplot --persist \"input_DFT.plt\"");
    if (EXIT) cerr << "Failed to plot input signal DFT.\n";

    EXIT = system("gnuplot --persist \"moving_avg.plt\"");
    if (EXIT) cerr << "Failed to plot input/output comparison.\n";

    EXIT = system("gnuplot --persist \"IR.plt\"");
    if (EXIT) cerr << "Failed to plot impulse response.\n";

    EXIT = system("gnuplot --persist \"freq_response.plt\"");
    if (EXIT) cerr << "Failed to plot frequency response.\n";

    return EXIT_SUCCESS;
}