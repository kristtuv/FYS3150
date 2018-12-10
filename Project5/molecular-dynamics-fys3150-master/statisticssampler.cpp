#include "system.h"
#include "statisticssampler.h"
#include "lennardjones.h"
#include "unitconverter.h"

using std::ofstream; using std::cout; using std::endl;

StatisticsSampler::StatisticsSampler(){

}

void StatisticsSampler::saveToFile(System &system)
{

    // Save the statistical properties for each timestep for plotting etc.
    // First, open the file if it's not open already
    if(!m_file.good()) {
        m_file.open(m_filename, ofstream::out);
        cout << "Now opening : " << m_filename << endl;
        m_file << setiosflags(ios::showpoint);
        m_file << setw(20) << "Time ";
        m_file << setw(20) << "Temperature";
        m_file << setw(20) << "KineticEnergy";
        m_file << setw(20) << "PotentialEnergy";
        m_file << setw(20) << "TotalEnergy";
        //m_file << setw(20) << "Density";
        m_file << setw(20) << "DiffusionConstant";
        m_file << setw(20) << "RSquared" << "\n";

        // If it's still not open, something bad happened...
        if(!m_file.good()) {
            cout << "Error, could not open statistics.txt" << endl;
            exit(1);
        }
    }
    m_file << setiosflags(ios::showpoint) ;
    m_file << setprecision(10);
    m_file << setw(20) << UnitConverter::timeToSI(system.time());
    m_file << setw(20) << UnitConverter::temperatureToSI( temperature());
    m_file << setw(20) << UnitConverter::energyToEv(kineticEnergy());
    m_file << setw(20) << UnitConverter::energyToEv(potentialEnergy());
    m_file << setw(20) << UnitConverter::energyToEv(totalEnergy());
    //m_file << setw(20) << m_density;
    m_file << setw(20) << diffusionConstant();
    m_file << setw(20) << m_rSquared << "\n";
   // m_file << sampleTemperature(system);
   // m_file << sampleKineticEnergy(system);
   // m_file << samplePotentialEnergy(system);
   // m_file << totalEnergy();
   // m_file << sampleDensity(system);
   // m_file << sampleDiffusionConstant(system) << endl;
}
void StatisticsSampler::close() {
    if(m_file.is_open()) {
        m_file.close();
    }
    cout << "Now Closing : " << m_filename << endl;
}

void StatisticsSampler::sample(System &system)
{
    // Here you should measure different kinds of statistical properties and save it to a file.

    sampleKineticEnergy(system);
    samplePotentialEnergy(system);
    sampleTemperature(system);
    //sampleDensity(system);
    sampleDiffusionConstant(system);
    //saveToFile(system);
}

void StatisticsSampler::sampleKineticEnergy(System &system)
{
    m_kineticEnergy = 0; // Remember to reset the value from the previous timestep
    for(Atom *atom : system.atoms()) {
        m_kineticEnergy += 0.5*atom->mass()*atom->velocity.lengthSquared();

    }
}

void StatisticsSampler::samplePotentialEnergy(System &system)
{
    m_potentialEnergy = system.potential().potentialEnergy();
}

void StatisticsSampler::sampleTemperature(System &system)
{
    m_temperature = 2.0/3.0 * m_kineticEnergy/system.atoms().size();
    // Hint: reuse the kinetic energy that we already calculated
}

void StatisticsSampler::sampleDensity(System &system)
{
       m_density = (system.atoms().size()*system.atoms()[0]->mass())/system.volume();
     //m_density = system.volume()/(system.atoms().size()*system.atoms()[0]->mass());
}

void StatisticsSampler::sampleDiffusionConstant(System &system)
{

    m_rSquared = 0; // Mean Square Distance
    m_diffusionConstant = 0;
    for(Atom *atom : system.atoms()) {
        //m_rSquared += (atom->position.length() - atom->initialPosition().length())*
        //              (atom->position.length() - atom->initialPosition().length());
        m_rSquared += (atom->position - atom->initialPosition()).lengthSquared();

    }
    m_rSquared /= system.atoms().size();
    m_diffusionConstant = m_rSquared/6.0/system.time();


}
