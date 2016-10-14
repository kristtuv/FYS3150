#ifndef VERLET_H
#define VERLET_H


class verlet
{
public:
    double m_dt;
    verlet(double dt);
    void integrateOneStep(class solarsystem &system);
};

#endif // VERLET_H
