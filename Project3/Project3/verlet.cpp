#include "verlet.h"
#include "solarsystem.h"
#include <iostream>
using namespace std;

verlet::verlet(double dt):
    m_dt(dt)

{
}

void verlet::integrateOneStep(class solarsystem &system)
{

    system.CalculateForcesandEnergy();


    for(CelestialBody &body : system.bodies())
    {
        body.position += m_dt*body.velocity + m_dt*m_dt/2 *body.force/body.mass;
        vec3 acceleration = body.force/body.mass;
        system.CalculateForcesandEnergy();
        //cout << acceleration << endl;
        //cout << body.force/body.mass << endl;

        body.velocity += m_dt/2*(body.force/body.mass + acceleration);


    }
}
void verlet::integrateOneStepRelativisticForce(class solarsystem &system)
{

    system.CalculateForcesandEnergyRelativistic();


    for(CelestialBody &body : system.bodies())
    {
        body.position += m_dt*body.velocity + m_dt*m_dt/2 *body.force/body.mass;
        vec3 acceleration = body.force/body.mass;
        system.CalculateForcesandEnergyRelativistic();

        body.velocity += m_dt/2*(body.force/body.mass + acceleration);


    }
}
