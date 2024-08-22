# Programmer: Connor Fricke
# File: phase_test.plt
# Latest Revision: 19-Aug-2024

# SET TERMINAL
set terminal png size 1920,1080
set out 'images/phase_test.png'

# LABELING
set title 'Goertzel Phase Results' font 'mono, 22'
set xlabel 'Re\{X(k)\}' font 'mono, 20'
set ylabel 'Im\{X(k)\}' font 'mono, 20'

# FORMATTING
set key font 'mono, 16'
set xtics font 'mono, 14' nomirror
set ytics font 'mono, 14' nomirror
set size ratio 1
set bmargin 10
set tmargin 10

# PLOTTING
set label "0" at graph 0.5,0.07 font 'mono, 14'
plot 'data/phase_test.dat' using 2:3 lt rgb "black" pt 5 ps 1.2 notitle