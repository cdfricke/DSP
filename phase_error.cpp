#include <iostream>
#include <fstream>
#include <cstdlib> // for system()
#include <iomanip>
#include "DSP.h"   // my personal DSP library for this project

using namespace DSP;

extern const double PI;

// Programmer: Connor Fricke (cd.fricke23@gmail.com)
// File: phase_error.cpp
// Latest Revision: 26-Nov-2024
// Desc: Program for testing error response to varying phase

int main() {

    // output file
    std::ofstream fout;
    fout.open("./data/phase_testing.dat", std::ios_base::out);
    fout << "phase Re{X(k)} Im{X(k)} Error\n"; 

    const double SAMPLE_RATE = 187.5e6;
    const double LENGTH = 126;
    const double SIG_FREQ = 31.25e6;
    const double SIG_AMPL = 1.0;
    const double PHI_STEP = 2 * PI / 1000;

    std::vector<double> timing = generateTiming(SAMPLE_RATE, LENGTH);

        for (double phi = -PI; phi <= PI; phi += PHI_STEP) {

            std::vector<SignalComponent> sineWaveComponents = {{SIG_AMPL, SIG_FREQ, phi}};
            std::vector<double> sineWave = generateSignal(timing, sineWaveComponents);

            dcomp Xk = goertzel_IIR(sineWave, LENGTH / 6);
            double error = (abs(Xk) - 63.0) / 63.0;
            if (error < 0.0)
            {
                error *= -1.0;
        }
                
        fout << std::setprecision(10) << phi << " " << Xk.real() << " " << Xk.imag() << " " << error << std::endl;
    }

    fout.close();
    return 0;
}