#include "euler.h"
#include "solarsystem.h"

Euler::Euler(double dt) :
    m_dt(dt)
{

}

void Euler::integrateOneStep(solarsystem &system)
{
    system.CalculateForcesandEnergy();

    for(CelestialBody &body : system.bodies()) {
        body.position += body.velocity*m_dt;
        body.velocity += body.force / body.mass * m_dt;
    }
}
