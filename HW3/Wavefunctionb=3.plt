# plot file for diffeq_test_exp_back
set timestamp

set xlabel 'r'
set ylabel 'u(r)'

set title 'HW3 plot, Varying Basis Size With b=3'

 
 plot "Wavefunctionb3d1.dat" using ($1):($2) title 'Dim=1'
 replot "Wavefunctionb3d5.dat" using ($1):($2) title 'Dim=5' 
 replot "Wavefunctionb3d10.dat" using ($1):($2) title 'Dim=10'
 replot "Wavefunctionb3d20.dat" using ($1):($2) title 'Dim=20'
 replot 2*x*exp(-x) title 'Exact' 
 set term postscript
 set output "HW3plot-b=3.ps"
 replot
 

