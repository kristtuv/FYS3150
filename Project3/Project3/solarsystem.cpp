#include "solarsystem.h"
#include <cmath>
#include <iostream>
#include <iomanip>
using namespace std;


solarsystem::solarsystem(){
    double m_kineticEnergy(0);
    double m_potentialEnergy(0);

    m_bodies.reserve(1000);


 }

CelestialBody& solarsystem::createCelestialBody(vec3 position, vec3 velocity, double mass){
    m_bodies.push_back(CelestialBody(position, velocity, mass ));
    return m_bodies.back();
}

int solarsystem::numberofbodies() const{
    return m_bodies.size();
}

void solarsystem::CalculateForcesandEnergy()
{
    m_kineticEnergy = 0;
    m_potentialEnergy = 0;

    for(CelestialBody &body : m_bodies) {
        // Reset forces on all bodies
        body.force.zeros();
    }

    for(int i=0; i<numberofbodies(); i++) {
        CelestialBody &body1 = m_bodies[i];

        for(int j=i+1; j<numberofbodies(); j++) {
            CelestialBody &body2 = m_bodies[j];
            vec3 deltaRVector = body1.position - body2.position;
            double dr = deltaRVector.length();

            // Calculate the force and potential energy here
            double G(4*M_PI*M_PI); //AU^3/(kg*yr^2)
            vec3 force = -G * body1.mass * body2.mass/(dr*dr) * deltaRVector.normalized();
            body1.force += force;
            body2.force -= force;

            m_potentialEnergy -= G*body1.mass*body2.mass/dr;

        }

        m_kineticEnergy += 0.5*body1.mass*body1.velocity.lengthSquared();

    }
}

void solarsystem::CalculateForcesandEnergyRelativistic()
{
    m_kineticEnergy = 0;
    m_potentialEnergy = 0;

    for(CelestialBody &body : m_bodies) {
        // Reset forces on all bodies
        body.force.zeros();
    }

    for(int i=0; i<numberofbodies(); i++) {
        CelestialBody &body1 = m_bodies[i];

        for(int j=i+1; j<numberofbodies(); j++) {
            CelestialBody &body2 = m_bodies[j];
            vec3 deltaRVector = body1.position - body2.position;
            double dr = deltaRVector.length();

            // Calculate the force and potential energy here
            double G(4*M_PI*M_PI); //AU^3/yr^2
            double c(63239.7263); //Speed of light in AU/yr

            vec3 force = G * body1.mass * body2.mass/(dr*dr)*deltaRVector.normalized();
            vec3 l     = deltaRVector.cross(body2.velocity - body1.velocity);
            double l2  = l.lengthSquared();

            double correction = (1 + (3*l2)/(dr*dr*c*c));
            force = force*correction;
            body1.force -= force;
            body2.force += force;

            m_potentialEnergy -= G*body1.mass*body2.mass/dr;
        }

        m_kineticEnergy += 0.5*body1.mass*body1.velocity.lengthSquared();

    }
}

double solarsystem::totalEnergy() const
{ return m_kineticEnergy + m_potentialEnergy;}

double solarsystem::potentialEnergy() const
{   //cout << m_potentialEnergy << " ";
    return m_potentialEnergy;}
double solarsystem::kineticEnergy() const
{   //cout << m_kineticEnergy << " ";
    return m_kineticEnergy;}

void solarsystem::writeToFile(string filename)
{
    if(!m_file.good()) {
        m_file.open(filename.c_str(), ofstream::out);
        if(!m_file.good()) {
            cout << "Error opening file " << filename << ". Aborting!" << endl;
            terminate();
        }
    }

    m_file << numberofbodies() << endl;
    m_file << "Comment line that needs to be here. Balle." << endl;
    for(CelestialBody &body : m_bodies) {
        m_file << "1" <<" "<< body.position.x() << " " << body.position.y() << " " << body.position.z() << "\n";
    }
}

void solarsystem::PrintToFile(string filename, CelestialBody &body)
{
    if(!m_file.good()) {
        m_file.open(filename.c_str(), ofstream::out);
        if(!m_file.good()) {
            cout << "Error opening file " << filename << ". Aborting!" << endl;
            terminate();
        }
    }
    m_file << body.position.x() << " " << body.position.y() << "\n";

}

vec3 solarsystem::angularmomentum()
{
    m_angularMomentum.zeros();
    CelestialBody &sun = m_bodies[0];
    for(int i=1; i<m_bodies.size(); i++) {
        CelestialBody &body = m_bodies[i];
        m_angularMomentum += body.mass*(body.position - sun.position).cross(body.velocity);
    }
    //cout << m_angularMomentum.length() << endl;
    return m_angularMomentum;
}

vector<CelestialBody> &solarsystem::bodies()
{
    return m_bodies;
}

vec3 solarsystem::FindMassCenter(){
    m_massCenter.zeros();
    M = 0.0;
    MR.zeros();

    for(int i = 0; i < m_bodies.size(); i++)
    {
    CelestialBody &body = m_bodies[i];
    M += body.mass;

    MR += body.mass*body.position;

    }
    m_massCenter = MR/M;
    return m_massCenter;

}

vec3 solarsystem::momentum()
{   m_momentum.zeros();
    //v_sun.zeros();

    for(int i = 0; i < m_bodies.size(); i ++)
    {
        CelestialBody &body = m_bodies[i];
        m_momentum += body.mass*body.velocity;
    }

    return -1*m_momentum;
}
