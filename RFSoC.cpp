/*
Programmer: Connor Fricke (cd.fricke23@gmail.com)
File: RFSoC.cpp
Latest Rev: 22-Aug-2024
Desc: Simulation of continuous wave detection using Goertzel Algorithm
with 3 GSPS signal (@ 500 MHz) for 375 MHz clock (decimation-in-time of signal by 8)
to illustrate aliasing results. Expected peak frequency detection at 125 MHz (k = ) 
*/

#include "DSP.h"
#include <fstream>
#include <cstdlib>
#include <iostream>

using namespace DSP;
extern const double PI;

int main()
{
    const int N = 2016;     // if we decimate by 8, we get N = 252
    const double SAMPLING_RATE = 3.0e9;     // 3 GSPS from ADC
    const int DECIMATION_FACTOR = 8;

    // * SAMPLING CONTROL *
    std::vector<double> t_samples = generateTiming(SAMPLING_RATE, N);

    std::vector<SignalComponent> components = {{1.0, 62.5e6, 0.0}};
    std::vector<double> signal = generateSignal(t_samples, components);

    // take sample # 0, 8, 16, 24...
    std::vector<double> signal_decimated = decimateSignal(signal, DECIMATION_FACTOR);
    std::vector<double> t_samples_decimated = decimateSignal(t_samples, DECIMATION_FACTOR);

    // * DFT INTEGER VALS *
    std::vector<int> k_samples;
    std::vector<int> k_samples_decimated;
    for (int i = 0; i < N / 2; i++)
        k_samples.push_back(i);
    for (int i = 0; i < N / 16; i++)
        k_samples_decimated.push_back(i);

    // ** PERFORM FULL DFT USING DFT() OR goertzel_IIR() FOR DECIMATED AND UNDECIMATED **
    std::vector<dcomp> signal_DFT;
    for (int k : k_samples)
        signal_DFT.push_back(goertzel_IIR(signal, k));
    std::vector<dcomp> signal_decimated_DFT;
    for (int k : k_samples_decimated)
        signal_decimated_DFT.push_back(goertzel_IIR(signal_decimated, k));

    std::ofstream fout;
    fout.open("data/62_5MHz.dat");
    for (int i = 0; i < signal.size(); i++)
    {
        fout << t_samples[i] << " " << signal[i] << std::endl;
    }
    fout.close();
    fout.open("data/62_5MHz_decimated.dat");
    for (int i = 0; i < signal_decimated.size(); i++)
    {
        fout << t_samples_decimated[i] << " " << signal_decimated[i] << std::endl;
    }
    fout.close();

    fout.open("data/3GSPS_DFT_2.dat");
    for (int i = 0; i < signal_DFT.size(); i++)
        fout << k_samples[i] << " " << abs(signal_DFT[i]) << std::endl;
    fout.close();
    fout.open("data/375MSPS_DFT_2.dat");
    for (int i = 0; i < signal_decimated_DFT.size(); i++)
        fout << k_samples_decimated[i] << " " << abs(signal_decimated_DFT[i]) << std::endl;
    fout.close();

    int EXIT = system("gnuplot \"plt/RFSoC.plt\"");
    EXIT = system("gnuplot \"plt/RFSoC_dfts.plt\""); 
    return 0;
}