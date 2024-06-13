# Programmer: Connor Fricke (cd.fricke23@gmail.com)
# File: input_DFT.plt
# Latest Revision: 13-June-2024
# Gnuplot script for plotting the Discrete Fourier transform of our input signal.

set terminal windows

set title 'Fourier Transform'
set ylabel 'Coefficient'
set xlabel 'Frequency (k)'

plot 'data/input_DFT.dat' with linespoints lw 2 title 'Input Signal DFT'

set terminal png size 1920,1080
set out 'data/input_DFT.png'
replot