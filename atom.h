#ifndef ATOM_H
#define ATOM_H
#include "math/vec3.h"

class Atom
{
private:
    float m_mass;
    vec3 m_initialPosition;
public:
    vec3 position;
    vec3 velocity;
    vec3 force;


    Atom(double mass);
    void resetForce();
    void resetVelocityMaxwellian(double temperature);

    double mass() { return m_mass; }
    void setMass(double mass) { m_mass = mass; }
    vec3 initialPosition() { return m_initialPosition; }
    void setInitialPosition(vec3 initialPosition) { m_initialPosition = initialPosition; }
};
#endif
