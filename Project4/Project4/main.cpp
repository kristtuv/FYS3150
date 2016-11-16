/*
   Program to solve the two-dimensional Ising model
   with zero external field and no parallelization
   The coupling constant J is set to J = 1
   Boltzmann's constant = 1, temperature has thus dimension energy
   Metropolis aolgorithm  is used as well as periodic boundary conditions.
   The code needs an output file on the command line and the variables mcs, nspins,
   initial temp, final temp, temp step and "ground" or "random" to set the initial states.


*/

#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <random>
#include <armadillo>
#include <string>
#include <time.h>
using namespace  std;
using namespace arma;
// output file
ofstream ofile;
ofstream yofile;

// inline function for PeriodicBoundary boundary conditions
inline int PeriodicBoundary(int i, int limit, int add) {
    return (i+limit+add) % (limit);
}
// Function to initialise energy and magnetization
void InitializeLattice(int, mat &, double&, double&, string);

// The metropolis algorithm including the loop over Monte Carlo cycles
void MetropolisSampling(int, int, double, vec &, string, int &, vec &, bool);


// prints to file the results of the calculations
void WriteResultstoFile(int, int, double, vec, int, bool);

//Writing Number of Energies to file for making probability-plot
void WriteNumberOfEnergies(double, vec);

// Main program begins here

int main(int argc, char* argv[])
{
    string filename, InitializeMatrix;
    int NSpins, MCcycles;
    double InitialTemp, FinalTemp, TempStep;
    if (argc <= 6) {
        cout << "Bad Usage: " << argv[0] <<
                " read output file, Number of spins, MC cycles, initial and final temperature, temperatur step and ('random' or 'ground')" << endl;
        exit(1);
    }
    else {
        filename=argv[1];
        NSpins = atoi(argv[2]);
        MCcycles = atoi(argv[3]);
        InitialTemp = atof(argv[4]);
        FinalTemp = atof(argv[5]);
        TempStep = atof(argv[6]);
        InitializeMatrix = argv[7];
    }
    // Declare new file name and add lattice size to file name
    string fileout = filename;
    string argument = to_string(NSpins);
    string MonteCarloCycles = to_string(MCcycles);
    string CountFilename = "CountingEnergies";
    fileout.append(argument);
    fileout.append(InitializeMatrix);
    CountFilename.append(MonteCarloCycles);

    ofile.open(fileout, std::ios_base::app);
    yofile.open(CountFilename);
    bool SteadyState = true;


    // Start Monte Carlo sampling by looping over the selcted Temperatures

    for (double Temperature = InitialTemp; Temperature <= FinalTemp; Temperature+=TempStep){
        vec ExpectationValues = zeros<mat>(5);
        vec NumberOfEnergies;
        int AcceptedConfigurations;
        // Start Monte Carlo computation and get expectation values,for steady state set Steadystate=true
        MetropolisSampling(NSpins, MCcycles, Temperature, ExpectationValues, InitializeMatrix,\
                           AcceptedConfigurations, NumberOfEnergies, SteadyState);

        //WriteResultstoFile(NSpins, MCcycles, Temperature, ExpectationValues, AcceptedConfigurations, SteadyState)
        WriteResultstoFile(NSpins, MCcycles, Temperature, ExpectationValues, AcceptedConfigurations, true);

        //WriteNumberOfEnergies(Temperature, NumberOfEnergies);
        void WriteNumberOfEnergies(Temperature, NumberOfEnergies);
    }
    ofile.close();
    yofile.close();
    // close output file
    return 0;
}



// The Monte Carlo part with the Metropolis algo with sweeps over the lattice
void MetropolisSampling(int NSpins, int MCcycles, double Temperature, vec &ExpectationValues, string InitializeMatrix,\
                        int &AcceptedConfigurations, vec &NumberOfEnergies, bool SteadyState = false)
{
    // Initialize the seed and call the Mersenne algorithm
    std::random_device rd;
    std::mt19937_64 gen(rd());

    // Set up the uniform distribution for x \in [[0, 1]
    std::uniform_real_distribution<double> RandomNumberGenerator(0.0,1.0);

    // Initialize the lattice spin values
    mat SpinMatrix = zeros<mat>(NSpins,NSpins);

    //    initialize energy and magnetization
    double Energy = 0.;     double MagneticMoment = 0.;

    // initialize array for expectation values
    InitializeLattice(NSpins, SpinMatrix, Energy, MagneticMoment, InitializeMatrix);

    // setup array for possible energy changes
    //There is only five possible energies for 2dim ising model
    vec EnergyDifference = zeros<mat>(17);

    //Countning energies
    NumberOfEnergies = zeros<mat>(2*2*NSpins*NSpins/4 + 1);


    //counting number of accepted configurations
    AcceptedConfigurations = 0;

    for( int de =-8; de <= 8; de+=4) {
        EnergyDifference(de+8) = exp(-de/Temperature);
        //cout << Temperature << " " << EnergyDifference(de+8) << endl;
    }

    // Start Monte Carlo cycles
    for (int cycles = 1; cycles <= MCcycles; cycles++){
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
        // update energycounter
        NumberOfEnergies((Energy + 2*NSpins*NSpins)/4) +=1;

        //Update expectationvalues. With or without Steadystate.
        if(SteadyState){
            //cout << "Steady state is reached" << endl;
            if (cycles >= MCcycles*0.1){

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
    //If InitializeMatrix = "random" produces a random initial state, "ground" produces the groundstate. Arguments entered on commandline
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
{   //Removing 10 percent of the cycles of steady state
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
    //MCc, T, <E>, Cv, <M>, Xi, <|M|>, AcceptedConfigurations
    ofile << setw(15) << setprecision(8) << MCcycles;
    ofile << setw(15) << setprecision(8) << temperature;
    ofile << setw(15) << setprecision(8) << E_ExpectationValues/NSpins/NSpins;
    ofile << setw(15) << setprecision(8) << Evariance/temperature/temperature;
    ofile << setw(15) << setprecision(8) << M_ExpectationValues/NSpins/NSpins;
    ofile << setw(15) << setprecision(8) << Mvariance/temperature;
    ofile << setw(15) << setprecision(8) << Mabs_ExpectationValues/NSpins/NSpins;
    ofile << setw(15) << setprecision(8) << AcceptedConfigurations << endl;

} // end output function

void WriteNumberOfEnergies(double Temperatur, vec NumberOfEnergies){

    //Write number of energies to file
    for(int i = 0; i < NumberOfEnergies.size(); i++){
    yofile << setiosflags(ios::showpoint);
    yofile << setw(15) <<setprecision(8) << Temperatur;
    yofile << resetiosflags(ios::showpoint);
    yofile << setw(15) << NumberOfEnergies(i) << endl;}



}


