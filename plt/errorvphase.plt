# Programmer: Connor Fricke (cd.fricke23@gmail.com)
# File: errorvphase.plt
# Latest Revision: 26-Nov-2024

# WRITE TO PNG
set terminal png size 1920,1080
set out "images/error_plot.png"

# LABELING
set title "Output Error vs. Phase" font "mono, 20"
set xlabel "Phase" font "mono, 20" offset 0,-1
set ylabel "Rel. Error" font "mono, 20" offset -2,0

# FORMATTING
set xtics font "mono, 14" nomirror
set ytics font "mono, 14" nomirror
set size ratio 0.12
set lmargin 20
set rmargin 5

# PLOTTING
set xrange [(-3.142):(3.142)]
plot "data/phase_testing.dat" using ($1):($4) with points lc black lw 2 pt 6 ps 0.8 notitle