#include <stdio.h>
#include "Body.h"
#include <stdlib.h>

int main(){
    BodyPtr sun = createBody(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.989e30);
    //BodyPtr earth = createBody(1.496e11, 0.0, 0.0, 0.0, 29780.0, 0.0, 0.0, 0.0, 0.0, 5.972e24);
    BodyPtr mars = createBody(2.279e11, 0.0, 0.0, 0.0, 24077.0, 0.0, 0.0, 0.0, 0.0, 6.39e23);



    if (sun == NULL || mars == NULL) {
        return EXIT_FAILURE; // Exit if body creation failed
    }
    
    // Simulation code would go here
    simulationLoop(sun,mars);

    // Clean up
    destroyBody(sun);
    destroyBody(mars);
    
    return 0;  // Added missing return statement
}




void simulationLoop(BodyPtr a, BodyPtr b){
    double deltatime = 1; // 1 day in seconds
    
    for(int step = 0; step < 50000; step++) // 365 days
    {
        resetAcceleration(a);
        resetAcceleration(b);
        updateAcceleration(a,b,deltatime);
        updateVelocity(a,deltatime);
        updateVelocity(b,deltatime);
        updatePosition(a,deltatime);
        updatePosition(b,deltatime);
        printf("%s","Mars:");
        printBody(a);
    }
}