#include "DecisionTree.h"
#include "../CSVReader/csvreader.h"
#include <stdio.h>
#include <stdlib.h>

static DoubleDataframe** SplitData (DoubleDataframe* dataBefore, int feature, double category)
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
    
    // initialize present data dataframe
    DoubleDataframe* presData = CreateDoubleDataframe(0,numRows);

    // initialize absent data dataframe
    DoubleDataframe* absData = CreateDoubleDataframe(0,numRows);

    // initialize buffer vector
    Vector* rowBuffer = create_vector();

/* /////////////////////////////////////DEBUGGING CODE\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

    // printf ("PresSplit len is: %d", presSplit->len);
    // for (int i = 0; i < presSplit->len; i++)
    // {
    //     printf ("%d, ", presSplit->arr[i]);
    // }
    // printf ("\n");

    // printf ("absSplit length is: %d, values are:\n", absSplit->len);
    // for (int i = 0; i < absSplit->len; i++)
    // {
    //     printf ("%d, ", absSplit->arr[i]);
    // }
    // printf ("\n");

/* /////////////////////////////////////DEBUGGING CODE\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

    // fill the dataframe of present data

    DoubleDataframe* dataBeforeCpy = CopyDoubleDataframe (dataBefore);
    dataBeforeCpy = TransposeDoubleDataframe (dataBeforeCpy);

    printf ("Assigning split nodes:\nRight Node:\n");
    for (int i = 0 ; i < presSplit->len; i++)
    {   
        printf ("%d of %d\n",i+1, presSplit->len);
        rowBuffer = CopyVector (dataBeforeCpy->vec[presSplit->arr[i]]);
        push_back_row (presData, rowBuffer);
    }

    // fill the dataframe of absent data
    printf ("Assigning split nodes:\nLeft Node:\n");
    for (int i = 0 ; i < absSplit->len; i++)
    {   
        printf ("%d of %d\n",i+1, absSplit->len);
        rowBuffer = CopyVector (dataBeforeCpy->vec[absSplit->arr[i]]);
        push_back_row (absData, rowBuffer);
    }

    presData = TransposeDoubleDataframe(presData);
    absData = TransposeDoubleDataframe(absData);

    

    DoubleDataframe** returnObj = malloc (2 * sizeof(DoubleDataframe*));
    returnObj[0] = CopyDoubleDataframe(presData);
    returnObj[1] = CopyDoubleDataframe(absData);

/* /////////////////////////////////////DEBUGGING CODE\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

    // printf ("length of presData is %d, its values are:\n", returnObj[0]->rows);
    // for (int i = 0; i < returnObj[0]->rows; i++)
    // {
    //     for (int j = 0; j < returnObj[0]->vec[i]->len; i++)
    //     {
    //         printf ("%lf, ",returnObj[0]->vec[i]->arr[j]);
    //     }
    //     printf("\n");
    // }

/* /////////////////////////////////////DEBUGGING CODE\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/


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

        DoubleDataframe** childrensData = malloc (2 * sizeof(DoubleDataframe*));
        childrensData = SplitData (nodeP->dataframe, nodeP->best_split.feature, nodeP->best_split.category);

        // if there is data after split, build a child node:
        if (childrensData[0]->cols > MIN_SAMPLES)
        {
            Node* newRightChild = newNode(childrensData[0]);
            newRightChild->depth++;
            nodeP->child_right = newRightChild;
            ConstructTree (nodeP->child_right);
        }

        if (childrensData[1]->cols > MIN_SAMPLES)
        {
            Node* newLeftChild = newNode(childrensData[1]);
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