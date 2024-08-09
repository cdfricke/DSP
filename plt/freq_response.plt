# Programmer: Connor Fricke (cd.fricke23@gmail.com)
# File: freq_response.plt
# Latest Revision: 9-Aug-2024

set terminal png size 1920,1080
set out "images/freq_response.png"

# LABELING
set title "Frequency Response" font 'mono,24'
set xlabel "f/f_N" font 'mono, 20'
set ylabel "Gain" font 'mono, 20'
set key font 'mono, 18'

# FORMATTING
set size ratio 0.3
set lmargin 10
set rmargin 10

# PLOTTING
set xrange [0:0.5]
plot "data/freq_response.dat" using ($1):(20*log10($2)) with linesp lw 2 lt 2 pt 2 lc black title "EMA filter, a = 1/8"