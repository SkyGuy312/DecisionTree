#ifndef _NODE_H
#define _NODE_H

#include "../Dataframes/dataframes.h"

typedef struct best_split_return
{
    float resultant_gini;
    int feature;
    float category;
}best_split_return;

typedef struct Node {
  
  struct Node* child_left;
  struct Node* child_right;
  DoubleDataframe* dataframe;
  best_split_return best_split;
  int depth;

} Node;

Node* newNode(DoubleDataframe* df);

double getGiniImpurity(int* arr, int len);

static IntVector** getSplitTargets(DoubleDataframe* dataP, int feature, double category);

best_split_return getBestSplit(DoubleDataframe* dataP);

#endif