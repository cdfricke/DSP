# Programmer: Connor Fricke (cd.fricke23@gmail.com)
# File: RFSoC.plt
# Latest Revision: 22-Aug-2024

# TERMINAL 
set terminal png size 1920,1080
set out 'images/RFSoC.png'

# LABELING
set xlabel 't (ns)' font 'mono, 20' offset 0,-1
set ylabel 'Signal Value' font 'mono, 20' offset -1,0
set title '500 MHz ADC Signal' font 'mono, 24'

# FORMATTING
set size ratio 0.2
set xrange [0:60]
set yrange [(-1.3):(1.3)]
set xtics font 'mono, 16' nomirror
set ytics font 'mono, 16' nomirror
set key font 'mono, 18'
set lmargin 15

# PLOTTING
plot 'data/500MHz.dat' using (($1)*1e9):2 with linespoints pt 6 ps 1.1 lt rgb "black" lw 2 title '500 MHz \@ 3 GSPS',\
    'data/500MHz_decimated.dat' using (($1)*1e9):2 with linespoints pt 6 ps 1.1 lw 3 lt rgb 'red' title '500 MHz \@ 375 MSPS'