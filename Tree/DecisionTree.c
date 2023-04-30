#include "DecisionTree.h"
#include "../CSVReader/csvreader.h"
#include <stdlib.h>

static TwoDataFrame SplitData (DoubleDataframe* dataBefore, int feature, double category)
{
    // vectors to indexes of values which either realize the category criterion or not
    IntVector* presSplit = create_int_vector();
    IntVector* absSplit = create_int_vector();

    /*vector of indexs of split data on both cases */

    int idx = 0;

    for (int i = 0; i < dataBefore->vec[feature]->len; i++)
    {
        double val = dataBefore->vec[feature]->arr[idx];

        if (val >= category)
        {
            push_back_intVec(presSplit,idx);
        }
        else
        {
            push_back_intVec(absSplit,idx);
        }

        idx++;
    }

    /* vector of data based on acquired indexes*/
    int numRows = dataBefore->rows;
    DoubleDataframe presData;

    Vector rowBuffer;
    rowBuffer.len = 0;
    rowBuffer.arr = (double*)malloc(0 * sizeof(double));



    for (int row = 0; row < numRows; row++)
    {
        for (int col = 0; col < presSplit->len; col++)
        {
            printf ("%lf\n", dataBefore->vec[row]->arr[col]);
            push_back(&rowBuffer, dataBefore->vec[row]->arr[col]);
        }

        push_back_row (&presData, &rowBuffer);
        clean(&rowBuffer);
    }

    DoubleDataframe absData;

    for (int row = 0; row < numRows; row++)
    {
        for (int col = 0; row < absSplit->len; col++)
        {
            push_back(&rowBuffer, dataBefore->vec[row]->arr[col]);
        }
        push_back_row(&absData, &rowBuffer);
        clean(&rowBuffer);
    }

    TwoDataFrame returnObj;

    returnObj.pres = presData;
    returnObj.abs = absData;

    return returnObj;
}

void ConstructTree (Node* nodeP)
{
    IntVector* labelsBefore = double_to_int_vector (nodeP->dataframe->vec[nodeP->dataframe->rows-1]);

    // check stopping critertia
    double giniBefore = getGiniImpurity(labelsBefore->arr, labelsBefore->len);

    printf ("Current depth: %d\n", nodeP->depth);

    if (nodeP->best_split.resultant_gini < giniBefore)
    {
        // recurse on children

        TwoDataFrame childrensData = SplitData (nodeP->dataframe, nodeP->best_split.feature, nodeP->best_split.category);

        // if there is data after split, build a child node:
        if (childrensData.pres.vec[0]->len > MIN_SAMPLES)
        {
            Node* newRightChild = newNode(&(childrensData.pres));
            newRightChild->depth++;
            nodeP->child_right = newRightChild;
            ConstructTree (nodeP->child_right);
        }

        if (childrensData.abs.vec[0]->len > MIN_SAMPLES)
        {
            Node* newLeftChild = newNode(&(childrensData.abs));
            newLeftChild->depth++;
            nodeP->child_left = newLeftChild;
            ConstructTree(nodeP->child_left);
        }
    }
}

void DeleteChildren (Node* nodeP)
{
    if (nodeP->child_right != (Node*)0)
    {
        DeleteChildren(nodeP->child_right);
    }

    if (nodeP->child_left != (Node*)0)
    {
        DeleteChildren(nodeP->child_left);
    }

    free(nodeP);
}

int RecusivelyPredict (Node* nodeP, IntVector samples)
{
    double sampleCategory = samples.arr[nodeP->best_split.feature];

    // initialize predict class
    int predictClass = -1;

    if ((nodeP->child_left == (Node*)0) && (nodeP->child_right == (Node*)0))
    {
        //this is a leaf node

        predictClass = nodeP->dataframe->vec[nodeP->dataframe->rows-1]->arr[0];
    }
    else if (sampleCategory >= nodeP->best_split.category)
    {
        // recurse on right child
        predictClass = RecusivelyPredict(nodeP->child_right, samples);
    }
    else
    {
        // recurse on left child
        predictClass = RecusivelyPredict(nodeP->child_left, samples);
    }
    return predictClass;
}

IntVector Predict (char* TestPath)
{

}

DecisionTree* CreateDecisionTree (char* trainPath)
{
    DoubleDataframe* trainingData = read(trainPath);
    printf("Data read successfully.\n\n");
    trainingData = TransposeDoubleDataframe(trainingData);
    Node* rootP = newNode (trainingData);
    rootP->depth = 0;
    ConstructTree (rootP);

    DecisionTree* model;
    model->rootP = rootP;

    return model;
    
}