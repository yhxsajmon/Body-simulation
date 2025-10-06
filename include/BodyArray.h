#ifndef BODYARRAY_H
#define BODYARRAY_H


#include <stdio.h>
#include <stdlib.h>
#include "Body.h"

typedef struct BodyArray {
    size_t size;      
    size_t capacity; 
    Body *data;

} BodyArray, *BodyArrayPtr;

// Initialize array with given capacity
BodyArrayPtr arrayInit(size_t capacity);

// Add body at end of array
void addBody(BodyArrayPtr list,
        double x, double y, double z,
        double vx, double vy, double vz,
        double ax,double ay,double az,
        double mass,double density);

// Remove body at specific index
void removeBodyAt(BodyArrayPtr list, size_t index);

// Get body at index
Body* getBodyAt(BodyArrayPtr list, size_t index);

// Clean up array
void destroyArray(BodyArrayPtr list);

#endif
