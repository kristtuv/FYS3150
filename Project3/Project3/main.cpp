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

void twobodysystem(int numTimesteps, double dt)
{
    solarsystem twoBodySystem;
    CelestialBody &sun = twoBodySystem.createCelestialBody( vec3(0.0, 0.0, 0.0), vec3(0.0, 0.0 ,0.0 ), 1.0 );
    CelestialBody &earth = twoBodySystem.createCelestialBody(vec3(1.0, 0.0, 0.0), vec3(0.0, 2.8277*M_PI, 0.0), 3e-6);
    vector<CelestialBody> &bodies = twoBodySystem.bodies();

    ostringstream convert;
    convert << numTimesteps;
    string timesteps = convert.str();
    string filename = "positionsTimesteps" + timesteps;
    cout << filename<< endl;

    for(int i = 0; i < bodies.size(); i++)
    {CelestialBody &body = bodies[i];}

    ofstream ofile;



    ofile.open(filename+"Verlet");

    verlet integrateVerlet(dt);
    for(int timestep = 0; timestep< numTimesteps; timestep++)
    {
        integrateVerlet.integrateOneStep(twoBodySystem);
        //twoBodySystem.writeToFileTuv("positionsverlet.xyz");
        ofile << earth.position.x() << " " << earth.position.y() << " " << twoBodySystem.kineticEnergy() << " ";
        ofile << twoBodySystem.potentialEnergy() << " " << twoBodySystem.angularmomentum() << endl;

    }

    ofile.close();
    cout << earth.velocity << endl;
}


int main()
{
    vector<int> numtimesteps = {1000, 10000, 50000, 100000, 1000000};
    double dt = 1.0/numtimesteps[2];
    FullSolarSystem test;
    //for(int numTimesteps: numtimesteps){
    //    double dt = 1.0/numTimesteps;

    //    test.TwoBodySystemVerlet(numTimesteps, dt);
    //    test.TwoBodySystemEuler(numTimesteps, dt);

    //}

    //test.TwoBodySystemVerlet(numtimesteps[4], dt);
    //double dt = 0.001;
    //test.ThreeBodySystemVerlet(numtimesteps[4], dt);

    //test.FullBodySystemVerlet(numtimesteps[4], dt);

    //test.ThreeBodySystemRealCenterOfMass(numtimesteps[4], dt);
    test.MercurPerihelion();


    return 0;
}
