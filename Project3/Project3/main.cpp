#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <sstream>
#include "vec3.h"
#include "celestialbody.h"
#include "solarsystem.h"
#include "euler.h"
#include "verlet.h"
#include <fstream>
#include <iomanip>
#include "fullsolarsystem.h"


using namespace std;


int main()
{

    vector<int> numtimesteps = {1000, 10000, 50000, 100000, 1000000};
    //vector<int> numtimesteps = {1000000};
    //double dt = 248.0/numtimesteps[4];

    FullSolarSystem test;
/*
 * Running The twobodysystem solver
 */
    for(int numTimesteps: numtimesteps){

        double dt = 100.0/numTimesteps;

        //test.TwoBodySystemVerlet(numTimesteps, dt);
        //test.TwoBodySystemEuler(numTimesteps, dt);


    }

/*
 * Running the threebodysystem solver
 */
    for(int numTimesteps: numtimesteps){

        double dt = 100.0/numTimesteps;

        //test.ThreeBodySystemRealCenterOfMass(numTimesteps, dt);
        //test.ThreeBodySystemVerlet(numTimesteps, dt);
    }

/*
 * Running The solver for the entire solarsystem
 */

    //test.FullBodySystemVerlet(numtimesteps[4], dt);

/*
 * Running the solver for the precession of mercury
 */
    //test.MercurPerihelion();


    return 0;
}
