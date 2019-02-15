//  file: area.cpp
//
//  This program calculates the area of a circle, given the radius.
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      02-Jan-2004  original version, for 780.20 Computational Physics
//      01-Jan-2010  updates to "To do" wishlist
//      12-Jan-2016  comment out "using namespace std;"
//
//  Notes:  
//   * compile with:  "g++ -o area.x area.cpp"
//
//  To do:
//   1. output the answer with higher precision (more digits)
//   2. use a "predefined" value of pi or generate it with atan
//   3. define an inline square function
//   4. split the calculation off into a function (subroutine)
//   5. output to a file (and/or input from a file)
//   6. add checks of the input (e.g., for non-positive radii)
//   7. rewrite using a Circle class
//
//*********************************************************************// 

// include files
#include <iostream>		// note that .h is omitted
#include <iomanip>		// note that .h is omitted
#include <fstream>		// note that .h is omitted
using namespace std;		// we need this when .h is omitted
#include <gsl/gsl_math.h>
#include <gsl/gsl_diff.h>

//*********************************************************************//

const double pi = M_PI;   // define pi as a constant 
inline double square(double radius)
{
	return radius*radius;
}
 double area(double radius)
  {
     return pi*square(radius);
  }
int
main ()
{
  double radius;    // every variable is declared as int or double or ...

  cout << "Enter the radius of a Circle: ";	// ask for radius
  cin >> radius;
  if ( radius < 0 ) {
  cout << "radius = " << setprecision(20) << radius << "  area = " << "area is not defined" << endl;
  }
  else {
  cout << "radius = " << setprecision(20) << radius << "  area = " << area(radius) <<endl;
  ofstream out ("area.dat");	// open the output file
  out << "radius" << "   " << "area of circle" << endl;
  out << radius << "          " << area(radius);
  }

  return 0;			// "0" for successful completion
}

//*********************************************************************//
