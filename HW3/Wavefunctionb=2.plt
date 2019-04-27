# plot file for diffeq_test_exp_back
set timestamp

set xlabel 'r'
set ylabel 'u(r)'

set title 'HW3 plot, Varying Basis Size With b=2'

 
 plot "Wavefunctionb2d1.dat" using ($1):($2) title 'Dim=1'
 replot "Wavefunctionb2d5.dat" using ($1):($2) title 'Dim=5' 
 replot "Wavefunctionb2d10.dat" using ($1):(-($2)) title 'Dim=10'
 replot "Wavefunctionb2d20.dat" using ($1):($2) title 'Dim=20'
 replot 2*x*exp(-x) title 'Exact' 
 set term postscript
 set output "HW3plot-b=2.ps"
 replot
 

