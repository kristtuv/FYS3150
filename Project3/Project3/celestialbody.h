#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H
#include "vec3.h"

class CelestialBody
{
public:
    vec3 position;
    vec3 velocity;
    vec3 force;

    double mass;

    CelestialBody(vec3 position, vec3 velocity, double mass); //everything needed to describe a planet

    void resetforce();



};

#endif // CELESTIALBODY_H
