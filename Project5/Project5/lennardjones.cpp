#include "lennardjones.h"
#include "system.h"

double LennardJones::potentialEnergy() const
{
    return m_potentialEnergy;
}

void LennardJones::setPotentialEnergy(double potentialEnergy)
{
    m_potentialEnergy = potentialEnergy;
}

double LennardJones::sigma() const
{
    return m_sigma;
}

void LennardJones::setSigma(double sigma)
{
    m_sigma = sigma;
}

double LennardJones::epsilon() const
{
    return m_epsilon;
}

void LennardJones::setEpsilon(double epsilon)
{
    m_epsilon = epsilon;
}

void LennardJones::calculateForces(System &system)
{
    m_potentialEnergy = 0; // Remember to compute this in the loop
    double sigma6 = m_sigma*m_sigma*m_sigma*m_sigma*m_sigma*m_sigma;
    double sigma12 = sigma6*sigma6;
    //We need this to compute the real distance between particles, because of boundary conditions
    double halfLatticeSize = system.systemSize()[0]*0.5;
    vec3 systemSize = system.systemSize();
    std::vector<Atom*> &atoms = system.atoms();
    int numberOfAtoms = system.atoms().size();
    int epsilon24 = 24*m_epsilon;
    int epsilon4 = 4*m_epsilon;

    //for(int atomi = 0; atomi = system.systemSize(); atomi++){
    //    for(int atomi = 0; atomi = system.systemSize(); atomi++){


    for(int i=0; i<numberOfAtoms; i++) {
        Atom *atomi = atoms[i];
        for(int j=i+1; j<numberOfAtoms; j++) {
            Atom *atomj = atoms[j];
            //if (atomi == atomj) continue;
            // Implementing boundary conditions
            /* Because of the boundary conditions, the real distance
             * between to particles when they are in different ends of
             * the box(lattice) is smaller. Imagine an identical box next
             * to the original an measure the distance between particle
             * B and A through the boundary of box1 and into box 2
             */
            double dx = atomj->position.x() - atomi->position.x();
            if (dx > halfLatticeSize) { dx -= systemSize[0]; }
            else if (dx <= -halfLatticeSize) { dx += systemSize[0]; }
            double dy = atomj->position.y() - atomi->position.y();
            if (dy > halfLatticeSize) { dy -= systemSize[1]; }
            else if (dy <= -halfLatticeSize) { dy += systemSize[1]; }
            double dz = atomj->position.z() - atomi->position.z();
            if (dz > halfLatticeSize) { dz -= systemSize[2]; }
            else if (dz <= -halfLatticeSize) { dz += systemSize[2]; }
            double dr2 = dx*dx + dy*dy + dz*dz;

            // Calculating force
            double oneOverDr2 = 1.0/dr2;
            double oneOverDr6 = oneOverDr2*oneOverDr2*oneOverDr2;
            double force = epsilon24*oneOverDr6*oneOverDr2*(2*sigma12*oneOverDr6 - sigma6);
            double force_x = force*dx;
            double force_y = force*dy;
            double force_z = force*dz;

            m_potentialEnergy += epsilon4*oneOverDr6*(sigma12*oneOverDr6-sigma6);

            // Adding force to atom i
            atomi->force[0] -= force_x;
            atomi->force[1] -= force_y;
            atomi->force[2] -= force_z;

            // Adding force to atom j
            atomj->force[0] += force_x;
            atomj->force[1] += force_y;
            atomj->force[2] += force_z;
        }
    }
    setPotentialEnergy(m_potentialEnergy);

}

