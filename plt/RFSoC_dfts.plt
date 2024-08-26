# Programmer: Connor Fricke (cd.fricke23@gmail.com)
# File: RFSoC_dfts.plt
# Latest Revision: 26-Aug-2024

# TERMINAL 
set terminal png size 1920,1080
set out 'images/RFSoC_DFT.png'

# LABELING
set xlabel 'k' font 'mono, 20' offset 0,-1
set ylabel '|X(k)|' font 'mono, 20' offset -1,0

# FORMATTING AND PLOTTING
set multiplot layout 2,1 title '500 MHz ADC Signal DFT' font 'mono, 24' offset 0,-7
set size ratio 0.2
set origin 0.01,0.01
set rmargin 10
set lmargin 10
set xtics font 'mono, 16' nomirror
set ytics font 'mono, 16' nomirror
set key top left font 'mono, 18' offset -8,0
set xrange [0:(2016/16)]
set label "k = 84 = N_D/3" font 'mono, 16' at graph 0.675,0.9
plot 'data/375MSPS_DFT.dat' using 1:2 with impulses lt rgb 'red' lw 5 title '500 MHz DFT \@ 375 MSPS, N_D = N_F/8 = 252'
set origin 0.01,0.42
set key top right font 'mono, 18' offset 1,0
set xrange [0:(2016/2)]
unset label
set label "k = 336 = N_F/6" font 'mono, 16' at graph 0.225,0.85
plot 'data/3GSPS_DFT.dat' using 1:2 with impulses lt rgb 'black' lw 5 title '500 MHz DFT \@ 3 GSPS, N_F = 2016'
unset label
unset multiplot

# PLOT AGAIN, DIFFERENT FREQ, DIFFERENT OUTPUT FILE
set out 'images/RFSoC_DFT2.png'
set multiplot layout 2,1 title '62.5 MHz ADC Signal DFT' font 'mono, 24' offset 0,-7
set rmargin 10
set lmargin 10

set origin 0.01,0.01
set xrange [0:(2016/16)]
set label "k = 42 = N_D/6" font 'mono, 16' at graph 0.35,0.9
plot 'data/375MSPS_DFT_2.dat' using 1:2 with impulses lt rgb 'red' lw 5 title '62.5 MHz DFT \@ 375 MSPS, N_D = N_F/8 = 252'
set origin 0.01,0.42
set key top right font 'mono, 18' offset 1,0
set xrange [0:(2016/2)]
unset label
set label "k = 42 = N_F/48" font 'mono, 16' at graph 0.05,0.85
plot 'data/3GSPS_DFT_2.dat' using 1:2 with impulses lt rgb 'black' lw 5 title '62.5 MHz DFT \@ 3 GSPS, N_F = 2016'