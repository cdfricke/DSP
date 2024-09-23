# Programmer: Connor Fricke
# File: aliasing.plt 
# Latest Rev: 28-Aug-2024

set terminal png size 1920,(2714*2)
set out 'images/aliasing31_25.png'

set xrange [0:120]
set yrange [-1.75:1.75]
set ylabel 'x(t)' font 'mono, 25'
set ytics font 'mono, 16' nomirror
set xtics 0,10,110 font 'mono, 16' nomirror offset 0,3
set key font 'mono, 20'
set multiplot layout 16,1 margins 0.05,0.95,0.05,0.95 spacing 0,0 title 'Signals Aliased to 31.25 MHz' font 'mono, 32' offset 0,-15

plot 'data/aliasing/signal_312.dat' using (($2)*1e9):3 with linespoints lw 4 lt rgb 'black' ps 1.2 pt 6 title '31.25 MHz, 187.5 MSPS',\
    'data/aliasing/signal_312_full.dat' using (($2)*1e9):3 with linespoints lw 2 lt rgb 'red' pt 6 title '31.25 MHz, 3 GSPS'
plot 'data/aliasing/signal_1562.dat' using (($2)*1e9):3 with linespoints lw 4 lt rgb 'blue' ps 1.2 pt 6 title '156.25 MHz, 187.5 MSPS',\
    'data/aliasing/signal_1562_full.dat' using (($2)*1e9):3 with linespoints lw 2 lt rgb 'red' pt 6 title '156.25 MHz, 3 GSPS'
plot 'data/aliasing/signal_2187.dat' using (($2)*1e9):3 with linespoints lw 4 lt rgb 'black' ps 1.2 pt 6 title '218.75 MHz, 187.5 MSPS',\
    'data/aliasing/signal_2187_full.dat' using (($2)*1e9):3 with linespoints lw 2 lt rgb 'red' pt 6 title '218.75 MHz, 3 GSPS' 
plot 'data/aliasing/signal_3437.dat' using (($2)*1e9):3 with linespoints lw 4 lt rgb 'blue' ps 1.2 pt 6 title '343.75 MHz, 187.5 MSPS',\
    'data/aliasing/signal_3437_full.dat' using (($2)*1e9):3 with linespoints lw 2 lt rgb 'red' pt 6 title '343.75 MHz, 3 GSPS'
plot 'data/aliasing/signal_4062.dat' using (($2)*1e9):3 with linespoints lw 4 lt rgb 'black' ps 1.2 pt 6 title '406.25 MHz, 187.5 MSPS',\
    'data/aliasing/signal_4062_full.dat' using (($2)*1e9):3 with linespoints lw 2 lt rgb 'red' pt 6 title '406.25 MHz, 3 GSPS'
plot 'data/aliasing/signal_5312.dat' using (($2)*1e9):3 with linespoints lw 4 lt rgb 'blue' ps 1.2 pt 6 title '531.25 MHz, 187.5 MSPS',\
    'data/aliasing/signal_5312_full.dat' using (($2)*1e9):3 with linespoints lw 2 lt rgb 'red' pt 6 title '531.25 MHz, 3 GSPS'
plot 'data/aliasing/signal_5937.dat' using (($2)*1e9):3 with linespoints lw 4 lt rgb 'black' ps 1.2 pt 6 title '593.75 MHz, 187.5 MSPS',\
    'data/aliasing/signal_5937_full.dat' using (($2)*1e9):3 with linespoints lw 2 lt rgb 'red' pt 6 title '593.75 MHz, 3 GSPS'
plot 'data/aliasing/signal_7187.dat' using (($2)*1e9):3 with linespoints lw 4 lt rgb 'blue' ps 1.2 pt 6 title '718.75 MHz, 187.5 MSPS',\
    'data/aliasing/signal_7187_full.dat' using (($2)*1e9):3 with linespoints lw 2 lt rgb 'red' pt 6 title '718.75 MHz, 3 GSPS'
plot 'data/aliasing/signal_7812.dat' using (($2)*1e9):3 with linespoints lw 4 lt rgb 'black' ps 1.2 pt 6 title '781.25 MHz, 187.5 MSPS',\
    'data/aliasing/signal_7812_full.dat' using (($2)*1e9):3 with linespoints lw 2 lt rgb 'red' pt 6 title '781.25 MHz, 3 GSPS'
plot 'data/aliasing/signal_9062.dat' using (($2)*1e9):3 with linespoints lw 4 lt rgb 'blue' ps 1.2 pt 6 title '906.25 MHz, 187.5 MSPS',\
    'data/aliasing/signal_9062_full.dat' using (($2)*1e9):3 with linespoints lw 2 lt rgb 'red' pt 6 title '906.25 MHz, 3 GSPS' 
plot 'data/aliasing/signal_9687.dat' using (($2)*1e9):3 with linespoints lw 4 lt rgb 'black' ps 1.2 pt 6 title '968.75 MHz, 187.5 MSPS',\
    'data/aliasing/signal_9687_full.dat' using (($2)*1e9):3 with linespoints lw 2 lt rgb 'red' pt 6 title '968.75 MHz, 3 GSPS'
plot 'data/aliasing/signal_10937.dat' using (($2)*1e9):3 with linespoints lw 4 lt rgb 'blue' ps 1.2 pt 6 title '1093.75 MHz, 187.5 MSPS',\
    'data/aliasing/signal_10937_full.dat' using (($2)*1e9):3 with linespoints lw 2 lt rgb 'red' pt 6 title '1093.75 MHz, 3 GSPS'
plot 'data/aliasing/signal_11562.dat' using (($2)*1e9):3 with linespoints lw 4 lt rgb 'black' ps 1.2 pt 6 title '1156.25 MHz, 187.5 MSPS',\
    'data/aliasing/signal_11562_full.dat' using (($2)*1e9):3 with linespoints lw 2 lt rgb 'red' pt 6 title '1156.25 MHz, 3 GSPS'
plot 'data/aliasing/signal_12812.dat' using (($2)*1e9):3 with linespoints lw 4 lt rgb 'blue' ps 1.2 pt 6 title '1281.25 MHz, 187.5 MSPS',\
    'data/aliasing/signal_12812_full.dat' using (($2)*1e9):3 with linespoints lw 2 lt rgb 'red' pt 6 title '1281.25 MHz, 3 GSPS'
plot 'data/aliasing/signal_13437.dat' using (($2)*1e9):3 with linespoints lw 4 lt rgb 'black' ps 1.2 pt 6 title '1343.75 MHz, 187.5 MSPS',\
    'data/aliasing/signal_13437_full.dat' using (($2)*1e9):3 with linespoints lw 2 lt rgb 'red' pt 6 title '1343.75 MHz, 3 GSPS'

set xlabel 't (ns)' font 'mono, 25'
plot 'data/aliasing/signal_14687.dat' using (($2)*1e9):3 with linespoints lw 4 lt rgb 'blue' ps 1.2 pt 6 title '1468.75 MHz, 187.5 MSPS',\
    'data/aliasing/signal_14687_full.dat' using (($2)*1e9):3 with linespoints lw 2 lt rgb 'red' pt 6 title '1468.75 MHz, 3 GSPS'