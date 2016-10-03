// c++ -std=c++11 -o test.x test.cpp
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
using namespace std;

// object for output files
ofstream ofile;



void printMatrix(double **A, int N) {
	for (int i=0; i < N; i++) {
		for (int j = 0; j < N; ++j) {
			cout << setw(20) << A[i][j] << " ";
		}
		cout << endl;
	}
}

void rotate(double ** A, double ** R, int k, int l, int N)
{
		double s, c;
		if (A[k][l] != 0.0){
			double t, tau;
			tau = (A[l][l] - A[k][k])/(2*A[k][l]);
			if (tau > 0){
				t = 1.0/(tau + sqrt(1.0 + tau*tau));
			}
			else{
				t = -1.0/(-tau + sqrt(1.0 + tau*tau));
			}
	
			c = 1/sqrt(1 + t*t);
			s = c*t;
		}
		else{
			c = 1.0;
			s = 0.0;
		}

		double akk, all, aik, ail, rik, ril;
		akk = A[k][k];
		all = A[l][l];
		//Changing the matrix elements with indices k and l
		A[k][k] = c*c*akk - 2.0*c*s*A[k][l] + s*s*all;
		A[l][l] = s*s*akk + 2.0*c*s*A[k][l] + c*c*all;
		A[k][l] = 0.0;
		A[l][k] = 0.0;

		for(int i = 0; i<N; i++){
			if (i != k && i != l){
				aik = A[i][k];
				ail = A[i][l];
				A[i][k] = c*aik - s*ail;
				A[k][i] = A[i][k];
				A[i][l] = c*ail + s*aik;
				A[l][i] = A[i][l];
			}
			rik = R[i][k];
			ril = R[i][l];
			R[i][k] = c*rik - s*ril;
			R[i][l] = c*ril + s*rik;

		}
		return;
	}

double maxoffdiagmoffokka(double ** A, int *k, int *l, int N){
	double max = 0.0;

	for (int i = 0; i < N; i++){
		for (int j = i + 1; j<N; j++){
			if (fabs(A[i][j]) > max) {
				max = fabs(A[i][j]);
				*l = i;
				*k = j;
			}
		}
	}
	return max;
}	

int Jacobimoffokka(double ** A, double ** R, int N){
	for(int i = 0; i < N; ++i){
		R[i] = new double[N];
		for (int j = 0; j < N; ++j){
				if (i == j){ R[i][j] = 1.0;}
				else {R[i][j] = 0.0;}
				
			}
			
	}

	double rho_max = 6.0;
	double h = rho_max/ (N + 1);

	for(int i=0;i<N; ++i){
		A[i] = new double[N];
		double rho = (i+1)*h; 

		for(int j = 0; j < N; j++){
			if(i == j){A[i][j] = 2.0/(h*h) + rho*rho;}
			else if(i == j+1 || i+1 == j){A[i][j] = -1.0/(h*h);}
			else{A[i][j] = 0.0;}
		} 
	}
	
	int k, l;
	double eps = 1.0e-8;
	long MaxIterations = N*N*N;
	int iterations = 0;
	double MaxOffdiag = maxoffdiagmoffokka(A, &k, &l, N);
	while (fabs(MaxOffdiag) > eps && iterations < MaxIterations){
		MaxOffdiag = maxoffdiagmoffokka(A, &k, &l, N);
		rotate(A, R, k, l, N);
		iterations++;
		
	}
	
	cout << "Number of iterations: " << iterations << endl;
	return iterations;


}
	

int main(int numberOfArguments, char **arguments) {
	vector<int> N = {10, 50, 100, 150, 200};
	
	string filename;

	if(numberOfArguments <= 1){
		cout << "Bad Usage" << arguments[0] << "read also filname on same line" << endl;
		exit(1);
	}
	else{filename = arguments[1];
		
		}
	ofile.open(filename);
	ofile << setiosflags(ios::showpoint | ios::uppercase);
	for(int i = 0; i < N.size(); i++){
		
		double ** B;
		B = new double*[N[i]];
		double ** R;
		R = new double*[N[i]];

		/*
		double ** T;
		T = new double*[N;
		for (int i = 0; i<N; i++){
			T[i] = new double[N];
		}
		T[0][0] = 3.0;
		T[0][1] = 2.0;
		T[0][2] = 4.0;
		T[1][0] = 2.0;
		T[1][1] = 0.0;
		T[1][2] = 2.0;
		T[2][0] = 4.0;
		T[2][1] = 2.0;
		T[2][2] = 3.0;
		*/
		
		int iterations = Jacobimoffokka(B, R, N[i]);

		//cout << "R: " << endl;
		//printMatrix(R, N[i]);
		//cout << endl << "B: " << endl;
		//printMatrix(B, N[i]);

		
	    
	    
	    ofile << setw(10) << N[i];
	    ofile << setw(10) << iterations << endl;

	    
	    
	    delete [] B; delete [] R;
	    
	}
	ofile.close();
	return 0;
}


