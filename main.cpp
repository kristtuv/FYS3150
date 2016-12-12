#include "math/random.h"
#include "lennardjones.h"
#include "velocityverlet.h"
#include "system.h"
#include "statisticssampler.h"
#include "atom.h"
#include "io.h"
#include "unitconverter.h"
#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

int main(int numberOfArguments, char **argumentList)
{
    int numberOfUnitCells = 7;
    int temperature_index_start = 620; //Starting initial temperature
    int temperature_index_finish = 620;
    int temperature_step = 10;


    double latticeConstant = UnitConverter::lengthFromAngstroms(5.26); // measured in angstroms <- hvorfor?
    double Sigma = UnitConverter::lengthFromAngstroms(3.405); //angstroms


    double epsilon = UnitConverter::temperatureFromSI(119.8); //measured in Kelvin
    //cout<< UnitConverter::lengthToSI(5.26)*5*5*5*UnitConverter::lengthToSI(5.26)*UnitConverter::lengthToSI(5.26) << endl;
    //cout << UnitConverter::temperatureFromSI(84) << endl;
    //cout << initialTemperature << endl;
    //exit(1);



    double dt = UnitConverter::timeFromSI(1e-14); // Measured in seconds.

    double mass = UnitConverter::massFromSI(6.63352088e-26); // Atom mass in kg
    cout << "The density is at t0: " << 4*UnitConverter::massToSI(mass)/pow(UnitConverter::lengthToSI(UnitConverter::lengthFromAngstroms(latticeConstant)),3)
        << "kg/meters^3" << endl;

    //cout << "One unit of length is " << UnitConverter::lengthToSI(1.0) << " meters" << endl;
    //cout << "One unit of velocity is " << UnitConverter::velocityToSI(1.0) << " meters/second" << endl;
    //cout << "One unit of time is " << UnitConverter::timeToSI(1.0) << " seconds" << endl;
    //cout << "One unit of mass is " << UnitConverter::massToSI(1.0) << " kg" << endl;
    //cout << "One unit of temperature is " << UnitConverter::temperatureToSI(1.0) << " K" << endl;






    //IO movie("penis.xyz"); // To write the state to file

    //cout << setw(20) << "Timestep" <<
    //        setw(20) << "Time" <<
    //        setw(20) << "Temperature" <<
    //        setw(20) << "KineticEnergy" <<
    //        setw(20) << "PotentialEnergy" <<
    //        setw(20) << "TotalEnergy" << endl;

    clock_t start, finish; // Program-timer start
    // INTEGRATING LOOP

    for(temperature_index_start; temperature_index_start <= temperature_index_finish; temperature_index_start += temperature_step){
        start = clock();
        int T = temperature_index_start;
        double initialT = UnitConverter::temperatureFromSI(T);
        StatisticsSampler statisticsSampler;
        System system;
        system.createFCCLattice(numberOfUnitCells, latticeConstant, initialT, mass);
        cout << epsilon << endl;
        system.potential().setEpsilon(epsilon);
        system.potential().setSigma(Sigma);
        system.removeTotalMomentum();


        string filename = "StatisticsTemperature" + to_string(T) + ".txt";

        for(int timestep=0; timestep<20000; timestep++) {
            system.step(dt);
            statisticsSampler.setfilename(filename);
            statisticsSampler.sample(system);
       if( timestep % 2000 == 0 ) {
            //Print the timestep every 100 timesteps
           cout << setw(20) << setprecision(10) << system.steps() << " " <<
                   setw(20) << system.time() <<
                   //setw(20) << UnitConverter::temperatureToSI( statisticsSampler.temperature()) <<
                   setw(20) << UnitConverter::temperatureToSI( statisticsSampler.temperature()) <<
                   setw(20) << statisticsSampler.kineticEnergy() <<
                   setw(20) << statisticsSampler.potentialEnergy() <<
                   setw(20) << statisticsSampler.totalEnergy() <<
                   setw(20) << statisticsSampler.diffusionConstant() <<
                   setw(20) << statisticsSampler.rSquared() <<
                   setw(20) << T << endl;
       }
        //movie.saveState(system);

        }

        statisticsSampler.close();

        //movie.close();
        finish = clock();
        double runTime = ((finish - start)/(double(CLOCKS_PER_SEC)))/60;
        double timeleft = runTime*(temperature_index_finish - temperature_index_start)/temperature_step;
        cout << "Initial Temperature: " << T << "  Time used: " << runTime << " minutes.  "
             << "  Estimated time left: " << timeleft << " minutes" << endl; // Program-timer stop
        cout << endl;
    }
    return 0;

}
