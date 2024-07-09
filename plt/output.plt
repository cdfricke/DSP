# Programmer: Connor Fricke (cd.fricke23@gmail.com)
# File: output.plt
# Latest Revision: 13-June-2024

set title "Filtered Signal"
set xlabel "t"
set ylabel "64-bit Value"

set terminal windows

# PLOT SINGLE-FILTERED RESULTS
set terminal windows
plot "data/output.dat" with lines title 'Filtered Output Signal'

set terminal png size 1920,1080
set out "data/output.png"
replot

