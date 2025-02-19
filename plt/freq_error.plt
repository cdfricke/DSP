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
set object 1 rect from 30.95,29.0 to 31.55,32.0 front fs empty border rgb "black"

# FORMATTING
set xtics 23.25,2 font "mono, 20" nomirror offset 0,-1
set ytics font "mono, 20" nomirror
set border lw 2
set size ratio 0.6
set lmargin 10
set rmargin 5
set tmargin 15
set bmargin 15
set key font "mono, 24"

# PLOTTING
set xrange [25.25:37.25]
plot "data/freq_error.dat" using (($1)/1.0e6):($4) with lines lc black lw 2 title "Simulated",\
     "data/27-JAN-2025.csv" using ($1):($2):($3) with yerrorbars lc rgb "blue" pt 4 title "Observed"

set out "images/freq_error_zoom.png"
set title "Frequency Response of |X(k)|" font "mono, 24"
set xlabel "Input Frequency (MHz)" font "mono, 24" offset 0,-2
set ylabel "|X(k)|" font "mono, 24" offset -4,0
set xtics 23.25,0.25 font "mono, 20" nomirror offset 0,-1
set ytics font "mono, 20" nomirror
set size ratio 0.6
set border lw 2
set lmargin 10
set rmargin 5
set tmargin 15
set bmargin 15
set key font "mono, 24"
set xrange [30.95:31.55]
set yrange [29.0:32.0]
plot "data/freq_error.dat" using (($1)/1.0e6):($4) with lines lc black lw 2 title "Simulated",\
     "data/27-JAN-2025.csv" using ($1):($2):($3) with yerrorbars lc rgb "blue" lw 2 pt 4 ps 1.2 title "Observed"
