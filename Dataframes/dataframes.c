#include "dataframes.h"
#include <stdio.h>
#include <stdlib.h>

DoubleDataframe* CreateDoubleDataframe(int rows, int cols) {
    DoubleDataframe* df = malloc(sizeof(DoubleDataframe));
    df->vec = malloc(rows * sizeof(Vector*));
    for (int i = 0; i < rows; i++) {
        df->vec[i] = create_vector();
    }
    df->cols = cols;
    df->rows = rows;
    return df;
}

DoubleDataframe* TransposeDoubleDataframe(DoubleDataframe* df) {
    DoubleDataframe* tdf = CreateDoubleDataframe(df->cols, df->rows);
    for (int i = 0; i < df->rows; i++) {
        for (int j = 0; j < df->cols; j++) {
            push_back(tdf->vec[j], df->vec[i]->arr[j]);
        }
    }
    return tdf;
}

double GetElementDoubleDataframe(DoubleDataframe* df, int row, int col) {
    return df->vec[row]->arr[col];
}

void SetElementDoubleDataframe(DoubleDataframe* df, int row, int col, double value) {
    push_back(df->vec[row], value);
}

DoubleDataframe* CopyDoubleDataframe(DoubleDataframe* source) {
    DoubleDataframe* copy = CreateDoubleDataframe(source->rows, source->cols);
    for (int i = 0; i < source->rows; i++) {
        for (int j = 0; j < source->cols; j++) {
            double element = GetElementDoubleDataframe(source, i, j);
            SetElementDoubleDataframe(copy, i, j, element);
        }
    }
    return copy;
}

void DeleteDoubleDataframe(DoubleDataframe* df) {
    for (int i = 0; i < df->rows; i++) {
        delete_vector(df->vec[i]);
    }
    free(df->vec);
    free(df);
}

IntDataframe* CreateIntDataframe(int rows, int cols) {
    IntDataframe* df = malloc(sizeof(IntDataframe));
    df->vec = malloc(rows * sizeof(IntVector*));
    for (int i = 0; i < rows; i++) {
        df->vec[i] = create_int_vector();
    }
    df->cols = cols;
    df->rows = rows;
    return df;
}

IntDataframe* TransposeIntDataframe(IntDataframe* df) {
    IntDataframe* tdf = CreateIntDataframe(df->cols, df->rows);
    for (int i = 0; i < df->rows; i++) {
        for (int j = 0; j < df->cols; j++) {
            push_back_intVec(tdf->vec[j], df->vec[i]->arr[j]);
        }
    }
    return tdf;
}

int GetElementIntDataframe(IntDataframe* df, int row, int col) {
    return df->vec[row]->arr[col];
}

void SetElementIntDataframe(IntDataframe* df, int row, int col, int value) {
    df->vec[row]->arr[col] = value;
}

// CopyIntDataframe: creates a deep copy of a given IntDataframe
IntDataframe* CopyIntDataframe(IntDataframe* source) {
    IntDataframe* copy = CreateIntDataframe(source->rows, source->cols);
    for (int i = 0; i < source->rows; i++) {
        for (int j = 0; j < source->cols; j++) {
            int element = GetElementIntDataframe(source, i, j);
            SetElementIntDataframe(copy, i, j, element);
        }
    }
    return copy;
}

void DeleteIntDataframe(IntDataframe* df) {
    for (int i = 0; i < df->rows; i++) {
        delete_int_vector(df->vec[i]);
    }
    free(df->vec);
    free(df);
}

void push_back_row(DoubleDataframe* df, Vector* row_vec)
{
    int i;
    for (i = 0; i < df->cols; i++) {
        push_back_vector(df->vec[i], row_vec);
    }
    df->rows++;
}

void PrintDoubleDataframe(DoubleDataframe* df) {
    for (int i = 0; i < df->rows; i++) {
        for (int j = 0; j < df->cols; j++) {
            printf("%f ", df->vec[i]->arr[j]);
        }
        printf("\n");
    }
    printf("DoubleDataframe (rows: %d, cols: %d)\n", df->rows, df->cols);
}

void PrintIntDataframe(IntDataframe* df) {
    printf("IntDataframe (rows: %d, cols: %d)\n", df->rows, df->cols);
    for (int i = 0; i < df->rows; i++) {
        for (int j = 0; j < df->cols; j++) {
            printf("%d ", df->vec[i]->arr[j]);
        }
        printf("\n");
    }
}