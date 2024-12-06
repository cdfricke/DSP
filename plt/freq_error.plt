# Programmer: Connor Fricke
# File: freq_error.plt
# Desc: Plots data from freq_error.cpp (freq_error.dat), error vs frequency

# WRITE TO PNG
set terminal png size 1920,1080
set out "images/freq_error.png"

# LABELING
set title "Frequency Response of |X(k)|" font "mono, 24"
set xlabel "Input Frequency (MHz)" font "mono, 24" offset 0,-2
set ylabel "|X(k)|" font "mono, 24" offset -2,0
set object circle at 31.25,63 radius char 0.8 fillstyle empty border lc rgb 'red' lw 4

# FORMATTING
set xtics 23.25,2 font "mono, 20" nomirror offset 0,-1
set ytics font "mono, 20" nomirror
set size ratio 0.6
set lmargin 10
set rmargin 5
set tmargin 20
set bmargin 20

# PLOTTING
set xrange [25.25:37.25]
plot "data/freq_error.dat" using (($1)/1.0e6):($4) with lines lc black lw 3 notitle