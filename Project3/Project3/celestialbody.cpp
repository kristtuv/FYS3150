#include "celestialbody.h"
#include "vec3.h"
#include <iostream>
using namespace std;
CelestialBody::CelestialBody(vec3 p, vec3 v, double m)
{   position = p;
    velocity = v;
    mass = m;


}

void CelestialBody::resetforce(){
    force.zeros(); //using zeros function from vec3
}
