#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

Vector* create_vector() {
    Vector* vec = malloc(sizeof(Vector));
    vec->len = 0;
    vec->arr = (double*)malloc(0 * sizeof(double));
    return vec;
}

void push_back(Vector* vec, double value) {
    vec->len++;
    vec->arr = (double*)realloc(vec->arr, vec->len * sizeof(double));
    vec->arr[vec->len - 1] = value;
}

void pop_back(Vector* vec) {
    if (vec->len == 0) {
        return;
    }
    vec->len--;
    vec->arr = realloc(vec->arr, vec->len * sizeof(double));
}

void delete_vector(Vector* vec) {
    free(vec->arr);
    free(vec);
}

IntVector* create_int_vector()
{
    IntVector* vec = malloc(sizeof(IntVector));
    vec->arr = NULL;
    vec->len = 0;
    return vec;
}

void push_back_intVec(IntVector* vec, int value)
{
    vec->len++;
    vec->arr = realloc(vec->arr, vec->len * sizeof(int));
    vec->arr[vec->len - 1] = value;
}

void pop_back_intVec(IntVector* vec)
{
    if (vec->len == 0) {
        return;
    }
    vec->len--;
    vec->arr = realloc(vec->arr, vec->len * sizeof(int));
}

void delete_int_vector(IntVector* vec)
{
    free(vec->arr);
    free(vec);
}

Vector* CopyVector(const Vector* vec) {
    Vector* new_vec = malloc(sizeof(Vector));
    new_vec->len = vec->len;
    new_vec->arr = malloc(new_vec->len * sizeof(double));
    for (int i = 0; i < new_vec->len; i++) {
        new_vec->arr[i] = vec->arr[i];
    }
    return new_vec;
}

IntVector* CopyIntVector(const IntVector* vec) {
    IntVector* new_vec = malloc(sizeof(IntVector));
    new_vec->len = vec->len;
    new_vec->arr = malloc(new_vec->len * sizeof(int));
    for (int i = 0; i < new_vec->len; i++) {
        new_vec->arr[i] = vec->arr[i];
    }
    return new_vec;
}

void push_back_vector(Vector* vec, Vector* new_vec)
{
    int i;
    for (i = 0; i < new_vec->len; i++) {
        push_back(vec, new_vec->arr[i]);
    }
}

void clean(Vector* vec) {
    vec->len = 0;
    free(vec->arr);
    vec->arr = (double*)calloc(vec->len, sizeof(double));
}

void print_vector(const Vector* vec) {
    for (int i = 0; i < vec->len; i++) {
        printf("%lf", vec->arr[i]);
        if (i != vec->len - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    printf("Vector of length %d: [", vec->len);
}

void print_int_vector(IntVector* vec) {
    printf("IntVector of length %d: [", vec->len);
    for (int i = 0; i < vec->len; i++) {
        printf("%d", vec->arr[i]);
        if (i != vec->len - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

IntVector* double_to_int_vector(Vector* double_vec) {
    IntVector* int_vec = create_int_vector();
    for (int i = 0; i < double_vec->len; i++) {
        int value = (int) double_vec->arr[i];
        push_back_intVec(int_vec, value);
    }
    return int_vec;
}

