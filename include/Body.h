#ifndef BODY_H
#define BODY_H

// Define Vector3 as an array of 3 doubles for x, y, z coordinates
typedef double Vector3[3];

typedef struct Body
{
    double position[3];
    double velocity[3];
    double acceleration[3];
    double mass;
    double density;
} Body, *BodyPtr;

//TODO: Remove the Implementation of BodyPtr to static Body
Body createBody(double x, double y, double z, double vx, double vy, double vz, double ax,double ay,double az,double mass,double density);
//void destroyBody(BodyPtr body);
void printBody(Body body);
double bodyDistance(Body a, Body b);
double calculateForce(Body a, Body b);  
double calculateRadius(Body body);
void updateAcceleration(BodyPtr a, BodyPtr b, double timestep);
void updateVelocity(BodyPtr body, double timeStep);
void updatePosition(BodyPtr body, double timeStep);
void resetAcceleration(BodyPtr body);  




#endif // BODY_H
