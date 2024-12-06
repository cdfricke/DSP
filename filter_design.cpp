#include <iostream>
#include <fstream>  
#include <cstdlib>      // for system()
#include <cassert>      // for assert()
#include <chrono>       // for timing with high res clock
#include "DSP.h"    // my personal DSP library for this project

using namespace DSP;
using std::chrono::duration_cast, std::chrono::microseconds, std::chrono::high_resolution_clock;
extern const double PI;

// Programmer: Connor Fricke (cd.fricke23@gmail.com)
// File: filter_design.cpp
// Latest Revision: 18-June-2024
// Synopsis: Short program for testing software implementation of filter designs, as well as my DSP library.

// ** MAIN PROGRAM **
int main()
{
    // parameters
    bool    FIR = false;                            // decides which filter is applied. Both have two taps chosen by alpha
    double  alpha = 0.125;                          // filter coeffs are {a, 1-a}
    double  SAMPLING_RATE = 100.0e+06;              // 100 MHz Arty A7 clock frequency
    double  SAMPLING_PERIOD = 1.0 / SAMPLING_RATE;
    double  NYQUIST = SAMPLING_RATE / 2.0;

    // *** USER-CREATED SIGNAL ***
    std::vector<SignalComponent> components = {{1.0, (100.0e6 / 6.0), 0.0}};
    assert(noAliasing(components, SAMPLING_RATE));

    int N = 126;

    // *** SAMPLING CONTROL ***
    std::vector<double> t_Samples = generateTiming(SAMPLING_RATE, N);

    // once we have the signal components and sampling control set, we can call generateSignal()
    std::vector<double> x = generateSignal(t_Samples, components);

    // *** FREQUENCY (k) DISCRETIZATION ***
    std::vector<int> k_vals;
    for (int i = -N / 2; i < (N / 2) + 1; i++) k_vals.push_back(i);

    // *** DFT ***
    auto startDFT = high_resolution_clock::now();

    // *********** BEGIN
    std::vector<dcomp> transformedSignal0 = DFT(x, k_vals);
    // *********** END

    auto stopDFT = high_resolution_clock::now();    
    auto DFT_duration = duration_cast<microseconds>(stopDFT - startDFT);
    std::cout << "DFT Duration: " << DFT_duration.count() << " microseconds.\n";

    // *** GOERTZEL ALGORITHM FIRST ORDER, ALL K VALUES OF DFT ***
    auto startGA1 = high_resolution_clock::now();

        // *********************************************** BEGIN
        std::vector<dcomp> transformedSignal1;
        for (int k : k_vals)
        {
            dcomp X = goertzel_1(x, k);
            // X(k) is the Nth value in the filtered signal (last value)
            transformedSignal1.push_back(X);
        }
        // *********************************************** END

    auto stopGA1 = high_resolution_clock::now();
    auto GA1_duration = duration_cast<microseconds>(stopGA1 - startGA1);
    std::cout << "Goertzel Algorithm, First Order Duration, All Frequencies: " << GA1_duration.count() << " microseconds.\n";

    // *** GOERTZEL ALGORITHM SECOND ORDER, ALL K VALUES OF DFT ***

    auto startGA2 = high_resolution_clock::now();

        // *********************************************** BEGIN
        std::vector<dcomp> transformedSignal2;
        for (int k : k_vals)
        {
            dcomp y_k = goertzel_IIR(x, k);
            transformedSignal2.push_back(y_k);
        }
        // *********************************************** END

    auto stopGA2 = high_resolution_clock::now();
    auto GA2_duration = duration_cast<microseconds>(stopGA2 - startGA2);
    std::cout << "Goertzel Algorithm, Second Order Duration, All Frequencies: " << GA2_duration.count() << " microseconds.\n";

    // *** GOERTZEL ALGORITHM FIRST ORDER, ONLY THREE K VALUES OF DFT ***
    
    auto startGA_short = high_resolution_clock::now();

        // ****************************************************** BEGIN
        dcomp y_5 = goertzel_1(x, 5);
        dcomp y_6 = goertzel_1(x, 6);
        dcomp y_7 = goertzel_1(x, 7);
        // ****************************************************** END

    auto stopGA_short = high_resolution_clock::now();
    auto GA_duration_short = duration_cast<microseconds>(stopGA_short - startGA_short);
    std::cout << "Goertzel Algorithm Duration, 3 Frequencies: " << GA_duration_short.count() << " microseconds.\n";

    // *** FILTERED SIGNAL ***
    std::vector<double> y0;
    if (FIR) y0 = LOWPASS_FIR(x, alpha);
    else y0 = AVERAGER_IIR(x, alpha);

    // *** IMPULSE RESPONSE ***
    // impulse signal duration = 100
    std::vector<double> impulse(N, 0);
    impulse[0] = 1;
    std::vector<double> h;
    if (FIR)
        h = LOWPASS_FIR(impulse, alpha);
    else
        h = AVERAGER_IIR(impulse, alpha);

    // *** FREQUENCY RESPONSE ***
    dcomp I = -1;
    I = sqrt(I);
    std::vector<dcomp> Freq_Response = DFT(h, k_vals);

    // ** CALCULATE PEAK FREQUENCY **
    double currentMax = 0.0;
    int maxK = 0;
    for (int i = 0; i < transformedSignal2.size(); i++)
    {
        if (abs(transformedSignal2[i]) > currentMax) { 
            currentMax = abs(transformedSignal2[i]);
            maxK = k_vals[i];
        }
    }

    // ** PRINT INFO **
    std::cout << "PARAMETERS:" << std::endl
              << "sampling rate: " << SAMPLING_RATE << std::endl
              << "nyquist: " << NYQUIST << std::endl
              << "signal components: " << std::endl;
    for (SignalComponent c : components)
        std::cout << "\t" << c.freq << std::endl;
    std::cout << "N: " << N << std::endl;
    std::cout << "Peak Freq: k = " << abs(maxK) << ", freq = " << (abs(maxK) * SAMPLING_RATE) / double(N) << std::endl;

    // *** SAVE DATA ***
    std::ofstream fout;
    fout.open("data/input.dat");
    for (int i = 0; i < x.size(); i++) 
        fout << t_Samples[i] << ' ' << x[i] << std::endl;
    fout.close();
    fout.open("data/input_DFT.dat");
    for (int i = 0; i < transformedSignal2.size(); i++)
        fout << k_vals[i] / double(N) * SAMPLING_RATE << ' ' << abs(transformedSignal2[i]) << std::endl;
    fout.close();
    fout.open("data/output.dat");
    for (int i = 0; i < y0.size(); i++)
        fout << t_Samples[i] << ' ' << y0[i] << std::endl;
    fout.close();
    fout.open("data/IR.dat");
    for (int i = 0; i < h.size(); i++)
        fout << i << ' ' << h[i] << std::endl;
    fout.close();
    fout.open("data/freq_response.dat");
    for (int i = 0; i < k_vals.size(); i++)
        fout << k_vals[i] / double(N) << ' ' << abs(Freq_Response[i]) << std::endl;
    fout.close();

    // *** PLOT WITH GNUPLOT, SYSTEM() SHOULD RETURN 0 ***
    int EXIT = 0;

    EXIT = system("gnuplot --persist \"plt/input.plt\"");
    if (EXIT)
        std::cerr << "Failed to plot input.\n";

    EXIT = system("gnuplot --persist \"plt/input_DFT.plt\"");
    if (EXIT)
        std::cerr << "Failed to plot input signal DFT.\n";

    EXIT = system("gnuplot --persist \"plt/comparison.plt\"");
    if (EXIT)
        std::cerr << "Failed to plot input/output comparison.\n";

    EXIT = system("gnuplot --persist \"plt/IR.plt\"");
    if (EXIT)
        std::cerr << "Failed to plot impulse response.\n";

    EXIT = system("gnuplot --persist \"plt/freq_response.plt\"");
    if (EXIT)
        std::cerr << "Failed to plot frequency response.\n";

    return EXIT_SUCCESS;
}