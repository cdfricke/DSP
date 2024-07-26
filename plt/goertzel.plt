# Programmer: Connor Fricke (cd.fricke23@gmail.com)
# File: freq_response.plt
# Latest Revision: 27-July-2024

set title "DFT: Goertzel 2nd Order Cascade Form"
set xlabel "frequency"
set ylabel "Power"

set terminal windows

plot "data/goertzel.dat" using ($2):($3) with linespoints linewidth 10 title "Goertzel IIR + FIR Cascade"