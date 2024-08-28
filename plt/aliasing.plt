# Programmer: Connor Fricke
# File: aliasing.plt 
# Latest Rev: 28-Aug-2024

set terminal png size 1920,(2714*2)
set out 'images/aliasing31_75.png'

set xrange [0:120]
set yrange [-1.75:1.75]
set ylabel 'x(t)' font 'mono, 25'
set ytics font 'mono, 16' nomirror
set xtics 0,10,110 font 'mono, 16' nomirror offset 0,3
set key font 'mono, 20'
set multiplot layout 16,1 margins 0.05,0.95,0.05,0.95 spacing 0,0 title 'Signals Aliased to 31.75 MHz' font 'mono, 32' offset 0,-7

plot 'data/aliasing/signal_317.dat' using (($2)*1e9):3 with linespoints lw 4 lt rgb 'black' ps 1.2 pt 6 title '31.75 MHz, 187.5 MSPS',\
    'data/aliasing/signal_317_full.dat' using (($2)*1e9):3 with linespoints lw 2 lt rgb 'red' pt 6 title '31.75 MHz, 3 GSPS'
plot 'data/aliasing/signal_1557.dat' using (($2)*1e9):3 with linespoints lw 4 lt rgb 'blue' ps 1.2 pt 6 title '155.75 MHz, 187.5 MSPS',\
    'data/aliasing/signal_1557_full.dat' using (($2)*1e9):3 with linespoints lw 2 lt rgb 'red' pt 6 title '155.75 MHz, 3 GSPS'
plot 'data/aliasing/signal_2192.dat' using (($2)*1e9):3 with linespoints lw 4 lt rgb 'black' ps 1.2 pt 6 title '219.25 MHz, 187.5 MSPS',\
    'data/aliasing/signal_2192_full.dat' using (($2)*1e9):3 with linespoints lw 2 lt rgb 'red' pt 6 title '219.25 MHz, 3 GSPS' 
plot 'data/aliasing/signal_3432.dat' using (($2)*1e9):3 with linespoints lw 4 lt rgb 'blue' ps 1.2 pt 6 title '343.25 MHz, 187.5 MSPS',\
    'data/aliasing/signal_3432_full.dat' using (($2)*1e9):3 with linespoints lw 2 lt rgb 'red' pt 6 title '343.25 MHz, 3 GSPS'
plot 'data/aliasing/signal_4067.dat' using (($2)*1e9):3 with linespoints lw 4 lt rgb 'black' ps 1.2 pt 6 title '406.75 MHz, 187.5 MSPS',\
    'data/aliasing/signal_4067_full.dat' using (($2)*1e9):3 with linespoints lw 2 lt rgb 'red' pt 6 title '406.75 MHz, 3 GSPS'
plot 'data/aliasing/signal_5307.dat' using (($2)*1e9):3 with linespoints lw 4 lt rgb 'blue' ps 1.2 pt 6 title '530.75 MHz, 187.5 MSPS',\
    'data/aliasing/signal_5307_full.dat' using (($2)*1e9):3 with linespoints lw 2 lt rgb 'red' pt 6 title '530.75 MHz, 3 GSPS'
plot 'data/aliasing/signal_5942.dat' using (($2)*1e9):3 with linespoints lw 4 lt rgb 'black' ps 1.2 pt 6 title '594.25 MHz, 187.5 MSPS',\
    'data/aliasing/signal_5942_full.dat' using (($2)*1e9):3 with linespoints lw 2 lt rgb 'red' pt 6 title '594.25 MHz, 3 GSPS'
plot 'data/aliasing/signal_7182.dat' using (($2)*1e9):3 with linespoints lw 4 lt rgb 'blue' ps 1.2 pt 6 title '718.25 MHz, 187.5 MSPS',\
    'data/aliasing/signal_7182_full.dat' using (($2)*1e9):3 with linespoints lw 2 lt rgb 'red' pt 6 title '718.25 MHz, 3 GSPS'
plot 'data/aliasing/signal_7817.dat' using (($2)*1e9):3 with linespoints lw 4 lt rgb 'black' ps 1.2 pt 6 title '781.75 MHz, 187.5 MSPS',\
    'data/aliasing/signal_7817_full.dat' using (($2)*1e9):3 with linespoints lw 2 lt rgb 'red' pt 6 title '781.75 MHz, 3 GSPS'
plot 'data/aliasing/signal_9057.dat' using (($2)*1e9):3 with linespoints lw 4 lt rgb 'blue' ps 1.2 pt 6 title '905.75 MHz, 187.5 MSPS',\
    'data/aliasing/signal_9057_full.dat' using (($2)*1e9):3 with linespoints lw 2 lt rgb 'red' pt 6 title '905.75 MHz, 3 GSPS' 
plot 'data/aliasing/signal_9692.dat' using (($2)*1e9):3 with linespoints lw 4 lt rgb 'black' ps 1.2 pt 6 title '969.25 MHz, 187.5 MSPS',\
    'data/aliasing/signal_9692_full.dat' using (($2)*1e9):3 with linespoints lw 2 lt rgb 'red' pt 6 title '969.25 MHz, 3 GSPS'
plot 'data/aliasing/signal_10932.dat' using (($2)*1e9):3 with linespoints lw 4 lt rgb 'blue' ps 1.2 pt 6 title '1093.25 MHz, 187.5 MSPS',\
    'data/aliasing/signal_10932_full.dat' using (($2)*1e9):3 with linespoints lw 2 lt rgb 'red' pt 6 title '1093.25 MHz, 3 GSPS'
plot 'data/aliasing/signal_11567.dat' using (($2)*1e9):3 with linespoints lw 4 lt rgb 'black' ps 1.2 pt 6 title '1156.75 MHz, 187.5 MSPS',\
    'data/aliasing/signal_11567_full.dat' using (($2)*1e9):3 with linespoints lw 2 lt rgb 'red' pt 6 title '1156.75 MHz, 3 GSPS'
plot 'data/aliasing/signal_12807.dat' using (($2)*1e9):3 with linespoints lw 4 lt rgb 'blue' ps 1.2 pt 6 title '1280.75 MHz, 187.5 MSPS',\
    'data/aliasing/signal_12807_full.dat' using (($2)*1e9):3 with linespoints lw 2 lt rgb 'red' pt 6 title '1280.75 MHz, 3 GSPS'
plot 'data/aliasing/signal_13442.dat' using (($2)*1e9):3 with linespoints lw 4 lt rgb 'black' ps 1.2 pt 6 title '1344.25 MHz, 187.5 MSPS',\
    'data/aliasing/signal_13442_full.dat' using (($2)*1e9):3 with linespoints lw 2 lt rgb 'red' pt 6 title '1344.25 MHz, 3 GSPS'

set xlabel 't (ns)' font 'mono, 25'
plot 'data/aliasing/signal_14682.dat' using (($2)*1e9):3 with linespoints lw 4 lt rgb 'blue' ps 1.2 pt 6 title '1468.25 MHz, 187.5 MSPS',\
    'data/aliasing/signal_14682_full.dat' using (($2)*1e9):3 with linespoints lw 2 lt rgb 'red' pt 6 title '1468.25 MHz, 3 GSPS'