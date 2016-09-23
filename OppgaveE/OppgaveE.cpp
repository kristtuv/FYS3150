#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <armadillo>

using namespace std;
using namespace arma;


//Output files
ofstream ofile;

//right hand side f(x)
double f(double x) {
	return 100.0*exp(-10.0*x);
}
//exact solution
double exact(double x){
	return 1.0 - (1 - exp(-10))*x - exp(-10*x);
}

int main(int argc, char *argv[]){
	int exponent;
	string filename;
	if(argc <= 1){
		cout << "Bad Usage: " << argv[0] <<
			"read also file name on same line and max power 10^n" << endl;
		exit(1);
	}
	else{
		filename = argv[1];
		exponent = atoi(argv[2]);
	}
	//Loop over powers of 10
	for (int i = 1; i<= exponent; i++){
		int n = (int) pow(10.0,i);
		string fileout = filename;

		string argument = to_string(i);
		fileout.append(argument);

		double h = 1.0/n;
		double hh = h*h;

		n = n-1; //We only want to study points between the endpoints
		mat A = zeros<mat>(n,n); //Making matrix of size nxn with zeros

		vec k(n);
		vec x(n);
		
		//filling in endpoints
		A(0,0) = 2.0; 
		A(0,1) = -1; 
		A(n-1, n-2) = -1.0; 
		A(n-1,n-1) = 2.0;
		x(0) = h; //we exclude the endpoint x0=0, first point is 0+h=h
		k(0) = hh*f(x(0)); //right hand side of equation
		x(n-1) = x(0) + (n-1)*h; //last point of x, we exclude endpoint x=1
		k(n-1) = hh*f(x(n-1));
		
		//Filling matrix A on the diagonal and subdiagonal
		//filling vectors x and k
		for (int i = 1; i < n-1; i++){
			x(i) = x(i-1) + h;
			k(i) = hh*f(x(i));
			A(i, i-1) = -1.0;
			A(i,i) = 2.0;
			A(i,i+1) = -1.0;

		}
		//using armadillo to solve the equation
		vec u = solve(A,k);

		//write to file
		ofile.open(fileout);
		ofile << setiosflags(ios::showpoint);
		for (int i=0; i< n; i++){
			double error = log10(fabs((exact(x(i)) - u(i))/exact(x(i))));

			ofile << setw(25) << setprecision(8) << x(i);
			ofile << setw(25) << setprecision(8) << u(i); 
			ofile << setw(25) << setprecision(8) << exact(x(i));
			ofile << setw(25) << setprecision(8) << error << endl;


		}
		ofile.close();







	}
	return 0;
}
