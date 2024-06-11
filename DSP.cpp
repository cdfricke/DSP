/*
Programmer: Connor Fricke (cd.fricke23@gmail.com)
File: DSP.cpp
Latest Revision: 11-June-2024
Synopsis: Implementation File for DSP function library
*/

#include "DSP.h"

extern const double PI = 2 * asin(1);

double getRandomFloat(const double lower, const double upper)
{
    random_device rd;
    mt19937 generator(rd());
    uniform_real_distribution<double> distribution(lower, upper);

    return distribution(generator);
}

void generateSignal(vector<double> &signal, const int TARGET_LENGTH)
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
        if (stepUp)
            currentValue += stepSize;
        else
            currentValue -= stepSize;
    }
}


void DFT(const vector<double>& x, const vector<double>& k_range, vector<complex<double>>& output)
{
    complex<double> I = -1;
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

void LOWPASS_FIR(const vector<double>& input, vector<double>& output, const double alpha)
{
    double delay0 = 0;
    for (double in : input) 
    {
        double out = (alpha * in) + ((1.0 - alpha) * delay0);
        output.push_back(out);
        delay0 = in;
    }
}


void AVERAGER_IIR(const vector<double>& input, vector<double>& output, const double alpha)
{
    double delay0 = 0;
    for (double in : input)
    {
        // DIFFERENCE EQUATION:
        // y[n] = a*x[n] + (1-a)*y[n-1]
        double out = (alpha * in) + ((1.0 - alpha) * delay0);
        delay0 = out;
        output.push_back(out);
    }
}