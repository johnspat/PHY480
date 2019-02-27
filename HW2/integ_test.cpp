//  file: integ_test.cpp
//
//  This is a test program for basic integration methods.               
//                                                                     
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      04-Jan-2004  original version, for 780.20 Computational Physics
//      08-Jan-2005  changed functions to pass integrand
//      09-Jan-2011  updated functions
//
//  Notes:
//   * define with floats to emphasize round-off error  
//   * compile with:  "g++ -Wall -c integ_test.cpp"
//   * adapted from: "Projects in Computational Physics" by Landau and Paez  
//             copyrighted by John Wiley and Sons, New York               
//             code copyrighted by RH Landau                           
// 
// This code was adapted to test Milne's method and Simpsons method, along with a gsl integration method.
// Patrick Johns
// johnspat@msu.edu
// 2/27/2019 added gsl integration routine.
// Discussion on the plot: The plot of the relative error between the integration technique and the number of intervals
// for Milne's and Simpson's method included 2 regions. The relative error for both would decrease linearly(on a log-log plot) 
// and then change to mostly noise afterwards. The linear relationship for Simpson's method had a slope of -4.03508(fitted by
// Gnuplot), which tells us that the relative error decreases like N^-4 with the number of intervals. For Milne's method,
// the slope was -6.18965, which tells us that the relative error decreases like N^-6 with the number of intervals. 
//
// PART 3: By eyeing the graph, the optimum number of points seems to be ~10^2.2=161. Using the fact that the optimum number
// of points is when etotal=eapprox, The optimum points should be roughly 1/(em)^6/5, where em is the machine error. For 
// double precision, this number should be 1.11e-16. However, when I do this calculation, theoretically the optimum 
// number of points should be ~1.39e19. I am not entirely sure I am doing the theoretical calculation correctly, but 
// my empirical measurement is completely off of the theoretical measurement, so it's safe to assume that my empirical
// measurement is more accurate, as it is less amount of points than Simpson's method needs and should be because
// it is a better algorithm.
//************************************************************************

// include files
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
using namespace std;

#include "integ_routines.h"	// prototypes for integration routines
#include <gsl/gsl_integration.h> // for gsl integration routine

double my_integrand (double x);
double my_gsl_integrand (double x, void *);


//************************************************************************

int
main ()
{
	gsl_integration_workspace *work_ptr
    = gsl_integration_workspace_alloc (1000); // set up the gsl integration routine.
  // set up the integration specifiction
  const int max_intervals = 100000;	// maximum number of intervals
  const double lower = 0.0;	// lower limit of integration
  const double upper = 1.0;	// upper limit of integration

  const double answer = 0.74682413281242702539947;	// the "exact" answer for the test 
  double result = 0.;  // approximate answer
  double abs_error = 1.0e-8;	/* to avoid round-off problems */
  double rel_error = 1.0e-8;	/* the result will usually be much better */
  double gslresult;		/* the result from the integration */
  double error;			/* the estimated error from the integration */
  
  gsl_function My_function;

  My_function.function = &my_gsl_integrand;  // further setting up the gsl integration routine.
  gsl_integration_qags (&My_function, lower, upper,
			abs_error, rel_error, 1000, work_ptr, &gslresult,
			&error);

  // open the output file stream
  ofstream Simpsons_out ("Simpsons.dat");	// save data in Simpsons.dat
  Simpsons_out << "#N                        Simpsons                     GSL " << endl;
  Simpsons_out << "#-----------------------------------------" << endl;

  // Simpson's rule requires an odd number of intervals  
  for (int i = 3; i <= max_intervals; i += 2)
  {
    Simpsons_out << setw(4) << log10(i);

    result = simpsons_rule (i, lower, upper, &my_integrand);
    Simpsons_out << setprecision(15) << "  " << scientific << log10(fabs ((result - answer)/(answer))) << "  " <<
	log10(fabs ((gslresult - answer)/(answer)));

    Simpsons_out << endl;
  }
  cout << "data stored";
  Simpsons_out.close ();
  // Milne's rule requires 4i + 1 intervals.
  
  ofstream Milne_out ("Milne.dat");	// save data in integ.dat
  Milne_out << "#N                        Milne                     GSL " << endl;
  Milne_out << "#-----------------------------------------" << endl;
  for (int i = 5; i <= max_intervals; i += 4)
  {
    Milne_out << setw(4) << log10(i);

    result = Milne_rule (i, lower, upper, &my_integrand);
    Milne_out << setprecision(15) << "  " << scientific << log10(fabs ((result - answer)/(answer))) << "  " <<
	log10(fabs ((gslresult - answer)/(answer)));

    Milne_out << endl;
  }
  Milne_out.close ();
  
	   
	  
  

  return (0);
}

//************************************************************************

// the function we want to integrate 
double
my_integrand (double x)
{
  return (exp (-x*x));
}
double 
my_gsl_integrand (double x, void *)
{
	return (exp (-x*x));
}
