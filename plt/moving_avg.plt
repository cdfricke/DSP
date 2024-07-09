# Programmer: Connor Fricke (cd.fricke23@gmail.com)
# File: moving_avg.plt
# Latest Revision: 11-June-2024
# GNUPLOT script for testing the functionality of the IIR recursive averaging filter.

set title "Moving Average"
set xlabel "n"
set ylabel "64-Bit Value"

set terminal windows

plot "data/input.dat" with lines lw 1,\
     "data/output.dat" with lines lw 3 lt rgb "red" title "EMA, a = 1/8"

set terminal png size 1920,1080
set out "data/moving_avg.png"
replot