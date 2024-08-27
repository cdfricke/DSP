# Programmer: Connor Fricke
# File: aliasing.plt 
# Latest Rev: 27-Aug-2024

set terminal png size 1920,2714
set out 'images/aliasing.png'

set xrange [0:60]
set yrange [-1.75:1.75]
set ylabel 'x(t)' font 'mono, 25'
set ytics font 'mono, 16' nomirror
set xtics 0,10,50 font 'mono, 16' nomirror offset 0,3
set key font 'mono, 20'
set multiplot layout 8,1 margins 0.05,0.95,0.05,0.95 spacing 0,0 title 'Signals Aliased to 62.5 MHz' font 'mono, 32' offset 0,-7

plot 'data/aliasing/signal_625.dat' using (($2)*1e9):3 with linespoints lw 4 lt rgb 'black' ps 1.2 pt 6 title '62.5 MHz, 375 MSPS',\
    'data/aliasing/signal_625_full.dat' using (($2)*1e9):3 with linespoints lw 2 lt rgb 'red' pt 6 title '62.5 MHz, 3 GSPS'
plot 'data/aliasing/signal_3125.dat' using (($2)*1e9):3 with linespoints lw 4 lt rgb 'blue' ps 1.2 pt 6 title '312.5 MHz, 375 MSPS',\
    'data/aliasing/signal_3125_full.dat' using (($2)*1e9):3 with linespoints lw 2 lt rgb 'red' pt 6 title '312.5 MHz, 3 GSPS'
plot 'data/aliasing/signal_4375.dat' using (($2)*1e9):3 with linespoints lw 4 lt rgb 'black' ps 1.2 pt 6 title '437.5 MHz, 375 MSPS',\
    'data/aliasing/signal_4375_full.dat' using (($2)*1e9):3 with linespoints lw 2 lt rgb 'red' pt 6 title '437.5 MHz, 3 GSPS' 
plot 'data/aliasing/signal_6875.dat' using (($2)*1e9):3 with linespoints lw 4 lt rgb 'blue' ps 1.2 pt 6 title '687.5 MHz, 375 MSPS',\
    'data/aliasing/signal_6875_full.dat' using (($2)*1e9):3 with linespoints lw 2 lt rgb 'red' pt 6 title '687.5 MHz, 3 GSPS'
plot 'data/aliasing/signal_8125.dat' using (($2)*1e9):3 with linespoints lw 4 lt rgb 'black' ps 1.2 pt 6 title '812.5 MHz, 375 MSPS',\
    'data/aliasing/signal_8125_full.dat' using (($2)*1e9):3 with linespoints lw 2 lt rgb 'red' pt 6 title '812.5 MHz, 3 GSPS'
plot 'data/aliasing/signal_10625.dat' using (($2)*1e9):3 with linespoints lw 4 lt rgb 'blue' ps 1.2 pt 6 title '1062.5 MHz, 375 MSPS',\
    'data/aliasing/signal_10625_full.dat' using (($2)*1e9):3 with linespoints lw 2 lt rgb 'red' pt 6 title '1062.5 MHz, 3 GSPS'
plot 'data/aliasing/signal_11875.dat' using (($2)*1e9):3 with linespoints lw 4 lt rgb 'black' ps 1.2 pt 6 title '1187.5 MHz, 375 MSPS',\
    'data/aliasing/signal_11875_full.dat' using (($2)*1e9):3 with linespoints lw 2 lt rgb 'red' pt 6 title '1187.5 MHz, 3 GSPS'

set xlabel 't' font 'mono, 25'
plot 'data/aliasing/signal_14375.dat' using (($2)*1e9):3 with linespoints lw 4 lt rgb 'blue' ps 1.2 pt 6 title '1437.5 MHz, 375 MSPS',\
    'data/aliasing/signal_14375_full.dat' using (($2)*1e9):3 with linespoints lw 2 lt rgb 'red' pt 6 title '1437.5 MHz, 3 GSPS'
