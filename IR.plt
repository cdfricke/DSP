# Programmer: Connor Fricke (cd.fricke23@gmail.com)
# File: IR.plt
# Latest Revision: 7-June-2024

set title "Filter Impulse Response"
set xlabel "n"
set ylabel "64-bit Value"

set terminal windows

plot "data/IR.dat" with impulses linewidth 10 title 'EMA, a = 1/8'

set terminal png size 1920,1080
set out "data/IR.png"
replot