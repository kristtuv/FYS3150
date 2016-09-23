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

      int n = (int) pow(10.0,i);

      // Declare new file name
      string fileout = filename;

      // Convert the power 10^i to a string
      string argument = to_string(i);

      // Final filename as filename-i-
      fileout.append(argument);

      //Set steplength h
      double h = 1.0/(n+1);
      double hh = h*h;

      // Set up arrays

      //Right hand side vector
      double *k = new double[n+2];
      double *x = new double[n+2];

      //Temporary matrices
       double *ktilde = new double[n+2];
       double *btilde = new double[n+2];

       //Solution
       double *u = new double[n+2];

       

      // Initializing values on the diagonal


      //Boundary points
      


      float a = -1.0;
      float b = 2.0;
      float c = -1.0;
      float ac = 1.0;

      

      for (int i = 0; i < n+2; i++){
          x[i] = i*h;
          k[i] = hh*f(x[i]);
      }
      //Temporary matrix values
      ktilde[1] = k[i];
      btilde[1] = b;

      //timer
       clock_t start, finish;
       start = clock();
       
      // Forward substitution
      for (int i = 2; i <= n ; i++) {
          btilde[i] = b - 1.0/btilde[i-1];
          ktilde[i] = k[i] + ktilde[i-1]/btilde[i-1];
      }

      // Backward substitution
      u[n] = ktilde[n]/btilde[n];
      

      for (int i = n-1; i >= 0; i--) {
          u[i] = (ktilde[i]+u[i+1])/btilde[i];
      }

      finish = clock();
      cout << "n = " << n << endl;
      cout<< "Time elapsed: "<< (float(finish) - float(start))/CLOCKS_PER_SEC << endl;
      
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
