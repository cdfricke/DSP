/*
Programmer: Connor Fricke (cd.fricke23@gmail.com)
File: DSP.h
Latest Revision: 18-June-2024
Synopsis: Header File for DSP function library
*/

#ifdef _WIN32

    /* Define ADD_EXPORTS when building DLL */
    #ifdef DSP_EXPORTS
        #define DSPAPI __declspec(dllexport)
    #else
        #define DSPAPI __declspec(dllimport)
    #endif
    #define DSPCALL __cdecl
#else /*_WIN32 not defined (some other OS)*/
    #define DSPAPI
    #define DSPCALL
#endif

#ifndef DSP_H
    #define DSP_H

    #include <random>
    #include <complex>
    #include <vector>
    #include <cmath>
    using namespace std;

    #ifdef __cplusplus
    extern "C"
    {
    #endif

    struct DSPAPI SignalComponent
    {
        double coeff=1.0;
        double freq=1.0;
        double phase=0.0;
    };

    typedef complex<double> dcomp;

    /*
    getRandomFloat(const double, const double):
        Simply returns a single random number generated with the Mersenne Twister (mt19937)
        over a uniform distribution between the upper and lower bounds parameters.
        @@ parameters:
            const double lower: lower bound to uniform distribution
            const double upper: upper bound to uniform distribution
    */
    DSPAPI double DSPCALL getRandomFloat(const double lower, const double upper);

    /*
    generateSignal(vector<double>& signal, const vector<SignalComponent>&):
        creates a signal with a Fourier sine series expansion method from frequency and coefficients 
        stored by the vector parameter. Discretizes output signal over x_values vector parameter.
        @@ parameters:
            const vector<double>& x_values: discretization vector, i.e. calculate the signal value at these x_values
            const vector<SignalComponent>& components: sine wave signal components, with their frequency and coefficient stored in a struct
        @@ return:
            vector<double> signal: output of function, a signal generated based on signal components
    */
    DSPAPI vector<double> DSPCALL generateSignal(const vector<double> &x_values, const vector<SignalComponent> &components);

    /*
    bool noAliasing(const vector<SignalComponent>& signal, const double SAMPLING_RATE):
        prevents aliasing by returning true if the highest frequency component of the signal is less than the NYQUIST rate
    */
    DSPAPI bool DSPCALL noAliasing(const vector<SignalComponent>& signal, const double SAMPLING_RATE);

    /*
    generateTiming(const double SAMPLING_RATE, const int N)
        generates a vector of time values for samples based on a sampling rate and signal duration 
        in terms of number of samples (N)
    */
    DSPAPI vector<double> DSPCALL generateTiming(const double SAMPLING_RATE, const int N);

    /*
    vector<double> decimateSignal(const vector<double> signal, const int DECIMATION_FACTOR)
        takes every n-th element of the input vector and adds it to the returned vector of resulting floor(len(signal)/n)
    */
    DSPAPI vector<double> DSPCALL decimateSignal(const vector<double> signal, const int DECIMATION_FACTOR);

    /*
    double aliasesTo(const double SIGNAL_FREQ, const double SAMPLING_RATE)
        returns the expected aliased frequency of a signal given a sampling rate lower than the signal frequency.
    */
    DSPAPI double DSPCALL aliasesTo(const double SIGNAL_FREQ, const double SAMPLING_RATE);

    /*
    LOWPASS_FIR(const vector<double>&, vector<double>&, const double):
        Takes in an input vector and output vector as parameters. Applies an FIR Filter
        to the input vector characterized by the difference equation:
            y[n] = a*x[n] + (1-a)*x[n-1]
        @@ parameters:
            const vector<double>& input: represents an unfiltered signal
            const double alpha: defines both taps (coefficients) of the FIR filter via {a, 1-a}.
        @@ return:
            vector<double> output: resulting filtered signal
    */
    DSPAPI vector<double> DSPCALL LOWPASS_FIR(const vector<double> &input, const double alpha);

    /*AVERAGER_IIR(const vector<double>&, vector<double>&, const double) :
        Takes in an input vector and output vector as parameters. Applies an IIR Filter
        to the input vector characterized by the difference equation:
            y[n] = a*x[n] + (1-a)*y[n-1]
        This filter corresponds to a lowpass filter with two taps defined by the third parameter value.
        It is well known as an exponential averaging filter.
        @@ parameters:
            const vector<double>& input: represents an unfiltered signal
            const double alpha: defines both taps (coefficients) of the IIR filter via {a, 1-a}
        @@ return:
            vector<double>& output: resulting filtered signal
    */
    DSPAPI vector<double> DSPCALL AVERAGER_IIR(const vector<double>& input, const double alpha);

    /*
    DFT(const vector<double>&, const vector<double>&, vector<dcomp> out):
        Takes the discrete Fourier Transform of a signal for discrete k values.
        @@ parameters:
            const vector<double>& x: input signal to be transformed
            const vector<int>& k_range: represents the discrete values of k for the DFT to be calculated over. must range from -N/2 to N/2
        @@ return:
            vector<complex<double>>& output: resulting transformed signal. each value is a complex number with real and imaginary components.
    */
    DSPAPI vector<dcomp> DSPCALL DFT(const vector<double>& x, const vector<int>& k_range);

    /*
    goertzelFilter_1(const vector<double>&, const int):
        Performs the 1st - order recursive implementation of a Goertzel Filter for a single integer k-value 
        of an input signal to calculate X(k) = y[N] where y is the output signal of the filter.
            y_k[n] = exp(i * 2 * PI * k / N)*y[n-1]
        @@ parameters:
            const vector<double>& input: input signal to be passed through the filter
            const int k: used in the difference equation
        @@ return:
            complex<double> out: result of Goertzel filtering on input signal
    */
    DSPAPI dcomp DSPCALL goertzel_1(const vector<double>& input, const int k);

    /*
    goertzelFilter_2(const vector<double>&, const int):
        Performs the 2nd - order recursive implementation of a Goertzel Filter for a single integer k-value
        of n input signal to calculate X(k) = y[N] where y is the output signal of the filter, and N is the
        final element in the digital signal.
            y[n] = x[n] - W_Nk*x[n-1] + 2cos(2PIk/N)*y[n-1] - y[n-2]
        @@ parameters:
            const vector<double>& input: input signal to be passed through the filter
            const int k: used in the difference equation
        @@ return:
            complex<double> out: result of Goertzel filtering on input signal
    */
    DSPAPI dcomp DSPCALL goertzel_2(const vector<double> &input, const int k);

    /* 
    goertzel_IIR(const vector<double>&, const int):
        Implements the IIR portion of the Goertzel algorithm. Takes in an input sequence x[n] and 
        first created an intermediate sequence s[n] to then be passed to the FIR portion of the cascade
            s[n] = x[n] + 2cos()s[n-1] - s[n-2]
        The result of this IIR filter is passed to the FIR portion in this function, and the result
        (a complex number whose magnitude is the discrete DFT value for the particular k) is returned.
        This implementation is most similar to a hardware (FPGA) implementation of the Goertzel filter.
        @@ parameters:
            const vector<double>& input: input signal to be passed through the filter
            const int k: used in the difference equation
        @@ return:
            complex<double> out: result of Goertzel filtering on input signal
    */
    DSPAPI dcomp DSPCALL goertzel_IIR(const vector<double> &input, const int k);

    #ifdef __cplusplus
    }
    #endif

#endif