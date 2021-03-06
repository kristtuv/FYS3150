/*
   Program to solve the two-dimensional Ising model
   with zero external field and no parallelization
   The coupling constant J is set to J = 1
   Boltzmann's constant = 1, temperature has thus dimension energy
   Metropolis aolgorithm  is used as well as periodic boundary conditions.
   The code needs an output file on the command line

*/

#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <random>
#include <armadillo>
#include <string>
#include <mpi.h>
#include <time.h>
using namespace  std;
using namespace arma;
// output file
ofstream ofile;


// inline function for PeriodicBoundary boundary conditions
inline int PeriodicBoundary(int i, int limit, int add) {
    return (i+limit+add) % (limit);
}
// Function to initialise energy and magnetization
void InitializeLattice(int, mat &, double&, double&, string);
// The metropolis algorithm including the loop over Monte Carlo cycles
void MetropolisSampling(int, int, int, double, vec &, string, int &, vec &, bool);


// prints to file the results of the calculations
void WriteResultstoFile(int, int, double, vec, int, bool);

// Main program begins here

int main(int argc, char* argv[])
{
    string outfilename, InitializeMatrix;
    int mcs, my_rank, numprocs;

    double InitialTemp, FinalTemp, TempStep;



    //  MPI initializations
     MPI_Init (&argc, &argv);
     MPI_Comm_size (MPI_COMM_WORLD, &numprocs);
     MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);
     if (my_rank == 0 && argc <= 1) {
       cout << "Bad Usage: " << argv[0] <<
         " read output file" << endl;
       exit(1);
     }
     if (my_rank == 0 && argc > 1) {
       outfilename=argv[1];
       ofile.open(outfilename);
     }
     vector<int> L = {40, 60, 100, 140}; mcs = 2000000;
     //InitialTemp = 2.0; FinalTemp = 2.22; TempStep =0.02; // loop "far" from temperature limit
       InitialTemp = 2.240; FinalTemp = 2.320; TempStep =0.005; //loop close to temperature limit

     /*
     Determine number of intervall which are used by all processes
     myloop_begin gives the starting point on process my_rank
     myloop_end gives the end point for summation on process my_rank
     */
     int no_intervalls = mcs/numprocs;
     int myloop_begin = my_rank*no_intervalls + 1;
     int myloop_end = (my_rank+1)*no_intervalls;
     if ( (my_rank == numprocs-1) &&( myloop_end < mcs) ) myloop_end = mcs;

     // broadcast to all nodes common variables
    // MPI_Bcast (&NSpins, 1, MPI_INT, 0, MPI_COMM_WORLD);
     MPI_Bcast (&InitialTemp, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
     MPI_Bcast (&FinalTemp, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
     MPI_Bcast (&TempStep, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);


    // Start Monte Carlo sampling by looping over the selcted Temperatures

    for(int NSpins:L){
        MPI_Bcast (&NSpins, 1, MPI_INT, 0, MPI_COMM_WORLD);
        cout << "Now running: " << NSpins << endl;
        for (double Temperature = InitialTemp; Temperature <= FinalTemp; Temperature+=TempStep){
            bool Steadystate = true;
            vec ExpectationValues = zeros<mat>(5);

            //This is what is written to file
            vec TotalExpectationValues = zeros<mat>(5);

            vec NumberOfEnergies;
            int AcceptedConfigurations;
            // Start Monte Carlo computation and get expectation values, accepted confiugrations, number of energies and you should start at
            //Steadystate = true
            MetropolisSampling(NSpins, myloop_begin, myloop_end, Temperature, ExpectationValues, InitializeMatrix,\
                               AcceptedConfigurations, NumberOfEnergies, true);

            //Combining the nodes
            for(int i = 0; i < 5; i++){
                MPI_Reduce(&ExpectationValues(i), &TotalExpectationValues(i), 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
            }
            //Only rank 0 writes to file. Steadystate should be true
            if(my_rank == 0){
            WriteResultstoFile(NSpins, mcs, Temperature, TotalExpectationValues, AcceptedConfigurations, true);

            }

        }
    }

    // close output file
    MPI_Finalize();
    return 0;
}



// The Monte Carlo part with the Metropolis algo with sweeps over the lattice
void MetropolisSampling(int NSpins, int myloop_begin, int myloop_end, double Temperature, vec &ExpectationValues, string InitializeMatrix,\
                        int &AcceptedConfigurations, vec &NumberOfEnergies, bool SteadyState = true)
{
    // Initialize the seed and call the Mersienne algo
    std::random_device rd;
    std::mt19937_64 gen(rd());

    // Set up the uniform distribution for x \in [[0, 1]
    std::uniform_real_distribution<double> RandomNumberGenerator(0.0,1.0);

    // Initialize the lattice spin values
    mat SpinMatrix = zeros<mat>(NSpins,NSpins);

    //    initialize energy and magnetization
    double Energy = 0.;     double MagneticMoment = 0.;

    // initialize array for expectation values
    InitializeLattice(NSpins, SpinMatrix, Energy, MagneticMoment, "random");

    // setup array for possible energy changes
    //There is only five possible energies for 2dim ising
    vec EnergyDifference = zeros<mat>(17);

    //counting energies
    //NumberOfEnergies = zeros<mat>(2*2*NSpins*NSpins/4 + 1);


    //counting number of accepted configurations
    AcceptedConfigurations = 0;

    for( int de =-8; de <= 8; de+=4) {
        EnergyDifference(de+8) = exp(-de/Temperature);
    }

    // Start Monte Carlo cycles
    for (int cycles = myloop_begin; cycles <= myloop_end; cycles++) {
        // The sweep over the lattice, looping over all spin sites
        for(int x =0; x < NSpins; x++) {
            for (int y= 0; y < NSpins; y++){
                //Creates random number between 0 and NSpins
                int ix = (int) (RandomNumberGenerator(gen)*(double)NSpins);
                int iy = (int) (RandomNumberGenerator(gen)*(double)NSpins);


                /*
                Choose a random position in the lattice
                Calculate energy in this position and
                Multiply by 2 to get the difference in energy.
                We can multiply by two because flipping one spin
                always gives the same energy but with the oposite sign*/

                int deltaE =  2*SpinMatrix(ix,iy)*
                        (SpinMatrix(ix,PeriodicBoundary(iy,NSpins,-1))+
                         SpinMatrix(PeriodicBoundary(ix,NSpins,-1),iy) +
                         SpinMatrix(ix,PeriodicBoundary(iy,NSpins,1)) +
                         SpinMatrix(PeriodicBoundary(ix,NSpins,1),iy));

                /*
                    if (deltaE <= 0){
                        SpinMatrix(ix,iy) *= -1.0;  // flip one spin and accept new spin config
                        MagneticMoment += (double) 2*SpinMatrix(ix,iy);
                        Energy += (double) deltaE;
                        AcceptedConfigurations += 1;}
                 * This part of the algorithm is not necessary because if deltaE <= 0
                 * then if ( RandomNumberGenerator(gen) <= EnergyDifference(deltaE+8) )
                 * will always be true*/

                if ( RandomNumberGenerator(gen) <= EnergyDifference(deltaE+8) ) {
                    SpinMatrix(ix,iy) *= -1.0;  // flip one spin and accept new spin config
                    MagneticMoment += (double) 2*SpinMatrix(ix,iy);
                    Energy += (double) deltaE;
                    AcceptedConfigurations += 1;
                }
            }
        }
        // couting energies
        //NumberOfEnergies((Energy + 2*NSpins*NSpins)/4) +=1;


        //Update expectationvalues. With or without Steadystate.
        if(SteadyState){
            //cout << "Steady state is reached" << endl;
            if (cycles >= myloop_begin + (myloop_end - myloop_begin)*0.1){

                ExpectationValues(0) += Energy;
                ExpectationValues(1) += Energy*Energy;
                ExpectationValues(2) += MagneticMoment;
                ExpectationValues(3) += MagneticMoment*MagneticMoment;
                ExpectationValues(4) += fabs(MagneticMoment);}}

        else{
            //cout << "Steady state is for pussies" << endl;
            ExpectationValues(0) += Energy;
            ExpectationValues(1) += Energy*Energy;
            ExpectationValues(2) += MagneticMoment;
            ExpectationValues(3) += MagneticMoment*MagneticMoment;
            ExpectationValues(4) += fabs(MagneticMoment);
            }
    }


} // end of Metropolis sampling over spins

// function to initialise energy, spin matrix and magnetization
void InitializeLattice(int NSpins, mat &SpinMatrix,  double& Energy, double& MagneticMoment, string InitializeMatrix)
{
    // Initialize the seed and call the Mersienne algo
    std::random_device rd;
    std::mt19937_64 gen(rd());

    // Set up the uniform distribution for x \in [[0, 1]
    std::uniform_real_distribution<double> RandomNumberGenerator(0.0,1.0);
    // setup spin matrix and initial magnetization
    //If InitializeMatrix = "random" produces a random initial state, "ground" produces the groundstate.
    for(int x =0; x < NSpins; x++) {
        for (int y= 0; y < NSpins; y++)
        {
            if(InitializeMatrix == "random")
            {
                SpinMatrix(x,y) = (int)(RandomNumberGenerator(gen)*2)*2-1; // spin orientation
                MagneticMoment +=  (double) SpinMatrix(x,y);
            }

            else{
            SpinMatrix(x,y) = 1.0; // spin orientation for the ground state
            MagneticMoment +=  (double) SpinMatrix(x,y);
            }
        }
    }
    // setup initial energy
    for(int x =0; x < NSpins; x++) {
        for (int y= 0; y < NSpins; y++){
            Energy -=  (double) SpinMatrix(x,y)*
                    (SpinMatrix(PeriodicBoundary(x,NSpins,-1),y) + SpinMatrix(x,PeriodicBoundary(y,NSpins,-1)));
        }
    }
}// end function initialise



void WriteResultstoFile(int NSpins, int MCcycles, double temperature, vec ExpectationValues, int AcceptedConfigurations, bool Steadystate)
{   //removing 10 percent of MCc if steady state
    if(Steadystate) MCcycles = 0.9*MCcycles;

    double norm = 1.0/((double) (MCcycles));  // divided by  number of cycles to normalize
    double E_ExpectationValues = ExpectationValues(0)*norm;
    double E2_ExpectationValues = ExpectationValues(1)*norm;
    double M_ExpectationValues = ExpectationValues(2)*norm;
    double M2_ExpectationValues = ExpectationValues(3)*norm;
    double Mabs_ExpectationValues = ExpectationValues(4)*norm;

    // all expectation values are per spin, divide by 1/NSpins/NSpins
    //This is so the values does not depend on the size of the lattice
    double Evariance = (E2_ExpectationValues- E_ExpectationValues*E_ExpectationValues)/NSpins/NSpins;
    double Mvariance = (M2_ExpectationValues - Mabs_ExpectationValues*Mabs_ExpectationValues)/NSpins/NSpins;
    ofile << setiosflags(ios::showpoint | ios::uppercase);
    //MCc, NSpins, T, <E>, Cv, <M>, Xi, <|M|>, AcceptedConfigurations
    ofile << setw(15) << setprecision(8) << MCcycles;
    ofile << setw(15) << setprecision(8) << NSpins;
    ofile << setw(15) << setprecision(8) << temperature;
    ofile << setw(15) << setprecision(8) << E_ExpectationValues/NSpins/NSpins;
    ofile << setw(15) << setprecision(8) << Evariance/temperature/temperature;
    ofile << setw(15) << setprecision(8) << M_ExpectationValues/NSpins/NSpins;
    ofile << setw(15) << setprecision(8) << Mvariance/temperature;
    ofile << setw(15) << setprecision(8) << Mabs_ExpectationValues/NSpins/NSpins;
    ofile << setw(15) << setprecision(8) << AcceptedConfigurations << endl;

} // end output function




