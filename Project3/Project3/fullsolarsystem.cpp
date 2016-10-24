#include "fullsolarsystem.h"
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
#include "time.h"

FullSolarSystem::FullSolarSystem()
{

}

void FullSolarSystem::TwoBodySystemEuler(int NumTimeSteps, double dt)
{
    solarsystem twoBodySystem;
    CelestialBody &sun = twoBodySystem.createCelestialBody( vec3(0.0, 0.0, 0.0), vec3(0.0, 0.0 ,0.0 ), 1.0 );
    CelestialBody &earth = twoBodySystem.createCelestialBody(vec3(1.0, 0.0, 0.0), vec3(0.0, 2*M_PI, 0.0), 3e-6);
    vector<CelestialBody> &bodies = twoBodySystem.bodies();

    ostringstream convert;
    convert << NumTimeSteps;
    string timesteps = convert.str();
    string filename = "positionsTimesteps" + timesteps;
    cout << filename<< endl;

    for(int i = 0; i < bodies.size(); i++)
    {CelestialBody &body = bodies[i];}

    ofstream ofile;
    ofstream yofile;


    ofile.open(filename+"Euler");
    yofile.open("EnergyAndMomentumEuler");
    clock_t start, finish;
    start =clock();
    Euler integrateEuler(dt);
    for(int timestep = 0; timestep< NumTimeSteps; timestep++)
    {
        integrateEuler.integrateOneStep(twoBodySystem);
        ofile << earth.position.x() << " " << earth.position.y() << " " << twoBodySystem.kineticEnergy() << " ";
        ofile << twoBodySystem.potentialEnergy() << " " << twoBodySystem.angularmomentum() << endl;
        yofile << twoBodySystem.potentialEnergy() << " " << twoBodySystem.kineticEnergy();
        yofile << " " << twoBodySystem.angularmomentum().length() << endl;
    }
    finish =clock();

    //cout << "Euler: " << " " << (finish - start)/CLOCKS_PER_SEC << endl;
    ofile.close();
}

