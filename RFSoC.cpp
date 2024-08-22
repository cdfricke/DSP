/*
Programmer: Connor Fricke (cd.fricke23@gmail.com)
File: RFSoC.cpp
Latest Rev: 22-Aug-2024
Desc: Simulation of continuous wave detection using Goertzel Algorithm
with 3 GSPS signal (@ 500 MHz) for 375 MHz clock (decimation-in-time of signal by 8)
to illustrate aliasing results. Expected peak frequency detection at 125 MHz (k = ) 
*/

#include "inc/DSP.h"
#include <fstream>
#include <cstdlib>
#include <iostream>
extern const double PI;

int main()
{
    const int N = 2016;     // if we decimate by 8, we get N = 252
    const int k = 21;       // TBD
    const double SAMPLING_RATE = 3.0e9;     // 3 GSPS from ADC
    const double SAMPLING_PERIOD = 1.0 / SAMPLING_RATE;
    const int DECIMATION_FACTOR = 8;

    // * SAMPLING CONTROL *
    vector<double> t_samples;
    double t = 0.0;
    for (int i = 0; i < N; i++) {
        t_samples.push_back(t);
        t += SAMPLING_PERIOD;
    }

    vector<SignalComponent> components = {{1.0, 500.0e6, 0.0}};
    vector<double> signal = generateSignal(t_samples, components);

    // take sample # 0, 8, 16, 24...
    vector<double> signal_decimated;
    vector<double> t_samples_decimated;
    for (int i = 0; i < N; i++) {
        if ( (i % DECIMATION_FACTOR) == 0 ) {
            signal_decimated.push_back(signal[i]);
            t_samples_decimated.push_back(t_samples[i]);
        }
    }

    ofstream fout;
    fout.open("data/500MHz.dat");
    for (int i = 0; i < signal.size(); i++)
    {
        fout << t_samples[i] << " " << signal[i] << endl;
    }
    fout.close();
    fout.open("data/500MHz_decimated.dat");
    for (int i = 0; i < signal_decimated.size(); i++)
    {
        fout << t_samples_decimated[i] << " " << signal_decimated[i] << endl;
    }

    int EXIT = system("gnuplot \"plt/RFSoC.plt\"");

    return 0;
}