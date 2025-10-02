#include <stdio.h>
#include "Body.h"
#include <stdlib.h>
#include "BodyArray.h"


void simulationLoop(BodyArrayPtr list);

int main(){

    BodyArrayPtr list = arrayInit(4);
    addBody(list, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.989e30);        // Sun 
    addBody(list, 2.279e11, 0.0, 0.0, 0.0, 24077.0, 0.0, 0.0, 0.0, 0.0, 6.39e23); // Mars
    simulationLoop(list);
    return 0;  
}




void simulationLoop(BodyArrayPtr list){
    double deltatime = 1; 
    for(int step = 0; step < 50000; step++){    // Outer: time steps
        for(int i=0; i<list->size; i++){        // Middle: bodies
            resetAcceleration(&list->data[i]);
            
            for(int j=0; j<list->size; j++){     // Inner: force calculation
                if(i != j){
                    updateAcceleration(&list->data[i], &list->data[j], deltatime);
                }
            }
            updateVelocity(&list->data[i], deltatime);
            updatePosition(&list->data[i], deltatime);
            printBody(list->data[i]);
        }
    }
    

}