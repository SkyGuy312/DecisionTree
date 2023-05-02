#ifndef DATAFRAMES_H
#define DATAFRAMES_H

#include "../Vector/vector.h"

typedef struct {
    Vector** vec;
    int cols;
    int rows;
} DoubleDataframe;

DoubleDataframe* CreateDoubleDataframe(int rows, int cols);
DoubleDataframe* TransposeDoubleDataframe(DoubleDataframe* df);
void DeleteDoubleDataframe(DoubleDataframe* df);
double GetElementDoubleDataframe(DoubleDataframe* df, int row, int col);
void SetElementDoubleDataframe(DoubleDataframe* df, int row, int col, double value);
DoubleDataframe* CopyDoubleDataframe(DoubleDataframe* source);
void PrintDoubleDataframe(DoubleDataframe* df);
DoubleDataframe* TransposeDataFrame(DoubleDataframe* df);


typedef struct {
    IntVector** vec;
    int cols;
    int rows;
} IntDataframe;

IntDataframe* CreateIntDataframe(int rows, int cols);
IntDataframe* TransposeIntDataframe(IntDataframe* df);
void DeleteIntDataframe(IntDataframe* df);
int GetElementIntDataframe(IntDataframe* df, int row, int col);
void SetElementIntDataframe(IntDataframe* df, int row, int col, int value);
IntDataframe* CopyIntDataframe(IntDataframe* source);
void PrintIntDataframe(IntDataframe* df);

void push_back_row(DoubleDataframe* df, Vector* row_vec);
#endif /* DATAFRAMES_H */
