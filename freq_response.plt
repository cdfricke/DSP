# Programmer: Connor Fricke (cd.fricke23@gmail.com)
# File: freq_response.plt
# Latest Revision: 7-June-2024

set title "Frequency Response, FIR Lowpass"
set xlabel "frequency"
set ylabel "Gain"

set terminal windows

plot "data/freq_response.dat" using ($1):(20*log10($2)) with linespoints linewidth 10 title "EMA, a = 1/8"

set terminal png size 1920,1080
set out "data/freq_response.png"
replot