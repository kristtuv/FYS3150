#include <iostream>
#include <stdlib.h>
#include <cmath>
#include "vec3.h"
#include "celestialbody.h"
#include "solarsystem.h"
#include "euler.h"
#include "verlet.h"
using namespace std;

int main()
{
    int numTimesteps = 10000;
    solarsystem Solar;
    CelestialBody &sun = Solar.createCelestialBody( vec3(0.0, 0.0, 0.0), vec3(0.0, 0.0 ,0.0 ), 1.0 );
    CelestialBody &earth = Solar.createCelestialBody(vec3(1.0, 0.0, 0.0), vec3(0.0, 2*M_PI, 0.0), 3e-6);

    vector<CelestialBody> &bodies = Solar.bodies();
    for(int i = 0; i < bodies.size(); i++)
    {
    CelestialBody &body = bodies[i];
    //cout << "Position of this object is " << body.position << endl;
    }
    double dt = 0.0001;

    /*

    Euler integrateEuler(dt);
    for(int timestep=0; timestep<numTimesteps; timestep++) {
       integrateEuler.integrateOneStep(Solar);
       cout << earth.position << endl;

       //Solar.writeToFile("positions.xyz");
   }
   */
    verlet integrateVerlet(dt);
    for(int timestep = 0; timestep< numTimesteps; timestep++)
    {
        integrateVerlet.integrateOneStep(Solar);
        cout << earth.position << endl;

    }

    cout << "I just created my first solar system that has " << Solar.bodies().size() << " objects." << endl;
    //cout << earth.force << endl;
    return 0;
};
