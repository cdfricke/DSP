# Programmer: Connor Fricke (cd.fricke23@gmail.com)
# File: input.plt
# Latest Revision: 7-June-2024

set title "Randomly Generated Signal"
set xlabel "n"
set ylabel "64-bit Value"

set terminal windows

plot "data/input.dat" with lines

set terminal png size 1920,1080
set out "data/noise.png"
replot