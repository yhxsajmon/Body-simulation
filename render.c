#include <SDL3/SDL.h>
#include "Body.h"
#include <math.h>
#include <stdio.h>

// Screen dimensions and scaling
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define SCALE_FACTOR 1e-9

// Forward declaration
void plotCirclePoints(SDL_Renderer* renderer, int cx, int cy, int x, int y);

void drawBody(BodyPtr body, SDL_Renderer* renderer){
    // Scale world coordinates to screen coordinates
    int cx = (int)((body->position[0] * SCALE_FACTOR) + SCREEN_WIDTH/2);
    int cy = (int)((body->position[1] * SCALE_FACTOR) + SCREEN_HEIGHT/2);
    
    // FIXED: Scale the radius properly for screen display
    double world_radius = calculateRadius(*body);
    int r = (int)(world_radius * SCALE_FACTOR);  // Apply same scaling as positions
    
    // DEBUG: Print both world and screen radius
    printf("Body at world pos: (%.2e, %.2e), world radius: %.2e, screen pos: (%d, %d), screen radius: %d\n", 
           body->position[0], body->position[1], world_radius, cx, cy, r);
    
    // Ensure minimum visible radius
    if (r < 2) r = 2;
    
    // Cap maximum radius to prevent overflow
    if (r > 100) r = 100;  // Limit to reasonable screen size
    
    // Check if on screen
    if (cx < -r || cx > SCREEN_WIDTH + r || cy < -r || cy > SCREEN_HEIGHT + r) {
        printf("Body off screen!\n");
        return;
    }
    
    // Set color based on mass (Sun = yellow, planets = red)
    if (body->mass > 1e29) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Yellow for Sun
    } else {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red for planets
    }
    
    // For very small radii, just draw a filled circle manually
    if (r <= 5) {
        for(int i = -r; i <= r; i++) {
            for(int j = -r; j <= r; j++) {
                if(i*i + j*j <= r*r) {
                    SDL_RenderPoint(renderer, cx + i, cy + j);
                }
            }
        }
        return;
    }
    
    // Bresenham's circle algorithm
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;
    
    plotCirclePoints(renderer, cx, cy, x, y);
    
    while (x <= y) {
        if (d <= 0) {
            d = d + 4 * x + 6;
        } else {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
        plotCirclePoints(renderer, cx, cy, x, y);
    }
}

// Helper function to plot 8 symmetric points
void plotCirclePoints(SDL_Renderer* renderer, int cx, int cy, int x, int y) {
    SDL_RenderPoint(renderer, cx + x, cy + y);
    SDL_RenderPoint(renderer, cx - x, cy + y);
    SDL_RenderPoint(renderer, cx + x, cy - y);
    SDL_RenderPoint(renderer, cx - x, cy - y);
    SDL_RenderPoint(renderer, cx + y, cy + x);
    SDL_RenderPoint(renderer, cx - y, cy + x);
    SDL_RenderPoint(renderer, cx + y, cy - x);
    SDL_RenderPoint(renderer, cx - y, cy - x);

}