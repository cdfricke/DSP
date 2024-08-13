# Programmer: Connor Fricke (cd.fricke23@gmail.com)
# File: input.plt
# Latest Revision: 9-Aug-2024

# WRITE TO PNG
set terminal png size 1920,1080
set out "images/input.png"

# LABELING
set title "Input Signal" font "mono, 20"
set xlabel "t (ns)" font "mono, 20" offset 0,-1
set ylabel "x(t)" font "mono, 20"

# FORMATTING
set xtics font "mono, 14" nomirror
set ytics font "mono, 14" nomirror
set size ratio 0.12
set lmargin 10
set rmargin 10

# PLOTTING
set xrange [0:1260]
set yrange [(-1.1):(1.1)]
plot "data/input.dat" using (($1)*1e9):($2) with linesp lc black lw 2 pt 6 ps 0.8 notitle



