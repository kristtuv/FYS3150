// c++ -std=c++11 -o test.x test.cpp
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>
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
void printVector(double *v, int N) {
	for (int i=0; i < N; i++) {
			cout << setw(20) << v[i] << endl;
	}
}

void MakeEigenvectorArray(double ** Matrix, int N, double *v){
	
	for(int j = 0; j < N; j++){
		
		v[j] = Matrix[j][j];
		
		}
	

	
}
void fileMatrix(double **A, int N, double *k){
	for (int i=0; i < N; i++) {
		ofile << setw(20) << k[i];
		for (int j = 0; j < N; ++j) {
			ofile  << setw(20) << A[i][j] << " ";
		}
		ofile << endl;
	}

}
//Rotating the matrix 
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
//Finding the bigges off diagonal element
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

int Jacobimoffokka(double ** A, double ** R, int N, double rho_max, double omega){
	for(int i = 0; i < N; ++i){
		R[i] = new double[N];
		for (int j = 0; j < N; ++j){
				if (i == j){ R[i][j] = 1.0;}
				else {R[i][j] = 0.0;}
				
			}
			
	}

	double h = rho_max/ (N + 1);
	for(int i=0;i<N; ++i){
		A[i] = new double[N];
		double rho = (i+1)*h; 
		double V = omega*omega*rho*rho;
		for(int j = 0; j < N; j++){
			if(i == j){A[i][j] = 2.0/(h*h) + V;}
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
	vector<int> N = {250};
	vector<double> rho_max = {7.0, 45.0};
	vector<double> omega = {0.01, 0.5, 1.0, 5.0};
	string filename;

	if(numberOfArguments <= 1){
		cout << "Bad Usage" << arguments[0] << "read also filname on same line" << endl;
		exit(1);
	}
	else{filename = arguments[1];
		
		}
	
	for(int l = 0; l<omega.size(); l++){

		ostringstream convert;
		convert << l+1;
		string penis = convert.str();
		string newfilename = filename + "W" + penis;
		
		ofile.open(newfilename);
		ofile << setiosflags(ios::showpoint | ios::uppercase);
		if(l == 0){
		
			for(int i = 0; i < N.size(); i++){
				
				double ** B = new double*[N[i]];
				double ** R = new double*[N[i]];
				double *v = new double[N[i]];

				int iterations = Jacobimoffokka(B, R, N[i], rho_max[1], omega[l]);
				MakeEigenvectorArray(B, N[i], v);
				fileMatrix(R, N[i], v);
				
			    

			    delete [] B; delete [] R; delete [] v;
			    
			}
		}
		else{ 
			for(int i = 0; i < N.size(); i++){
				
				double ** B = new double*[N[i]];
				double ** R = new double*[N[i]];
				double *v = new double[N[i]];

				int iterations = Jacobimoffokka(B, R, N[i], rho_max[0], omega[l]);
				MakeEigenvectorArray(B, N[i], v);
				fileMatrix(R, N[i], v);
				
			    

			    delete [] B; delete [] R; delete [] v;


			}
		}	
	ofile.close();
	}
	return 0;
}


