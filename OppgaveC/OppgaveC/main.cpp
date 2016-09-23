#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <time.h>


using namespace std;

// object for output files
ofstream ofile;

// Declaring functions we have from the analytical solution
double f(double x){
    return 100*exp(-10.0*x);
}

double exact(double x) {
    return 1.0-(1-exp(-10))*x-exp(-10*x);
}

int main(int argc, char *argv[]){
  int exponent;
    string filename;

    // We read also the basic name for the output file and the highest power of 10^n we want
    if( argc <= 1 ){
          cout << "Bad Usage: " << argv[0] <<
              " read also file name on same line and max power 10^n" << endl;
          exit(1);
    }
        else{
        filename = argv[1]; // first command line argument after name of program
        exponent = atoi(argv[2]);
    }
    // Loop over powers of 10
    for (int i = 1; i <= exponent; i++){

      int  n = (int) pow(10.0,i);

      // Declare new file name
      string fileout = filename;

      // Convert the power 10^i to a string
      string argument = to_string(i);

      // Final filename as filename-i-
      fileout.append(argument);

      //Set steplength h
      double h = 1.0/(n);
      double hh = h*h;

      // Set up arrays
      //Matrix elements
      clock_t start, finish;
      start = clock();
      int a = -1; int c = -1; int b = 2; int ac = 1;

      //Right hand side vector
      double *k = new double[n];
      double *x = new double[n];

      //Temporary matrices
       double *ktilde = new double[n];
       double *btilde = new double[n];

       //Solution
       double *u = new double[n];




      //Boundary points
      u[0] = u[n-1] = 0.0;





      for (int i = 0; i <= n-1; i++){
          x[i] = i*h;
          k[i] = hh*f(x[i]);
      }
      //Temporary matrix values
      ktilde[0] = k[0];
      btilde[0] = b;
      // Forward substitution
      for (int i = 1; i < n; i++) {
          btilde[i] = b - ac/btilde[i-1];
          ktilde[i] = k[i] - ktilde[i-1]*a/btilde[i-1];
      }

      // Backward substitution
      u[n-1] = ktilde[n-1]/btilde[n-1];

      for (int i = n-2; i > 0; i--) {
          u[i] = (ktilde[i]-c*u[i+1])/btilde[i];
      }

      finish = clock();
      cout << "n = " << n << endl;
      cout<< "Time elapsed C: "<<(float(finish) - float(start))/CLOCKS_PER_SEC << endl;
      //cout <<"u2 = "<< u[2] << endl;
      //cout << "exact = "<< exact(x[2]) << endl;
      //cout << "ktilde =  "<< ktilde[2] << endl;
      //cout << "u3 = " << u[3] << endl;
      //cout << "btilde = " << btilde[2] <<endl;
      //cout << endl;

      ofile.open(fileout);
      ofile << setiosflags(ios::showpoint | ios::uppercase);
          //      ofile << "       x:             approx:          exact:       relative error" << endl;
          double max;

          double *err = new double[n];
         for (int i = 1; i < n; i++) {
            err[i] = log10(fabs((exact(x[i])-u[i])/exact(x[i])));
                if(err[i] > err[i - 1]){
                    max = err[i];

                }

            ofile << setw(15) << setprecision(8) << x[i];
            ofile << setw(15) << setprecision(8) << u[i];
            ofile << setw(15) << setprecision(8) << exact(x[i]);
            ofile << setw(15) << setprecision(8) << err[i] << endl;

          }
         cout << "Maximum Error: " << max << endl << endl;

      ofile.close();
      delete [] x; delete [] btilde; delete [] ktilde; delete [] u; delete [] k; delete [] err;


}

    return 0;
}
