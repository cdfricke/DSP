# Programmer: Connor Fricke (cd.fricke23@gmail.com)
# File: input.plt
# Latest Revision: 13-June-2024

set title "Randomly Generated Signal"
set xlabel "t"
set ylabel "64-bit Value"

set terminal windows

plot "data/input.dat" with lines title 'Unfiltered Input Signal'

set terminal png size 1920,1080
set out "data/input.png"
replot