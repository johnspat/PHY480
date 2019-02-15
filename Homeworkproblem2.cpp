#include <iostream>		// note that .h is omitted
#include <iomanip>		// note that .h is omitted
#include <fstream>		// note that .h is omitted
#include <cmath>
using namespace std;		// we need this when .h is omitted
#include <gsl/gsl_math.h>
#include <gsl/gsl_diff.h>
//Discussions:
//The two methods are equally precise in lower N sometimes indicated by the relative error being -inf(meaning we're 
//calculating log(0)). Between 10e4.1 and 10e6, there seems to be a linear relationship between N and the relative error
//with the slope fitted to be ~2(2.01564). The overall trend is that as N gets bigger, the relative error increases. The
//downward is more precise because with the upward sum, you are more in danger of subtractive cancellations because the sum
//gets large very quickly at first, and after a while you are adding on numbers that have a difference of more than the
//machine precision, which adds subtractive cancellations. The downward sum avoids this problem by slowly building up
//the sum from the smallest numbers first, and gradually getting bigger.
int
main ()
{ 
   int bigN = 1e8;   // Upper bound for N
   int N = 1;         // initial value for N
   float first_num_sum1 = 1.;  // First number for sum 1
   float first_num_sum2 = 1./N;  // First numbedr for sum 2
   ofstream out ("Homeworkproblem2.dat"); //Opening the output file
  out << "#N               Difference/sum" << endl; // titles for the data file
  while (N < bigN) 
  {
   first_num_sum1 = 1.;  //starting the sum over for each N
   first_num_sum2 = 1./N;
   for (int i = 1; i < N; i++)
      {
	  first_num_sum1 += 1./(i+1);   //sum up
	  first_num_sum2 += 1./(N-i);   //sum down
	  }
	  
	  out << scientific << setprecision(20) << log10(N) << " " << 
	  log10(fabs((first_num_sum1-first_num_sum2))/(.5*(fabs(first_num_sum1)+fabs(first_num_sum2)))) 
	  << endl; //outputting the data.
	  
	  N *= 2;
  }
  cout << setprecision(20) << "Sum Up " << first_num_sum1 << " Sum Down " << first_num_sum2 << endl; //Printing the results
  
 }

