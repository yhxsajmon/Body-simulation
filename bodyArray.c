#include "BodyArray.h"
#include "Body.h"

BodyArrayPtr arrayInit(size_t capacity) {  
    BodyArrayPtr list = malloc(sizeof(BodyArray));
    if (!list) return NULL;
    
    list->data = malloc(sizeof(Body) * capacity);
    if (!list->data) {
        free(list);
        return NULL;
    }
    
    list->size = 0;        
    list->capacity = capacity;
    return list;           
}

void addBody(BodyArrayPtr list, Body body) {
    if (!list) return;
    
    if(list->size == list->capacity) {

        list->capacity *= 2;
        Body* new_data = realloc(list->data, sizeof(Body) * list->capacity);
        if (!new_data) return; 
        list->data = new_data;
    }
    

    list->data[list->size] = body;
    list->size++;
}

void removeBodyAt(BodyArrayPtr list, size_t index) {
    if (!list || index >= list->size) return;
    
    // Shift elements left to fill the gap
    for (size_t i = index; i < list->size - 1; i++) {
        list->data[i] = list->data[i + 1];
    }
    list->size--;
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