void FullSolarSystem::TwoBodySystemVerlet(int NumTimeSteps, double dt)
{
    solarsystem twoBodySystem;
    CelestialBody &sun = twoBodySystem.createCelestialBody( vec3(0.0, 0.0, 0.0), vec3(0.0, 0.0 ,0.0 ), 1.0 );
    CelestialBody &earth = twoBodySystem.createCelestialBody(vec3(1.0, 0.0, 0.0), vec3(0.0, 2*M_PI, 0.0), 3e-6);

    vector<CelestialBody> &bodies = twoBodySystem.bodies();

    ostringstream convert;
    convert << NumTimeSteps;
    string timesteps = convert.str();
    string filename = "positionsTimesteps" + timesteps;
    cout << filename<< endl;

    for(int i = 0; i < bodies.size(); i++)
    {CelestialBody &body = bodies[i];}

    ofstream ofile;
    ofstream yofile;


    ofile.open(filename+"Verlet");
    yofile.open("EnergyAndMomentumVerlet");
    clock_t start, finish;
    start = clock();
    verlet integrateVerlet(dt);
    for(int timestep = 0; timestep< NumTimeSteps; timestep++)
    {
        integrateVerlet.integrateOneStep(twoBodySystem);
        ofile << earth.position.x() << " " << earth.position.y() << endl;
        yofile << twoBodySystem.potentialEnergy() << " " << twoBodySystem.kineticEnergy();
        yofile << " " << twoBodySystem.angularmomentum().length() << endl;

    }

    finish = clock() ;
    //cout << "Verlet: " << " " << ((finish - start)/CLOCKS_PER_SEC) << endl;
    ofile.close();
    yofile.close();
}
void FullSolarSystem::ThreeBodySystemVerlet(int NumTimeSteps, double dt)
{
    solarsystem threeBodySystem;
    vector<CelestialBody> &bodies = threeBodySystem.bodies();

    CelestialBody &sun = threeBodySystem.createCelestialBody( vec3(0.0, 0.0, 0.0),
                                                             vec3(0.0, 0.0 ,0.0 ),
                                                             1.0 );


    CelestialBody &earth = threeBodySystem.createCelestialBody(vec3(1.0, 0.0 , 0.0),
                                                              vec3(0.0, 2*M_PI, 0.0),
                                                              3e-6);

    CelestialBody &jupiter = threeBodySystem.createCelestialBody( vec3(5.20, 0.0, 0.0),
                                                                 vec3(0.0, 0.83*M_PI ,0.0 ),
                                                                 1*0.95e-3);

    for(int i = 0; i < bodies.size(); i++)
    {CelestialBody &body = bodies[i];}

    ostringstream convert;
    convert << NumTimeSteps;
    string timesteps = convert.str();
    string filename = "positionsTimesteps" + timesteps;

    ofstream ofile;
    ofstream yoyofile;
    ofile.open(filename+"Earth");
    yoyofile.open(filename+"Jupiter");
    verlet integrateVerlet(dt);
    for(int timestep = 0; timestep< NumTimeSteps; timestep++)
    {
        integrateVerlet.integrateOneStep(threeBodySystem);
        ofile << earth.position.x() << " " << earth.position.y() << endl;
        yoyofile << jupiter.position.x() << " " << jupiter.position.y() << endl;
    }
    ofile.close();
    yoyofile.close();
}
void FullSolarSystem::ThreeBodySystemRealCenterOfMass(int NumTimeSteps, double dt)
{
    solarsystem threeBodySystem;
    vector<CelestialBody> &bodies = threeBodySystem.bodies();
    CelestialBody &sun = threeBodySystem.createCelestialBody( vec3(0.0, 0.0, 0.0),
                                                             vec3(0.0, 0.0 ,0.0 ),
                                                             1.0 );


    CelestialBody &earth = threeBodySystem.createCelestialBody(vec3(1.0, 0.0 , 0.0),
                                                              vec3(0.0, 2*M_PI, 0.0),
                                                              3e-6);

    CelestialBody &jupiter = threeBodySystem.createCelestialBody( vec3(5.20, 0.0, 0.0),
                                                                 vec3(0.0, 0.83*M_PI ,0.0 ),
                                                                 1*0.95e-3);

    vec3 MC = threeBodySystem.FindMassCenter();
    vec3 momentum = threeBodySystem.momentum();
    sun.position -=  MC;
    earth.position -= MC;
    jupiter.position -= MC;
    sun.velocity += momentum;


    //sun.position = vec3(sun.position.x()-MC, vec3(sun.position.y()-MC, vec3(sun.position.x()-MC)


    for(int i = 0; i < bodies.size(); i++)
    {CelestialBody &body = bodies[i];}

    ostringstream convert;
    convert << NumTimeSteps;
    string timesteps = convert.str();
    string filename = "positionsTimesteps" + timesteps;




    ofstream ofile;
    ofstream yoyofile;



    ofile.open(filename+"EarthReal");
    yoyofile.open(filename+"JupiterReal");
    verlet integrateVerlet(dt);
    for(int timestep = 0; timestep< NumTimeSteps; timestep++)
    {

        integrateVerlet.integrateOneStep(threeBodySystem);
        ofile << earth.position.x() << " " << earth.position.y() << endl;
        yoyofile << jupiter.position.x() << " " << jupiter.position.y() << endl;


    }

    ofile.close();
    yoyofile.close();
}
void FullSolarSystem::FullBodySystemVerlet(int NumTimeSteps, double dt)
{
    solarsystem fullBodySystem;
        CelestialBody &sun = fullBodySystem.createCelestialBody( vec3(3.567569132518468E-03, 3.402725585472963E-03, 0.0),
                                                                 vec3(-1.987631356370456E-06*365, 6.841214093898640E-06*365 ,0.0 ),
                                                                 1.0 );
      CelestialBody &mercury = fullBodySystem.createCelestialBody( vec3(-3.448088926082000E-01, 1.060250803722253E-01, 0.0),
                                                                     vec3(-1.377317016029842E-02*365, -2.577724446766713E-02*365 ,0.0 ),
                                                                     1.2e-7 );
      CelestialBody &venus = fullBodySystem.createCelestialBody( vec3(1.814959969646973E-01, -7.018747180931129E-01, 0.0),
                                                                   vec3(1.947420769434422E-02*365, 4.885314858116717E-03*365 ,0.0 ),
                                                                   2.45e-6 );
        CelestialBody &earth = fullBodySystem.createCelestialBody(vec3(9.356619245372438E-01, 3.583403516829250E-01, 0.0),
                                                                  vec3(-6.405361360564236E-03*365, 1.601367683562308E-02*365, 0.0),
                                                                  3e-6);
        CelestialBody &mars = fullBodySystem.createCelestialBody( vec3(1.153835515595857, -7.631393683685221E-01, 0.0),
                                                                  vec3(8.290101223222136E-03*365, 1.285064506000931E-02*365 ,0.0 ),
                                                                  3.3e-7 );
        CelestialBody &jupiter = fullBodySystem.createCelestialBody( vec3(-5.429091121847574, -4.464121857033960E-01, 0.0),
                                                                     vec3(5.310921442239308E-04*365, -7.163232763813381E-03*365 ,0.0 ),
                                                                     0.95e-3);
        CelestialBody &saturn = fullBodySystem.createCelestialBody( vec3(-2.272178928493247, -9.773535746042706, 0.0),
                                                                    vec3(5.127458852019526E-03*365, -1.281135103943108E-03*365 ,0.0 ),
                                                                    2.75e-4 );
        CelestialBody &uranus = fullBodySystem.createCelestialBody( vec3(1.846474430744711E+01, 7.557968549777230E+00, 0.0),
                                                                    vec3(-1.518690330813693E-03*365, 3.456622065519562E-03*365 ,0.0 ),
                                                                    4.4e-5 );
        CelestialBody &neptun = fullBodySystem.createCelestialBody( vec3(2.825991344979922E+01, -9.925274968694582E+00, 0.0),
                                                                    vec3(1.018892127682802E-03*365, 2.980370221614675E-03*365 ,0.0 ),
                                                                    0.515e-4 );
        CelestialBody &pluto = fullBodySystem.createCelestialBody( vec3(9.420766235048019, -3.181847836470213E+01, 0.0),
                                                                   vec3(3.082778705023476E-03*365, 2.516987371233560E-04*365 ,0.0 ),
                                                                   0.655e-8 );

        vector<CelestialBody> &bodies = fullBodySystem.bodies();


        for(int i = 0; i < bodies.size(); i++)
        {CelestialBody &body = bodies[i];}

        ofstream ofile;
        ofile.open("FullSolarsystem");
        Euler integrateVerlet(dt);
        for(int timestep = 0; timestep< NumTimeSteps; timestep++)
        {
            //cout << mercury.position << endl;
            integrateVerlet.integrateOneStep(fullBodySystem);

           ofile << mercury.position.x() << " " << mercury.position.y() << " ";
           ofile << venus.position.x() << " " << venus.position.y() << " ";
           ofile << earth.position.x() << " " << earth.position.y() << " ";
           ofile << mars.position.x() << " " << mars.position.y() << " ";
           ofile << jupiter.position.x() << " " << jupiter.position.y() << " ";
           ofile << saturn.position.x() << " " << saturn.position.y() << " ";
           ofile << uranus.position.x() << " " << uranus.position.y() << " ";
           ofile << neptun.position.x() << " " << neptun.position.y() << " ";
           ofile << pluto.position.x() << " " << pluto.position.y() << endl;
            //fullBodySystem.writeToFile("penis.xyz");
        }
        ofile.close();

}
void FullSolarSystem::MercurPerihelion()
{
    double T = 100.0;
    double dt = 5e-6;
    int Numsteps = T/dt;

    solarsystem mercurPerihelion;
    CelestialBody &sun = mercurPerihelion.createCelestialBody(vec3(0,0,0), vec3(0,0,0), 1);
    CelestialBody &mercur = mercurPerihelion.createCelestialBody(vec3(0.3075, 0.0, 0.0),
                                                                 vec3( 0.0, 12.44,0.0 ),
                                                                 1.2e-7);

    vector<CelestialBody> &bodies = mercurPerihelion.bodies();
    for(int i = 0; i < bodies.size(); i++)
    {CelestialBody &body = bodies[i];}

    // Set some helper variables before we start the time integration.
    double thetaPrevious 	= 0;	// The perihelion angle of the previous time step.
    double theta 		= 0;	// The perihelion angle of the current time step.

    double rPreviousPrevious 	= 0;	// Mercury-Sun-distance two times steps ago.
    double rPrevious   	 	= 0;	// Mercury-Sun-distance of the previous time step.
    double r 		 	= 0;	// Mercury-Sun-distance of the current time step.



    verlet integrateVerlet(dt);
    ofstream ofile;
    ofile.open("PerihelionAngleRelativistic");
    for(int timestep = 0; timestep<Numsteps; timestep++)
    {
        integrateVerlet.integrateOneStepRelativisticForce(mercurPerihelion);
        double x = mercur.position.x()- sun.position.x();
        double y = mercur.position.y()- sun.position.y();

        double thetaCurrent = atan2(y, x);
        double rCurrent = (mercur.position - sun.position).length();

        // Check if the *previous* time step was a minimum for the Mercury-Sun distance. I.e. check
        // if the previous distance is smaller than the current one *and* the previous previous one
        if ( rCurrent > rPrevious && rPrevious < rPreviousPrevious )
        {
            //cout << "Perihelion angle: " << thetaPrevious << endl;
            double arcseconds = 206265*thetaPrevious;
            ofile << setprecision(20) << arcseconds << endl;
            //ofile << setprecision(20) << thetaPrevious << endl;

        }
        // Update the helper variables (current, previous, previousPrevious).
            rPreviousPrevious = rPrevious;
            rPrevious = rCurrent;
            thetaPrevious = thetaCurrent;
    }
    ofile.close();

}
