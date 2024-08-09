# Programmer: Connor Fricke (cd.fricke23@gmail.com)
# File: comparison.plt
# Latest Revision: 11-June-2024
# GNUPLOT script for testing the functionality of the IIR recursive averaging filter.

# WRITE TO PNG
set terminal png size 1920,1080
set out "images/comparison.png"

# LABELING
set title 'IIR Filter Effect' font 'mono, 22'
set xlabel 't (ns)' font 'mono, 20'
set ylabel 'Signal Value' font 'mono, 20'

# FORMATTING
set key font 'mono, 16'
set xtics font 'mono, 14' nomirror
set ytics font 'mono, 14' nomirror
set size ratio 0.3
set lmargin 20
set rmargin 10

set yrange [-1.5:1.5]
set xrange [0:1300]
plot "data/input.dat" using (($1)*1e9):($2) with linesp lw 2 lc black notitle,\
     "data/output.dat" using (($1)*1e9):($2) with linesp lw 3 lt rgb "red" title "EMA, a = 1/8"