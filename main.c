#include <stdio.h>
#include "Tree/DecisionTree.h"

int main ()
{
    Node* model = CreateDecisionTree("Dataset/Dataset.csv");
    printTree (model, 0);
}   