# ******* GNUPLOT SCRIPT *******
# Programmmer: Connor Fricke
# File: probe.plt
# Latest Revision: 9-Aug-2024
# Desc: Plotting s(n) probe data from C++ program
# ******************************

# SET TERMINAL
set terminal png size 1920,1080
set out 'images/probe.png'

# LABELING
set title 'IIR Filter Behavior ' font 'mono, 22'
set xlabel 'n' font 'mono, 20'
set ylabel 's(n)' font 'mono, 20'

# FORMATTING
set key font 'mono, 16'
set xtics font 'mono, 14' nomirror
set ytics font 'mono, 14' nomirror -40,20,40
set size ratio 0.12
set lmargin 10
set rmargin 10


# PLOTTING
set xrange [0:126]
set yrange [-45:45]
plot 'data/probe.dat' using 1:2 with linesp lt rgb "black" lw 2 pt 5 ps 1.2 notitle