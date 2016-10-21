#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H

#include "celestialbody.h"
#include <vector>
#include <string>
#include <fstream>
using namespace std;


class solarsystem
{
public:
    solarsystem();
    CelestialBody& createCelestialBody(vec3 position, vec3 velocity, double mass);

    void CalculateForcesandEnergy();
    void CalculateForcesandEnergyRelativistic();
    int numberofbodies() const;

    double totalEnergy() const;
    double potentialEnergy() const;
    double kineticEnergy() const;
    void writeToFile(string filename);
    void PrintToFile(string filename, CelestialBody &body);

    vec3 angularmomentum();
    vector<CelestialBody> &bodies();

private:
    vector<CelestialBody> m_bodies;
    vec3 m_angularMomentum;
    ofstream m_file;
    double m_kineticEnergy;
    double m_potentialEnergy;
    double G;


};

#endif // SOLARSYSTEM_H
