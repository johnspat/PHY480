# plot file for diffeq_test_exp_back
set timestamp

set xlabel 'i (log10)'
set ylabel 'relative error in integration (log10)'

set title 'Comparing integrating Algorithms'

 
 plot "Simpsons.dat" using ($1):($2) title 'Simpsons'
 replot "Simpsons.dat" using ($1):($3) title 'GSL' 
 replot "Milne.dat" using ($1):($2) title 'Milne' 
 set term postscript
 set output "HW2plot.ps"
 replot
 

