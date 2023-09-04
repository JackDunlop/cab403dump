#include <stdio.h>
#include <stdlib.h>
#include "dbl_vector.h"


void dv_init( dbl_vector_t* vec ) {
    vec->capacity = DV_INITIAL_CAPACITY;
    vec->size = 0;
    vec->data = (double*)malloc(vec->capacity * sizeof(double));
}


void dv_ensure_capacity(dbl_vector_t* vec, size_t new_size) {
    size_t old_capacity = vec->capacity; // WHERE old_capacity is the previous value of vec->capacity
    size_t old_size = vec->size; // AND old_size == previous value of vec->size
    double* old_data = vec->data; // AND old_data == previous value of vec->data
    if (new_size <= old_capacity) { // if new size <= old_capacity
        vec->capacity = old_capacity; // vec->capacity == old_capacity
        vec->data = old_data; // vec->data == old_data
    } else {
        size_t new_capacity = (size_t)(old_capacity * DV_GROWTH_FACTOR); vec->capacity == new_capacity 
        new_capacity = new_size;
        double* new_data = (double*)realloc(old_data, new_capacity * sizeof(double)); 
        vec->capacity = new_capacity;
        vec->data = new_data;
    }
    vec->size = old_size;
}

void dv_destroy( dbl_vector_t* vec ) {
    // INSERT SOLUTION HERE
}

void dv_copy( dbl_vector_t* vec, dbl_vector_t* dest ) {
    // INSERT SOLUTION HERE
}

void dv_clear( dbl_vector_t* vec ) {
    // INSERT SOLUTION HERE
}

void dv_push( dbl_vector_t* vec, double new_item ) {
    // INSERT SOLUTION HERE
}

void dv_pop( dbl_vector_t* vec ) {
    // INSERT SOLUTION HERE
}

double dv_last( dbl_vector_t* vec ) {
    double result = NAN;
    // INSERT SOLUTION HERE
    return result;
}

void dv_insert_at( dbl_vector_t* vec, size_t pos, double new_item ) {
    // INSERT SOLUTION HERE
}

void dv_remove_at( dbl_vector_t* vec, size_t pos ) {
    // INSERT SOLUTION HERE
}

void dv_foreach( dbl_vector_t* vec, void (*callback)(double, void*), void* info ) {
    // INSERT SOLUTION HERE
}

