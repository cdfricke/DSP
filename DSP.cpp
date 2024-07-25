/*
Programmer: Connor Fricke (cd.fricke23@gmail.com)
File: DSP.cpp
Latest Revision: 18-June-2024
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

vector<double> generateSignal(const vector<double> t_Samples)
{
    vector<double> output;
    // initialize for the first step
    double currentValue = 0.5;
    double stepSize = 0.0;
    bool stepUp = false;
    while(output.size() < t_Samples.size())
    {
        // add current value to signal vector
        output.push_back(currentValue);
        // decide on stepSize, step direction
        stepSize = getRandomFloat(0.0, 0.05);
        stepUp = (getRandomFloat(0.0, 1.0) > 0.5);
        // make step
        if (stepUp)
            currentValue += stepSize;
        else
            currentValue -= stepSize;
    }
    return output;
}


vector<double> generateSignal(const vector<double>& t_values, const vector<SignalComponent> &components)
{
    vector<double> output;
    for (double t : t_values)
    {
        double currentValue = 0.0;
        
        for (SignalComponent c : components)
        {
            // cos takes radians argument so we multiply by 2PI because freq is units of Hz
            currentValue += c.coeff * cos(2.0 * PI * c.freq * t);
        }
        
        output.push_back(currentValue);
    }
    return output;
}


vector<dcomp> DFT(const vector<double> &x, const vector<int> &k_range)
{
    vector<dcomp> output;
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
    return output;
}

vector<double> LOWPASS_FIR(const vector<double>& input, const double alpha)
{
    vector<double> output;
    double delay0 = 0;
    for (double in : input) 
    {
        double out = (alpha * in) + ((1.0 - alpha) * delay0);
        output.push_back(out);
        delay0 = in;
    }
    return output;
}


vector<double> AVERAGER_IIR(const vector<double>& input, const double alpha)
{
    vector<double> output;
    double delay0 = 0;
    for (double in : input)
    {
        // DIFFERENCE EQUATION:
        // y[n] = a*x[n] + (1-a)*y[n-1]
        double out = (alpha * in) + ((1.0 - alpha) * delay0);
        delay0 = out;
        output.push_back(out);
    }
    return output;
}

vector<dcomp> goertzelFilter_1(const vector<double>& input, const int k)
{
    vector<dcomp> output;
    dcomp I = -1;
    I = sqrt(I);
    int N = input.size();

    dcomp delay0 = 0;
    for (double in : input)
    {
        // convert real number input to complex value with only real component
        dcomp c_in = complex(in, 0.0); 
        // DIFFERENCE EQUATION:
        // y[n] = x[n] + exp(i * 2 * PI * k / N) * y[n - 1]
        dcomp out = c_in + exp(I * 2.0 * PI * double(k) / double(N))*delay0;
        delay0 = out;
        output.push_back(out);
    }
    return output;
}

dpair goertzelFilter_2(const vector<double> &input, const int k)
{
    int N = input.size();

    // IIR delay registers for re and im calculations
    double dro0_re = 0;     // Re{y[n-1]}
    double dro1_re = 0;     // Re{y[n-2]}

    double dro0_im = 0;     // Im{y[n-1]}
    double dro1_im = 0;     // Im{y[n-2]}

    // FIR delay register
    double dri = 0;         // x[n-1]

    // compute constant coefficients
    const double phase = 2.0 * PI * double(k) / double(N);
    const double COS = cos(phase);
    const double SIN = sin(phase);
    double out_Re=0, out_Im=0;

    int n = 0;
    for (double in : input)
    {
        // DIFFERENCE EQUATION:
        // Re{y[n]} = x[n] - cos(2PIk/N)*x[n-1] + 2cos(2PIk/N)*Re{y[n-1]} - Re{y[n-2]}
        // Im{y[n]} = sin(2PIk/N)*x[n-1] + 2cos(2PIk/N)*Im{y[n-1]} - Im{y[n-2]}
        out_Re = ( in ) - ( COS*dri ) + ( 2*COS*dro0_re ) - ( dro1_re );
        out_Im = ( SIN * dri ) + ( 2*COS*dro0_im ) - ( dro1_im );

        // update delay regs
        dri = in;           // x[n] -> x[n-1]

        dro1_re = dro0_re;  // Re{y[n-1]} -> Re{y[n-2]}
        dro0_re = out_Re;   // Re{y[n]} -> Re{y[n-1]}
        
        dro1_im = dro0_im;  // Im{y[n-1]} -> Im{y[n-2]}
        dro0_im = out_Im;   // Im{y[n]} -> Im{y[n-1]}
    }

    return dpair{out_Re, out_Im};
}