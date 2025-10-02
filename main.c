#include <stdio.h>
#include "Body.h"
#include <stdlib.h>
#include "BodyArray.h"


int main(){

    BodyArrayPtr list = arrayInit(4);
    
    list->data[0] = addBody(list,0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.989e30);
    list->data[1] = addBody(list,2.279e11, 0.0, 0.0, 0.0, 24077.0, 0.0, 0.0, 0.0, 0.0, 6.39e23);
    
    //BodyPtr earth = createBody(1.496e11, 0.0, 0.0, 0.0, 29780.0, 0.0, 0.0, 0.0, 0.0, 5.972e24);




    
    // Simulation code would go here
    simulationLoop(list);

    // Clean up

    
    return 0;  // Added missing return statement
}




void simulationLoop(BodyArrayPtr list){
    double deltatime = 1; // 1 day in seconds
    for(int i=0; i<list->capacity;i++){
        for(int step = 0; step < 50000; step++) // 365 days
        {
            resetAcceleration(list->data[i]);
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
    

}