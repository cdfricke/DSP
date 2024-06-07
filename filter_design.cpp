#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <cstdlib>
#include <complex>
#include <cmath>
using namespace std;
typedef complex<double> dcomp;

// Programmer: Connor Fricke (cd.fricke23@gmail.com)
// File: filter_design.cpp
// Latest Revision: 7-June-2024
// Synopsis: Short program for testing software implementation of filter designs.

const double PI = 2 * asin(1);

// ** FUNCTION PROTOTYPES **
double getRandomFloat(const double, const double);
void generateSignal(vector<double>&, const int);
void LOWPASS_FIR(const double input, double &output, const double a0, const double a1, double &delay0);
void DFT(vector<double> x, vector<double> k_range, vector<dcomp> &output);

// ** MAIN PROGRAM **
int main()
{
    ofstream fout;
    // *** RANDOMIZED, NOISY SIGNAL ***
    int SIGNAL_LENGTH = 1000;
    vector<double> x;
    generateSignal(x, SIGNAL_LENGTH);

    // *** FILTERED SIGNAL ***
    vector<double> y;
    vector<double> a = {0.6, 0.4};
    double delay_reg_0 = 0;
    for (int i = 0; i < x.size(); i++)
    {
        double y_i = 0;
        LOWPASS_FIR(x[i], y_i, a[0], a[1], delay_reg_0);
        y.push_back(y_i);
    }

    // *** IMPULSE RESPONSE ***
    vector<double> impulse(10, 0);
    impulse[0] = 1;

    vector<double> h;
    double delay_reg_1 = 0;
    for (int i = 0; i < impulse.size(); i++)
    {
        double h_i = 0;
        LOWPASS_FIR(impulse[i], h_i, a[0], a[1], delay_reg_1);
        h.push_back(h_i);
    }

    // *** FREQUENCY RESPONSE ***
    fout.open("data/freq_response.dat");
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
    for (int i = 0; i < k_vals.size(); i++) fout << k_vals[i] << ' ' << abs(Freq_Response[i]) << endl;

    // *** SAVE DATA ***
    fout.close();
    fout.open("data/input.dat");
    for (int i = 0; i < x.size(); i++) fout << i << ' ' << x[i] << endl;
    fout.close();
    fout.open("data/output.dat");
    for (int i = 0; i < y.size(); i++) fout << i << ' ' << y[i] << endl;
    fout.close();
    fout.open("data/IR.dat");
    for (int i = 0; i < h.size(); i++) fout << i << ' ' << h[i] << endl;
    fout.close();

    // *** PLOT WITH GNUPLOT ***
    system("gnuplot --persist \"input.plt\"");
    system("gnuplot --persist \"filtered.plt\"");
    system("gnuplot --persist \"IR.plt\"");
    system("gnuplot --persist \"freq_response.plt\"");

    return 0;
}

// ** FUNCTION DEFINITIONS **

double getRandomFloat(const double lower, const double upper)
{
    random_device rd;
    mt19937 generator(rd());
    uniform_real_distribution<double> distribution(lower, upper);
    
    return distribution(generator);
}

void generateSignal(vector<double>& signal, const int TARGET_LENGTH)
{
    // initialize for the first step
    double currentValue = 0.5;
    double stepSize = 0.0;
    bool stepUp = false;
    while (signal.size() < TARGET_LENGTH)
    {
        // add current value to signal vector
        signal.push_back(currentValue);
        // decide on stepSize, step direction
        stepSize = getRandomFloat(0.0, 0.05);
        stepUp = (getRandomFloat(0.0, 1.0) > 0.5);
        // make step
        if (stepUp) currentValue += stepSize;
        else currentValue -= stepSize;
    }
}

void LOWPASS_FIR(const double input, double &output, const double a0, const double a1, double &delay0)
{
    // rule: 2 coefficients, a0 and a1 -> a0 + a1 = 1
    // DIFFERENCE EQUATION:
    // y[n] = a0*x[n] + a1*x[n-1];
    output = (a0 * input) + (a1 * delay0);
    delay0 = input;
}

void DFT(vector<double> x, vector<double> k_range, vector<dcomp>& output)
{
    dcomp I = -1;
    I = sqrt(I);

    // X(k) = sum_{n=0}^{N-1}{x[n]*W_N^{kn}}
    // W_N = exp(-I*2*PI/N)
    const int N = x.size();
    for (double k : k_range)
    {
        dcomp X = 0.0;
        for (int i = 0; i < N; i++)
        {
            X += x[i] * exp(-I * 2.0 * PI * k * double(i) / double(N));
        }
        output.push_back(X);
    }
}