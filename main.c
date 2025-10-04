#include <stdio.h>
#include "Body.h"
#include <stdlib.h>
#include "BodyArray.h"
#include <SDL3/SDL.h>
#include "render.h"
#include "math.h"

void simulationLoop(BodyArrayPtr list, SDL_Renderer* renderer);

int main(){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Body Simulation", 1920, 1080, SDL_WINDOW_BORDERLESS | SDL_WINDOW_FULLSCREEN);
    
    if (!window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }
    
    // Create renderer - this was missing!
    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        printf("Renderer creation failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    BodyArrayPtr list = arrayInit(4);
    // addBody(list, x, y, z, vx, vy, vz, ax, ay, az, mass, density)
    addBody(list, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.989e30, 1.41);        // Sun at origin
    
    // FIXED: Mars with proper orbital velocity
    // Position: (x=2.279e11, y=0, z=0) - Mars distance from Sun
    // Velocity: (vx=0, vy=24077, vz=0) - Only tangential velocity for circular orbit
    addBody(list, 2.279e11, 0.0, 0.0, 0.0, 24077.0, 0.0, 0.0, 0.0, 0.0, 6.39e23, 3.93); // Mars
    
    // DEBUG: Check what was actually stored
    printf("=== DEBUG: Bodies after creation ===\n");
    for(int i = 0; i < list->size; i++) {
        printf("Body %d:\n", i);
        printBody(list->data[i]);
        printf("Mass in array: %.2e, Density in array: %.2f\n", 
               list->data[i].mass, list->data[i].density);
    }
    printf("=====================================\n");
    
    simulationLoop(list, renderer);

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

void simulationLoop(BodyArrayPtr list, SDL_Renderer* renderer){
    double deltatime = 3600; // 1 minute instead of 1 hour
    // Even better: double deltatime = 10.0; // 10 seconds
    SDL_Event event;
    int running = 1;
    
    for(int step = 0; step < 50000 && running; step++){
        // Handle events
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_EVENT_QUIT || event.type == SDL_EVENT_KEY_DOWN) {
                running = 0;
            }
        }
        
        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        for(int i=0; i<list->size; i++){
            resetAcceleration(&list->data[i]);
            
            for(int j=0; j<list->size; j++){
                if(i != j){
                    // DEBUG: Print before and after acceleration update
                    if(step < 5 && i == 1) {  // Mars, first 5 steps only
                        printf("Before updateAcceleration: Mars accel = (%.2e, %.2e, %.2e)\n",
                               list->data[i].acceleration[0], list->data[i].acceleration[1], list->data[i].acceleration[2]);
                    }
                    
                    updateAcceleration(&list->data[i], &list->data[j], deltatime);
                    
                    if(step < 5 && i == 1) {
                        printf("After updateAcceleration: Mars accel = (%.2e, %.2e, %.2e)\n",
                               list->data[i].acceleration[0], list->data[i].acceleration[1], list->data[i].acceleration[2]);
                    }
                }
            }
            
            // DEBUG: Print before velocity/position updates
            if(step < 5 && i == 1) {
                printf("Before velocity update: Mars vel = (%.2e, %.2e, %.2e)\n",
                       list->data[i].velocity[0], list->data[i].velocity[1], list->data[i].velocity[2]);
            }
            
            updateVelocity(&list->data[i], deltatime);
            updatePosition(&list->data[i], deltatime);
            
            if(step < 5 && i == 1) {
                printf("After updates: Mars vel = (%.2e, %.2e, %.2e), pos = (%.2e, %.2e, %.2e)\n",
                       list->data[i].velocity[0], list->data[i].velocity[1], list->data[i].velocity[2],
                       list->data[i].position[0], list->data[i].position[1], list->data[i].position[2]);
                printf("---\n");
            }
            
            // FIXED: Draw every frame, not just every 100th
            drawBody(&list->data[i], renderer);
        }
        
        // FIXED: Present every frame
        SDL_RenderPresent(renderer);
        SDL_Delay(16); // ~60 FPS
        
        // Stop early if Mars goes too far
        if(fabs(list->data[1].position[0]) > 1e13) {  // 10 trillion meters
            printf("Mars escaped! Stopping simulation.\n");
            break;
        }
    }
}