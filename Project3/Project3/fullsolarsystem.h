#ifndef FULLSOLARSYSTEM_H
#define FULLSOLARSYSTEM_H


class FullSolarSystem
{
public:
    int NumTimeSteps;
    double dt;
    FullSolarSystem();
    void TwoBodySystemEuler(int NumTimeSteps, double dt);
    void TwoBodySystemVerlet(int NumTimeSteps, double dt);
    void ThreeBodySystemVerlet(int NumTimeSteps, double dt);
    void ThreeBodySystemRealCenterOfMass(int NumTimeSteps, double dt);
    void FullBodySystemVerlet(int NumTimeSteps, double dt);
    void MercurPerihelion();
};


#endif // FULLSOLARSYSTEM_H
