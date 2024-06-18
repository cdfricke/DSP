Created by: Connor Fricke (cd.fricke23@gmail.com)
Collection of various testbenches and programs used while learning how to design
and implement FIR and IIR filters in software and FPGA applications.

Data generated with C++, plotted with Gnuplot.

For Windows, all gnuplot scripts (.plt files) must call "set terminal windows".
For Linux, all gnuplot scripts (.plt files) must instead call "set terminal x11".
Note: There are in fact some cross-platform terminals that can be used alternatively, but the native ones to each platform work best.

Program successfully compiled and ran with:
PowerShell > g++ -g filter_design.cpp DSP.cpp -o filter_design.exe -O3 -I {currentDirectory} -std=c++17
Bash > g++ -g filter_design.cpp DSP.cpp -o filter_design.x -O3 -I {currentDirectory} -std=c++17
