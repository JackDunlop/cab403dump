#include <stdio.h>
#include <stdlib.h>
#include "dbl_vector.h"

void dv_init( dbl_vector_t* vec ) {
    vec->capacity = DV_INITIAL_CAPACITY;
    vec->size = 0;
    vec->data = (double*)malloc(vec->capacity * sizeof(double));
}

void dv_ensure_capacity(dbl_vector_t* vec, size_t new_size) {
    size_t old_capacity = vec->capacity;
    size_t old_size = vec->size;
    double* old_data = vec->data;
    if (new_size <= old_capacity) {
        vec->capacity = old_capacity;
        vec->data = old_data;
    } else {
        size_t new_capacity = (size_t)(old_capacity * DV_GROWTH_FACTOR);
        if (new_capacity < new_size) {
            new_capacity = new_size;
        }
        double* new_data = (double*)realloc(old_data, new_capacity * sizeof(double));
        vec->capacity = new_capacity;
        vec->data = new_data;
    }
    vec->size = old_size;
}

void dv_destroy( dbl_vector_t* vec ) {
    vec->capacity = 0;
    vec->size = 0;
    free(vec->data);
}


void dv_copy( dbl_vector_t* vec, dbl_vector_t* dest ) {
    if(vec != dest)
    {
        dest->size = vec->size;
        dv_ensure_capacity(dest, vec->size);
        for(int i = 0; i < vec->size; i++)
        {
            dest->data[i] = vec->data[i];
        }
    }
    else
    {
        return 0; // probably should fix
    }

}

void dv_clear( dbl_vector_t* vec ) {
    vec->size = 0;
}

void dv_push( dbl_vector_t* vec, double new_item ) {
    size_t old_size = vec->size;
    double* old_data = vec->data;
    vec->size = old_size + 1;
    dv_ensure_capacity(vec, vec->size);
    for(int i = 0; i < old_size; i++){
        vec->data[i] = old_data[i];
    }
    vec->data[old_size] = new_item;
}

void dv_pop( dbl_vector_t* vec ) {
   size_t old_capacity = vec->capacity;
   size_t old_size = vec->size;
   double* old_data = vec->data;
   vec->capacity = old_capacity;
   vec->data = old_data;
   if(old_size > 0)
   {
    vec->size = old_size - 1;
    for(int i = 0; i < old_size - 1; i++ )
        vec->data[i] = old_data[i];
   }
   else
   {
    vec->size = 0;
   }
}

double dv_last( dbl_vector_t* vec ) {
    double result = NAN;
    size_t old_capacity = vec->capacity;
    size_t old_size = vec->size;
    double* old_data = vec->data;

    vec->size = old_size;
    vec->capacity = old_capacity;
    vec->data = old_data;

    for(int i = 0; i < vec->size; i++)
    {
        vec->data[i] = old_data[i];
    }
    if(vec->size > 0){
        return vec->data[vec->size - 1];
    }
    else
    {
        return result;
    }

    return result;
}


void dv_insert_at( dbl_vector_t* vec, size_t pos, double new_item ) {
    size_t old_size = vec->size;
    double* old_data = vec->data;
    size_t loc = (pos > old_size) ? old_size : pos;

    vec->size = old_size + 1;
    dv_ensure_capacity(vec,old_size+1);
    for(int i = 0; i < loc; i++){
        vec->data[i] = old_data[i];

    }
      for (int i = old_size; i > loc; i--) {
        vec->data[i] = old_data[i - 1];
    }

    vec->data[loc] = new_item;
   
    
}

void dv_remove_at(dbl_vector_t* vec, size_t pos) {
    size_t old_size = vec->size;
    if (pos >= old_size) {
        return; 
    }
    double* old_data = vec->data;
    size_t loc = (pos > old_size) ? old_size : pos;
       for(int i = 0; i < loc; i++){

        vec->data[i] = old_data[i];

    }
    for (size_t i = loc; i < old_size - 1; i++) {
        
        vec->data[i] = old_data[i + 1];
    }

    vec->size = old_size - 1;
}

void dv_foreach( dbl_vector_t* vec, void (*callback)(double, void*), void* info ) {
    size_t old_size = vec->size;
    size_t old_capacity = vec->capacity;
    double* old_data = vec->data;

    vec->capacity = old_capacity;
    vec->size = old_size;
    vec->data = old_data;

    for(int i = 0; i < vec->size; i++)
    { 
        callback(vec->data[i], info); 
    }

    old_size = vec->size;
    old_capacity = vec->capacity;
    old_data = vec->data;
}
