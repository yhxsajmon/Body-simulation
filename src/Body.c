#include "Body.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifndef M_PI
#   define M_PI 3.1415926535897932384626433832
#endif
//Remove existance of BodyPtr

// Function to initialize a body
Body createBody(double x, double y, double z, double vx, double vy, double vz, double ax,double ay,double az,double mass, double density) {
    Body body;
    
    body.position[0] = x; body.position[1] = y; body.position[2] = z;
    body.velocity[0] = vx; body.velocity[1] = vy; body.velocity[2] = vz;
    body.acceleration[0] = ax; body.acceleration[1] = ay; body.acceleration[2] = az;
    body.mass = mass;
    body.density = density;
    return body;
}



void printBody(Body body) {
    printf("Position: (%.2e, %.2e, %.2e) m\n", 
           body.position[0], body.position[1], body.position[2]);
    printf("Velocity: (%.2f, %.2f, %.2f) m/s\n", 
           body.velocity[0], body.velocity[1], body.velocity[2]);
    printf("Mass: %.2e kg\n\n", body.mass);
}

double bodyDistance(Body a, Body b) {
    
    double dx = a.position[0] - b.position[0];
    double dy = a.position[1] - b.position[1];
    double dz = a.position[2] - b.position[2];
    
    double distance = sqrt(dx*dx + dy*dy + dz*dz);
    printf("Distance between bodies: %.2e meters\n", distance);
    return distance;
}

double calculateForce(Body a, Body b){
    double distance = bodyDistance(a,b);
    double G = 6.674e-11;  // m³/(kg·s²)
    double force = (G*a.mass*b.mass)/pow(distance,2);
    return force;
}

double calculateRadius(Body body){
    double radius;
    double volume;

    // Check for invalid density to avoid division by zero
    if (body.density <= 0) {
        printf("ERROR: Invalid density %.2f for body with mass %.2e\n", body.density, body.mass);
        return 1.0; // Return default radius
    }

    volume = body.mass / body.density;
    radius = pow(3.0 * volume / (4.0 * M_PI), 1.0/3.0);
    
    // DEBUG: Print calculated values
    printf("Mass: %.2e, Density: %.2f, Volume: %.2e, Calculated radius: %.2e\n", 
           body.mass, body.density, volume, radius);

    return radius;
}

void updateAcceleration(BodyPtr a, BodyPtr b, double timestep) {
    
    // Calculate distance and direction once
    double dx = b->position[0] - a->position[0];
    double dy = b->position[1] - a->position[1];
    double dz = b->position[2] - a->position[2];
    
    double distance = sqrt(dx*dx + dy*dy + dz*dz);
    if (distance <= 0) return;
    
    // FIXED: Use correct gravitational constant
    double G = 6.674e-11;  // m³/(kg·s²)
    
    // Calculate gravitational acceleration on body 'a' due to body 'b'
    double acceleration_magnitude = (G * b->mass) / (distance * distance);
    
    // Normalize direction vector (from a to b)
    double unit_dx = dx / distance;
    double unit_dy = dy / distance;
    double unit_dz = dz / distance;
    
    // FIXED: Only apply acceleration to body 'a' (the simulation loop handles the reciprocal)
    a->acceleration[0] += acceleration_magnitude * unit_dx;
    a->acceleration[1] += acceleration_magnitude * unit_dy;
    a->acceleration[2] += acceleration_magnitude * unit_dz;
}

void updateVelocity(BodyPtr a,double deltatime){
    a->velocity[0] += a->acceleration[0]*deltatime;
    a->velocity[1] += a->acceleration[1]*deltatime;
    a->velocity[2] += a->acceleration[2]*deltatime;
}
void updatePosition(BodyPtr a,double deltatime){
    a->position[0] += a->velocity[0]*deltatime;
    a->position[1] += a->velocity[1]*deltatime;
    a->position[2] += a->velocity[2]*deltatime;
}

void resetAcceleration(BodyPtr a){
    a->acceleration[0] = 0;
    a->acceleration[1] = 0;
    a->acceleration[2] = 0;
}

