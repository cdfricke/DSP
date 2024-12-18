# Programmer: Connor Fricke (cd.fricke23@gmail.com)
# File: phase_increment.py
# Latest Revision: 25-June-2024
# Description:
# If this script is run, it will prompt the user for a desired frequency of the wave generator
# module (wave_generator.v) which uses the CORDIC IP from AMD to generate continuous wave signals.
# It returns the required phase increment parameter that should be passed to the wave_generator.v 
# module in order to produce a signal of that frequency.

from math import cos, pi
import numpy as np

# global constants
CLK_FREQ = 375e6 # Hz
FRAC_BITS = 13    # number of fractional bits used to represent the input phase to CORDIC
TWO_PI = round(2 * pi * (2**FRAC_BITS))       # two's complement representation of 2pi for phase input

def samplesPerPeriod(PHASE_INC: int) -> int:
    """
    Calculates the number of samples in a single period of the wave generated by the
    CORDIC IP given the phase increment value.
    @@ parameters:
        PHASE_INC : int : the phase increment parameter for the wave_generator.v module. It sets
        the integer value that the phase input increases each clock cycle for the CORDIC IP.
    @@ return:
        int: expected number of samples in each cycle of the resulting output signal from the wave_generator.v module.
    """
    samples = 1
    phase = 0
    while (phase + PHASE_INC < TWO_PI):
        phase += PHASE_INC
        samples += 1
    return samples

def getPhaseInc(possibleFreqs, desiredFreq) -> int:
    """
    @@ parameters:
        - possibleFreqs : [(phaseInc, freq)] : a NumPy array of tuples of corresponding pairs
        of phase increments and the resulting output frequency of the CORDIC IP.
        - desiredFreq : float : a floating point value representing the desired frequency
        output by the CORDIC IP
    @@ return:
        - given a particular desired frequency, the return value of this function is
        an integer type representing the required phase increment parameter to be passed
        to the CORDIC IP wave generator module.
    """
    previousDifference = abs(possibleFreqs[0][1] - desiredFreq)
    result = 0
    for pair in possibleFreqs:
        newDifference = abs(pair[1] - desiredFreq)
        if newDifference < previousDifference:
            result = pair[0]
        previousDifference = newDifference
    return result

def getFreqOut(PHASE_INC: int, SAMPLE_RATE: float) -> float:
    """
    Given a particular phase increment parameter, this function
    will return the actual frequency of the output of the wave generator module.
    @@ parameters:
        PHASE_INC : int : the phase increment parameter 
    @@ return:
        float: the sample rate divided by the number of samples in a cycle of the output signal
    """
    if (PHASE_INC == 0): 
        return 0
    return SAMPLE_RATE / (samplesPerPeriod(PHASE_INC))

def freqQuantization(SAMPLE_RATE: float) -> np.array:
    """
    Returns a NumPy array of tuples which are pairs of phase increment values and the corresponding
    frequency output values of the CORDIC algorithm wave generator module. Assumes 
    @@ return:
    """
    # ** CREATE A LIST OF ALL POSSIBLE FREQUENCIES **
    previousPeriod = samplesPerPeriod(1) / SAMPLE_RATE
    possibleFreqs = []
    for i in range(2, TWO_PI):
        currentPeriod = samplesPerPeriod(i) / SAMPLE_RATE
        if (currentPeriod != previousPeriod):
            previousPeriod = currentPeriod
            possibleFreqs.append( (i, round(1.0/previousPeriod)) )
    
    return np.array(possibleFreqs)

if __name__ == "__main__":

    possibleFreqs = freqQuantization(SAMPLE_RATE=CLK_FREQ)

    # ** PLOT POSSIBLE FREQUENCIES AGAINST THEIR PHASE INCREMENTS **
    # phase_increments = [tuple[0] for tuple in possibleFreqs]
    # frequencies = [tuple[1] for tuple in possibleFreqs]
    
    # fig, ax = plt.subplots()
    # ax.set_title("Quantization of Frequencies from CORDIC IP")
    # ax.set_ylabel("Frequency")
    # ax.set_xlabel("Phase Increment")
    # ax.plot(phase_increments, frequencies, 'k.')
    # plt.show()

    # ** PROMPT USER FOR A DESIRED FREQUENCY **
    print("(PHASE INC)     (FREQ)")
    for pair in possibleFreqs:
        print("%11d %10d" % (pair[0], pair[1]))
    userFreq = input("Enter the desired frequency output of the wave generator (Hz): ")
    requiredPhaseInc = getPhaseInc(possibleFreqs, desiredFreq=float(userFreq))
    print(f"For this frequency, (or the closest option), your phase increment should be {requiredPhaseInc}")
    actualFreq = getFreqOut(PHASE_INC=requiredPhaseInc, SAMPLE_RATE=CLK_FREQ)
    print(f"The resulting frequency is {round(actualFreq, 2)} Hz.")



        
        
        
