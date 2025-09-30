#ifndef BODYARRAY_H
#define BODYARRAY_H


#include <stdio.h>
#include <stdlib.h>
#include "Body.h"

typedef struct BodyArray {
    size_t size;      // Fixed: use standard size_t
    size_t capacity;  // Fixed: use standard size_t
    Body *data;
} BodyArray, *BodyArrayPtr;

// Initialize array with given capacity
BodyArrayPtr arrayInit(size_t capacity);

// Add body at end of array
void addBody(BodyArrayPtr list, Body body);

// Remove body at specific index
void removeBodyAt(BodyArrayPtr list, size_t index);

// Get body at index
Body* getBodyAt(BodyArrayPtr list, size_t index);

// Clean up array
void destroyArray(BodyArrayPtr list);

#endif
