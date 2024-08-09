# Programmer: Connor Fricke (cd.fricke23@gmail.com)
# File: IR.plt
# Latest Revision: 7-June-2024

# WRTIE TO PNG
set terminal png size 1920,1080
set out "images/IR.png"

# LABELING
set title "Filter Impulse Response" font 'mono, 20'
set xlabel "n" font 'mono, 20'
set ylabel "h(n)" font 'mono, 20'
set key font 'mono, 16'

# FORMATTING
set lmargin 20
set rmargin 10
set xtics font 'mono, 14' nomirror scale 0
set ytics font 'mono, 14' nomirror scale 0
set size ratio 0.3

set xrange [0:126]
plot "data/IR.dat" with impulses lw 5 title 'EMA, a = 1/8'