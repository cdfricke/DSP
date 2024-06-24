import scipy.signal as sig
import matplotlib.pyplot as plt
from math import cos, pi
import numpy as np
import pandas as pd

SAMPLING_FREQ = 12e6 # Hz
NYQUIST = SAMPLING_FREQ / 2.0

def wave_generator(wave_freq, sampling_freq, duration):
    """
    Generates a cosine signal of a particular sampling frequency, wave frequency,
    and total duration. Returns a tuple of lists x and y of the signal.
    @@ parameters:
        - wave_freq: desired frequency of the output signal, in Hz
        - sampling_freq: sets the rate at which the signal value is measured, in Hz
        - duration: defines the length of the output arrays, in seconds
    @@ returns:
        - nptime: ndarray of floats representing discrete time samples of the signal
        - npsignal: ndarray of the corresponding value of the signal at each time sample
    """
    time = []
    signal = []
    SAMPLING_PERIOD = 1.0 / sampling_freq
    currentTime = 0
    currentValue = cos(2*pi*wave_freq*currentTime)
    while (currentTime < duration):
        time.append(currentTime)
        signal.append(currentValue)
        currentTime += SAMPLING_PERIOD
        currentValue = cos(2*pi*wave_freq*currentTime)

    nptime = np.array(time)
    npsignal = np.array(signal)
    
    return nptime, npsignal

HIGHEST_FREQ = 2e6
SIGNAL_DURATION = 20.0 / HIGHEST_FREQ
time, signal_500kHz = wave_generator(500e3, SAMPLING_FREQ, SIGNAL_DURATION)
time, signal_1MHz = wave_generator(1e6, SAMPLING_FREQ, SIGNAL_DURATION)
time, signal_2MHz = wave_generator(2e6, SAMPLING_FREQ, SIGNAL_DURATION)

totalSignal = signal_500kHz + (0.5*signal_1MHz) + (0.25*signal_2MHz)
# ** APPLY FILTER **
# y[n] - (1-a)y[n-1] = ax[n]
alpha = 0.125
a = np.array([1.0, -(1.0-alpha)])
b = np.array([alpha])
filteredSignal = sig.lfilter(a, b, totalSignal)

# ** IMPORT DATA TO COMPARE **
df = pd.read_csv("./data/iladata.csv", sep=',')
# slice to size and scale
filteredSignal_FPGA = np.array(df["filteredCos[17:0]"])[0:filteredSignal.size] / (2**14)
outputCos = np.array(df["outputCos[16:0]"])[10:totalSignal.size+10] / (2**14)


fig, ax = plt.subplots()
ax.set_title("Filtered Signal: FPGA vs. SciPy")
ax.set_xlabel("Time")
ax.set_ylabel("Signal Value")
ax.plot(time, filteredSignal_FPGA)
ax.plot(time, filteredSignal)

plt.show()

fig, ax = plt.subplots()
ax.set_title("Unfiltered Signal: FPGA vs. Python")
ax.set_xlabel("Phase")
ax.set_ylabel("Signal Value")
ax.plot(time, totalSignal)
ax.plot(time, outputCos)

plt.show()



