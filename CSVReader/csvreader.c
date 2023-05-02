#include "../Dataframes/dataframes.h"
#include "../Vector/vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 4069

DoubleDataframe* read(char* trainPath) {
    FILE* fp = fopen(trainPath, "r");
    if (fp == NULL) {
        printf("Failed to open file %s\n", trainPath);
        return NULL;
    }

    // Count number of rows and columns
    int rows = 0, cols = 0;
    char line[MAX_LINE_LENGTH];
    fgets(line, MAX_LINE_LENGTH, fp);
    char* token = strtok(line, ",");
    while (token != NULL) {
        cols++;
        token = strtok(NULL, ",");
    }
    rows++;
    while (fgets(line, MAX_LINE_LENGTH, fp)) {
        rows++;
    }
    rewind(fp);

    // Allocate memory for the DoubleDataframe
    DoubleDataframe* dataframe = CreateDoubleDataframe(rows, cols);

    // Read data into DoubleDataframe
    int row = 0, col = 0;
    // fgets(line, MAX_LINE_LENGTH, fp);
    while (fgets(line, MAX_LINE_LENGTH, fp)) {
        // if (row == 1014) 
        // {
        //     printf ("BP\n");
        // }
        col = 0;
        token = strtok(line, ",");
        // if (token == '\r' || token == '\n')
        // {
        //     printf ("BP\n");
        // }

        while (token != NULL) {
            int num = atof(token);
            // if (num == 48 && row == 1014)
            // {
            //     printf("BP\n");
            // }
            SetElementDoubleDataframe(dataframe, row, col, atof(token));
            col++;
            token = strtok(NULL, ",");
        }
        row++;
    }

    // PrintDoubleDataframe (dataframe);
    // printf("\n\n\n");
    // dataframe = TransposeDoubleDataframe(dataframe);
    // PrintDoubleDataframe (dataframe);
    

    // Close file and return dataframe
    fclose(fp);
    // PrintDoubleDataframe(dataframe);

    return dataframe;
}