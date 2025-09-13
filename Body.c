#include "Body.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Implementation of functions declared in Body.h would go here

// Function to initialize a body
BodyPtr createBody(double x, double y, double z, double vx, double vy, double vz, double ax,double ay,double az,double mass) {
    BodyPtr body = malloc(sizeof(Body));
    if (body == NULL) return NULL;  // Check malloc success
    
    body->position[0] = x; body->position[1] = y; body->position[2] = z;
    body->velocity[0] = vx; body->velocity[1] = vy; body->velocity[2] = vz;
    body->acceleration[0] = ax; body->acceleration[1] = ay; body->acceleration[2] = az;
    body->mass = mass;
    
    return body;
}

void destroyBody(BodyPtr body) {
    if (body != NULL) {
        free(body);
    }
}

void printBody(BodyPtr body) {
    if (body == NULL) {
        printf("Body is NULL\n");
        return;
    }
    printf("Position: (%.2e, %.2e, %.2e) m\n", 
           body->position[0], body->position[1], body->position[2]);
    printf("Velocity: (%.2f, %.2f, %.2f) m/s\n", 
           body->velocity[0], body->velocity[1], body->velocity[2]);
    printf("Mass: %.2e kg\n\n", body->mass);
}

double bodyDistance(BodyPtr a, BodyPtr b) {
    if (a == NULL || b == NULL) return -1.0;
    
    double dx = a->position[0] - b->position[0];
    double dy = a->position[1] - b->position[1];
    double dz = a->position[2] - b->position[2];
    
    double distance = sqrt(dx*dx + dy*dy + dz*dz);
    printf("Distance between bodies: %.2e meters\n", distance);
    return distance;
}

double calculateForce(BodyPtr a, BodyPtr b){
    double distance = bodyDistance(a,b);
    double G = 1.0;
    double force = (G*a->mass*b->mass)/pow(distance,2);
    return force;
}

void updateAcceleration(BodyPtr a, BodyPtr b, double timestep) {
    if (a == NULL || b == NULL) return;
    
    // Calculate distance and direction once
    double dx = b->position[0] - a->position[0];
    double dy = b->position[1] - a->position[1];
    double dz = b->position[2] - a->position[2];
    
    double distance = sqrt(dx*dx + dy*dy + dz*dz);
    if (distance <= 0) return;
    
    // Calculate force
    double G = 1.0;
    double force = (G * a->mass * b->mass) / (distance * distance);
    
    // Normalize direction vector
    double unit_dx = dx / distance;
    double unit_dy = dy / distance;
    double unit_dz = dz / distance;
    
    // Calculate accelerations for both bodies
    double accel_a = force / a->mass;
    double accel_b = force / b->mass;
    
    // Apply acceleration to both bodies (mutual attraction)
    a->acceleration[0] += accel_a * unit_dx;
    a->acceleration[1] += accel_a * unit_dy;
    a->acceleration[2] += accel_a * unit_dz;
    
    b->acceleration[0] -= accel_b * unit_dx;  // Opposite direction
    b->acceleration[1] -= accel_b * unit_dy;
    b->acceleration[2] -= accel_b * unit_dz;
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

