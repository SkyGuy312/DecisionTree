#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
    double* arr;
    int len;
} Vector;

typedef struct {
    int* arr;
    int len;
} IntVector;

Vector* create_vector();
void push_back(Vector* vec, double value);
void pop_back(Vector* vec);
void delete_vector(Vector* vec);
void print_vector(const Vector* vec);

IntVector* create_int_vector();
void push_back_intVec(IntVector* vec, int value);
void pop_back_intVec(IntVector* vec);
void delete_int_vector(IntVector* vec);

Vector* CopyVector(const Vector* vec);
IntVector* CopyIntVector(const IntVector* vec);

void push_back_vector(Vector* vec, Vector* new_vec);
void print_int_vector(IntVector* vec);

IntVector* double_to_int_vector(Vector* double_vec);

void clean(Vector* vec);

#endif
