#include "lib.h"

int get_max(int *arr, int len) {
    int max = *arr; // Initialize max to the first element of the row
    
    int i;
    for (i = 1; i < len; i++) {
        if (*(arr + i) > max) { // Compare each element with the current max
            max = *(arr + i); // Update max if necessary
        }
    }
    
    return max;
}

float get_max_float(float *arr, int len) {
    float max = *arr; // Initialize max to the first element of the row
    
    int i;
    for (i = 1; i < len; i++) {
        if (*(arr + i) > max) { // Compare each element with the current max
            max = *(arr + i); // Update max if necessary
        }
    }
    
    return max;
}