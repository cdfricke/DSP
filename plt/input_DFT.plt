# Programmer: Connor Fricke (cd.fricke23@gmail.com)
# File: input_DFT.plt
# Latest Revision: 9-Aug-2024
# Gnuplot script for plotting the Discrete Fourier transform of our input signal.

# WRITE TO PNG
set terminal png size 1920,1080
set out 'images/input_DFT.png'

# LABELING
set title 'Input Signal: Frequency Domain' font 'mono, 20'
set ylabel '|X(k)|' font 'mono, 20' offset -1,0
set xlabel 'Frequency (MHz)' font 'mono, 20'

# FORMATTING
set xtics font "mono, 14" nomirror 
set ytics font "mono, 14" nomirror 0,20,60
set size ratio 0.12
set lmargin 10
set rmargin 10

# PLOTTING
set xrange [0:50]
set yrange [0:70]
set label "63" at graph 0.318,0.91 font 'mono, 14'
plot 'data/input_DFT.dat' using (($1)/1e6):($2) with impulses lw 5 lt -1 notitle