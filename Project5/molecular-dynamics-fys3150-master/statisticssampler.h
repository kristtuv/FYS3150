#ifndef STATISTICSSAMPLER_H
#define STATISTICSSAMPLER_H
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

class System; // Promise the compiler that this is a class even though we haven't included system.h here

class StatisticsSampler
{
private:
    std::ofstream m_file;

    double m_kineticEnergy = 0;
    double m_potentialEnergy = 0;
    double m_temperature = 0;
    double m_density = 0;
    double m_diffusionConstant = 0;
    double m_rSquared = 0;
    string m_filename = "penis";


public:
    StatisticsSampler();
    void saveToFile(System &system);
    void sample(System &system);
    void close();

    void sampleKineticEnergy(System &system);
    void samplePotentialEnergy(System &system);
    void sampleTemperature(System &system);
    void sampleDensity(System &system);
    void sampleDiffusionConstant(System & system);

    double kineticEnergy() { return m_kineticEnergy; }
    double potentialEnergy() { return m_potentialEnergy; }
    double totalEnergy() { return m_kineticEnergy+m_potentialEnergy; }
    double temperature() { return m_temperature; }
    double density() { return m_density; }
    double diffusionConstant() { return m_diffusionConstant; }
    double rSquared() {return m_rSquared; }



    void setfilename(string filename){ m_filename = filename;}
};
#endif
