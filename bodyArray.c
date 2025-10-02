#include "BodyArray.h"
#include "Body.h"

BodyArrayPtr arrayInit(size_t initial_capacity) {  
    BodyArrayPtr list = malloc(sizeof(BodyArray));
    if (!list) return NULL;
    
    // Fix: capacity is allocated space, size is current count
    list->capacity = initial_capacity;
    list->size = 0;  // Start with 0 elements

    list->data = malloc(sizeof(Body) * list->capacity);
    if (!list->data) {
        free(list);
        return NULL;
    }
    
    return list;           
}


//Probably correct revision
void addBody(BodyArrayPtr list, double x, double y, double z, double vx, double vy, double vz, double ax,double ay,double az,double mass) {
    if (!list) return;
    

    if(list->size == list->capacity) {
        size_t new_capacity = list->capacity == 0 ? 1 : list->capacity * 2;  // Handle 0 capacity
        Body* new_data = realloc(list->data, sizeof(Body) * new_capacity);
        if (!new_data) return;
        list->data = new_data;
        list->capacity = new_capacity;
    }

    Body newBody = createBody(x,y,z,vx,vy,vz,ax,ay,az,mass);

    list->data[list->size] = newBody;
    list->size++;
}

void removeBodyAt(BodyArrayPtr list, size_t index) {
    if (!list || index >= list->size) return;
    

    // Shift elements left to fill the gap
    for (size_t i = index; i < list->size - 1; i++) {
        list->data[i] = list->data[i + 1];
    }
    list->size--;  // Fix: decrease size, not capacity
}

Body* getBodyAt(BodyArrayPtr list, size_t index) {
    if (!list || index >= list->size) return NULL;
    return &list->data[index];
}

void destroyArray(BodyArrayPtr list) {
    if (!list) return;
    free(list->data);
    free(list);
}


