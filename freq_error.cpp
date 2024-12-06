/*
Programmer: Connor Fricke
File: freq_error.cpp
Latest Rev: 4-Dec-2024
Desc: Simulation of Goertzel filter output over a range of frequencies around the target frequency.
*/

#include <fstream>
#include <iostream>
#include "DSP.h"

using std::vector;

int main() {

    const int N = 126;
    const double SAMPLE_RATE = 187.5e6;

    std::ofstream fout;
    fout.open("./data/freq_error.dat");
    fout << "freq Xk_re Xk_im Xk_mag Xk_err\n";

    vector<double> t = DSP::generateTiming(SAMPLE_RATE, N);

    for (double freq = 22.25e6; freq < 40.25e6; freq += 0.01e6) {
        DSP::SignalComponent component;
        component.freq = freq;
        vector<double> signal = DSP::generateSignal(t, {component});
        
        DSP::dcomp Xk = DSP::goertzel_IIR(signal, 21);

        double Xk_re = Xk.real();
        double Xk_im = Xk.imag();
        double Xk_mag = sqrt((Xk_re * Xk_re) + (Xk_im * Xk_im));
        double Xk_err = (Xk_mag - 63.0) / 63.0;

        fout << freq << ' ' << Xk_re << ' ' << Xk_im << ' ' << Xk_mag << ' ' << Xk_err << '\n';
    }

    return 0;
}