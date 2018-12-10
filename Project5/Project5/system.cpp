#include "system.h"
#include "velocityverlet.h"
#include "lennardjones.h"
#include "statisticssampler.h"
#include "unitconverter.h"
#include "math/random.h"

System::System()
{

}

System::~System()
{
    for(Atom *atom : m_atoms) {
        delete atom;
    }
    m_atoms.clear();
}

void System::applyPeriodicBoundaryConditions() {
    // Read here: http://en.wikipedia.org/wiki/Periodic_boundary_conditions#Practical_implementation:_continuity_and_the_minimum_image_convention
    //m_systemSize is set in createFCCLattice
    for(Atom *atom : m_atoms) {
        if (atom->position[0] > m_systemSize[0]) {
            atom->position[0] -= m_systemSize[0];
            atom->initialPosition()[0] -= m_systemSize[0];

        }
        else if (atom->position[0] < 0) {
            atom->position[0] += m_systemSize[0];
            atom->initialPosition()[0] += m_systemSize[0];

        }
        if (atom->position[1] > m_systemSize[1]) {
            atom->position[1] -= m_systemSize[1];
            atom->initialPosition()[1] -= m_systemSize[1];

        }
        else if (atom->position[1] < 0) {
            atom->position[1] += m_systemSize[1];
            atom->initialPosition()[1] += m_systemSize[1];

        }
        if (atom->position[2] > m_systemSize[2]) {
            atom->position[2] -= m_systemSize[2];
            atom->initialPosition()[2] -= m_systemSize[2];

        }
        else if (atom->position[2] < 0) {
            atom->position[2] += m_systemSize[2];
            atom->initialPosition()[2] += m_systemSize[2];

        }
    }
}



void System::removeTotalMomentum() {
    // Find the total momentum and remove momentum equally on each atom so the total momentum becomes zero.
    //We find the total momentum of the system, and devide by nr of atoms and then remove this from every atom
    //to make the net total momentum zero
    vec3 TotalVelocity(0,0,0);

       for(Atom *atom : m_atoms) {
           TotalVelocity += atom->velocity;

       }

       TotalVelocity /= m_atoms.size();


       for(Atom *atom : m_atoms) {
           atom->velocity -= TotalVelocity;
       }

}

void System::createFCCLattice(int numberOfUnitCellsEachDimension, double latticeConstant, double temperature, double mass) {

    for(int i=0; i<numberOfUnitCellsEachDimension; i++) {
        for(int j=0; j<numberOfUnitCellsEachDimension; j++) {
            for(int k=0; k<numberOfUnitCellsEachDimension; k++) {
                // Setting 4 atoms at points in the lattice
                Atom * atom1 = new Atom(mass);
                atom1->position.set(i*latticeConstant,j*latticeConstant,k*latticeConstant);
                atom1->resetVelocityMaxwellian(temperature);
                atom1->setInitialPosition(atom1->position);
                m_atoms.push_back(atom1);

                Atom * atom2 = new Atom(mass);
                atom2->position.set(i*latticeConstant+latticeConstant/2.,j*latticeConstant+latticeConstant/2.,k*latticeConstant);
                atom2->resetVelocityMaxwellian(temperature);
                atom2->setInitialPosition(atom2->position);
                m_atoms.push_back(atom2);

                Atom * atom3 = new Atom(mass);
                atom3->position.set(i*latticeConstant,j*latticeConstant+latticeConstant/2.,k*latticeConstant+latticeConstant/2.);
                atom3->resetVelocityMaxwellian(temperature);
                atom3->setInitialPosition(atom3->position);
                m_atoms.push_back(atom3);

                Atom * atom4 = new Atom(mass);
                atom4->position.set(i*latticeConstant+latticeConstant/2.,j*latticeConstant,k*latticeConstant+latticeConstant/2.);
                atom4->resetVelocityMaxwellian(temperature);
                atom4->setInitialPosition(atom4->position);
                m_atoms.push_back(atom4);
            }
        }
    }
    setSystemSize(vec3(numberOfUnitCellsEachDimension*latticeConstant, numberOfUnitCellsEachDimension*latticeConstant, numberOfUnitCellsEachDimension*latticeConstant));

}

void System::calculateForces() {
    for(Atom *atom : m_atoms) {
        atom->resetForce();
    }
    m_potential.calculateForces(*this); // this is a pointer, *this is a reference to this object
}

void System::step(double dt) {

    m_integrator.integrate(*this, dt);
    m_steps++;
    m_time += dt;
}
