# Programmer: Connor Fricke (cd.fricke23@gmail.com)
# File: ILA_Analyis.py
# Latest Revision: 25-June-2024
# Synopsis: Plotting of filtering results from ILAdata.csv exported from "Wave Synthesis" Vivado Project.

import scipy.signal as sig
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

# ** IMPORT DATA **
df = pd.read_csv("./data/ILAdata.csv", sep=',')

filteredSignal_FPGA = np.array(df["filteredCos[18:0]"]) / (2**15)
outputSignal_FPGA = np.array(df["outputCos[17:0]"]) / (2**14)
time = np.array(df["Sample in Window"])

# ** APPLY FILTER **
# y[n] - (1-a)y[n-1] = ax[n]
alpha = 0.125
a = np.array([1.0, -(1.0-alpha)])
b = np.array([alpha])
filteredSignal_SciPy = sig.lfilter(b, a, outputSignal_FPGA)

# ** PLOT UNFILTERED DATA **
fig, ax = plt.subplots()
ax.set_title("Unfiltered Signal: FPGA vs. Python")
ax.set_xlabel("Sample #")
ax.set_ylabel("Signal Value")
ax.plot(time, outputSignal_FPGA, label="FPGA ILA Signal Data")

plt.legend()
plt.xlim([0,150])
plt.show()

# ** PLOT ALL SIGNAL COMPONENTS **
fig, axs = plt.subplots(4, 1, sharex=True)
plt.xlim((0,150))
fig.suptitle("Signal Components")
fig.supxlabel("Sample #")

cos_500kHz = np.array(df["cos_500kHz[15:0]"]) / (2**14)     # 16-bit data, 1.1.14 (1 sign bit, 1 integer bit, 14 fraction bits)
cos_1MHz = np.array(df["cos_1MHz[15:0]"]) / (2**14)         # 16-bit data, 1.1.14
cos_2MHz = np.array(df["cos_2MHz[15:0]"]) / (2**14)         # 16-bit data, 1.1.14
cos_2_8MHz = np.array(df["cos_2_8MHz_wc[15:0]"]) / (2**15)  # 16-bit data, 1.0.15
components = [cos_500kHz, cos_1MHz, cos_2MHz, cos_2_8MHz]
labels = ["500 kHz", "1 MHz", "2 MHz", "2.8 MHz"]

for i in range(axs.size):
    axs[i].plot(time, components[i], label=labels[i])
    axs[i].legend(loc='center right')

plt.show()

# ** PLOT FILTERED DATA **
fig, ax = plt.subplots()
ax.set_title("Filtered Signal: FPGA vs. SciPy")
ax.set_xlabel("Sample #")
ax.set_ylabel("Signal Value")
ax.plot(time, filteredSignal_FPGA, label="FPGA-Filtered")
ax.plot(time, filteredSignal_SciPy, label="Python-Filtered")

plt.legend()
plt.xlim([0,150])
plt.show()

# ** PLOT UNFILTERED VS. FILTERED **
fig, ax = plt.subplots()
ax.set_title("Filter Effect")
ax.set_xlabel("Phase")
ax.set_ylabel("Signal Value")
ax.plot(time, outputSignal_FPGA, label="FPGA ILA Signal Data")
ax.plot(time, filteredSignal_FPGA, label="FPGA-Filtered")
ax.plot(time, filteredSignal_SciPy, label="Python-Filtered")

plt.legend()
plt.xlim([0,150])
plt.show()



