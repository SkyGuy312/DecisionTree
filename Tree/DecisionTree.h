#ifndef TREE_H
#define TREE_H

#include "../Node/node.h"

#define MIN_SAMPLES 0

typedef struct TwoDataFrame
{
    DoubleDataframe pres;       //samples that realizes split criterion
    DoubleDataframe abs;        //samples that do not relize split criterion
}TwoDataFrame;

typedef struct DecisionTree
{
    Node* rootP;
}DecisionTree;

// function to initialize model with trainset
DecisionTree* CreateDecisionTree (char* trainPath);

// function to traverse the tree
void TraverseTree();

// function to split data
static TwoDataFrame SplitData (DoubleDataframe* dataBefore, int feature, double category);

// function to construct more nodes
static void ConstructTree (Node* nodeP);

// function to infer prediction
IntVector Predict (char* TestPath);
static int RecusivelyPredict (Node* nodeP, IntVector samples);

// function to delete children of specific node
void DeleteChildren (Node* nodeP);

#endif