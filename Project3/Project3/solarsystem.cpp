#include "solarsystem.h"
#include <cmath>
#include <iostream>
using namespace std;


solarsystem::solarsystem(){
    double m_kineticEnergy(0);
    double m_potentialEnergy(0);


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
    m_angularMomentum.zeros();

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
            vec3 force = G * body1.mass * body2.mass/(dr*dr) * deltaRVector.normalized();
            body1.force -= force;
            body2.force += force;
        }



        m_kineticEnergy += 0.5*body1.mass*body1.velocity.lengthSquared();

    }
}

double solarsystem::totalEnergy() const
{ return m_kineticEnergy + m_potentialEnergy;}

double solarsystem::potentialEnergy() const
{return m_potentialEnergy;}
double solarsystem::kineticEnergy() const
{return m_kineticEnergy;}

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
        m_file << "1 " << body.position.x() << " " << body.position.y() << " " << body.position.z() << "\n";
    }
}

vec3 solarsystem::angularmomentum() const
{
    return m_angularMomentum;
}

vector<CelestialBody> &solarsystem::bodies()
{
    return m_bodies;
}
