/*
Programmer: Connor Fricke (cd.fricke23@gmail.com)
File: aliasing.cpp
Latest Revision: 27-Aug-2024
Desc: Main program for determining frequencies in the range of 0-1500MHz which alias to
31.75 MHz with a sampling rate of 375/2 = 187.5 MSPS such that k/N = 1/6 in the Goertzel algorithm.
*/

#include <iostream>
#include <string>
#include <fstream>
#include "inc/DSP.h"

using std::to_string;

int main() {

    bool WRITE_DATA = false;

    const int N_F = 2016;                       // the length of our Goertzel window for the "Full" 3 GSPS sampling rate
    const int DEC_FACTOR = 16;                  // decimation factor, i.e. w take one out of every DEC_FACTOR samples for the Goertzel alg
    const int N_D = N_F/DEC_FACTOR;             // the length of our actual Goertzel window at the RFSoC clock rate 375 MSPS
    const double ADC_CLK = 3.0e9;               // ADC Sample Rate
    const double GZ_CLK = ADC_CLK/DEC_FACTOR;   // Goertzel Sample Rate ( RFSoC CLK / 2 )

    
    // * determines all frequencies in the range (increment of 100 kHz) which alias to within EPSILON Hz of the target frequency.
    double TARGET_FREQ = 31.25e6;    // target frequency resulting from aliasing of higher frequencies
    double EPSILON = 0.1;           // error range for resulting aliased frequencies
    double FREQ_INC = 50.0e3;      // frequency step  

    vector<double> validFreqs;
    
    for (double freq = 0.0; freq <= (ADC_CLK/2.0); freq += FREQ_INC) {
        double aliasedFreq = aliasesTo(freq, GZ_CLK);
        // check that the aliased frequency is within +-EPSILON of the target
        if (abs(aliasedFreq - TARGET_FREQ) < EPSILON) {
            validFreqs.push_back(freq);
        }
    }

    /* SAMPLE TIMING CONTROL */
    vector<double> adc_sample_times = generateTiming(ADC_CLK, N_F);  // time values for samples produced by ADC
    vector<double> gz_sample_times = generateTiming(GZ_CLK, N_D); // time values for samples detected by Goertzel module (1 of every 8)

    ofstream fout;
    vector<SignalComponent> components;
    vector<double> decSignal;
    vector<double> fullSignal;

    for (double freq : validFreqs)
    {
        // generate signal of each frequency at both ADC and RFSoC clk rates
        components = {{1.0, freq, 0.0}};
        decSignal = generateSignal(gz_sample_times, components);
        fullSignal = generateSignal(adc_sample_times, components);

        // output decimated signal to file
        if (WRITE_DATA) {
            string FILENAME = "data/aliasing/signal_" + to_string(int(freq / 1e5)) + ".dat";
            fout.open(FILENAME);
            for (int i = 0; i < decSignal.size(); i++)
                fout << i << " " << gz_sample_times[i] << " " << decSignal[i] << endl;
            fout.close();
            // output full signal to file
            FILENAME = "data/aliasing/signal_" + to_string(int(freq / 1e5)) + "_full.dat";
            fout.open(FILENAME);
            for (int i = 0; i < fullSignal.size(); i++)
                fout << i << " " << adc_sample_times[i] << " " << fullSignal[i] << endl;
            fout.close();
        }   
    }

    cout << "ADC CLK: " << ADC_CLK / (1.0e9) << " GSPS.\n";
    cout << "GZ (Goertzel) CLK: " << GZ_CLK / (1.0e6) << " MHz.\n";
    cout << "ADC Signal Length: " << fullSignal.size() << " samples.\n";
    cout << "GZ Signal Length: " << decSignal.size() << " samples.\n";
    cout << "Decimation: GZ Algorithm takes one of every " << DEC_FACTOR << " samples from ADC.\n";

    dcomp cw_detection = goertzel_IIR(decSignal, decSignal.size()/6);
    cout << "Goertzel CW Detection Results: X(k) = " 
        << cw_detection.real() << " + " << cw_detection.imag() 
        << "i, |X(k)| = " << abs(cw_detection) << endl;

    return 0;
}