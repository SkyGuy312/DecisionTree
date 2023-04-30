#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Vector/vector.h"
#include "../Dataframes/dataframes.h"
#include "node.h"
#include "../Libs/lib.h"

Node* newNode(DoubleDataframe* df) {
  Node* node = (Node*) malloc(sizeof(Node));
  node->child_left = NULL;
  node->child_right = NULL;
  //IntVector* labelsBefore = (IntVector*)df->vec[df->rows-1];
  node->dataframe = CopyDoubleDataframe(df);

  node->best_split = getBestSplit(df);

  return node;
}

double getGiniImpurity(int* arr, int len)
{
  if (len == 0) return 0.0;

  else
  {
    double giniSum = 0.0;

    /* Step 1: count the number of samples for each class */

    const int max = get_max(arr, len);

    // declare number of counts for each class variable, initialize it with zeros
    int counts[max+1];
    memset(counts, 0, sizeof(counts));

    // count the instances of each class
    for (int i = 0; i < len; i++)
    {
      counts[arr[i]] += 1;
    }


    /* Step 2: Calculate the Gini Impurity*/
    for(int j = 0; j <= max; j++) {

        double pClass = (double)counts[j] / (double)len;
        giniSum += pClass * (1 - pClass);

    }

    return giniSum;
  }
}

static IntVector** getSplitTargets(DoubleDataframe* dataP, int feature, double category)
{
  // create right and left side indexs that would correspond for future left and right child nodes
  IntVector* trueSplit = create_int_vector();
  IntVector* falseSplit = create_int_vector();

  int idx = 0;

  // get split indexes
  for (int i = 0; i < dataP->rows; i++)
  {
    double val = GetElementDoubleDataframe(dataP, feature, idx);

    if (val >= category)
    {
      push_back_intVec(trueSplit, idx);
    }
    else
    {
      push_back_intVec(falseSplit, idx);
    }

    idx++;

  }

  // create vectors with values of associated outcomes
  IntVector* allLabels = double_to_int_vector (dataP->vec[dataP->rows-1]);

  IntVector* trueLabels = create_int_vector();
  IntVector* falseLabels = create_int_vector();
/*
  for (int i = 0; i < falseSplit->len; i++)
  {
    push_back_intVec(falseLabels, allLabels->arr[falseSplit->arr[i]]);
  }

  for (int i = 0; i < trueSplit->len; i++)
  {
    push_back_intVec(trueLabels, allLabels->arr[trueSplit->arr[i]]);
  }
*/

  IntVector** retData = malloc (2 * sizeof(IntVector*));

  retData[0] = CopyIntVector (trueSplit);
  retData[1] = CopyIntVector (falseSplit);

/* /////////////////////////////////////DEBUGGING CODE\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/


  // printf("Length of trueSplits here is: %d, its values are:\n",retData[0]->len);
  // for (int i = 0 ; i < retData[0]->len; i++)
  // {
  //   // printf("%d, ", retData[0]->arr[i]);
  //   printf ("%d, ", allLabels->arr[retData[0]->arr[i]]);
  // }
  // printf("\n");

  // printf("Length of falseSplits here is: %d, its values are:\n",retData[0]->len);
  // for (int i = 0; i < retData[1]->len; i++)
  // {
  //   // printf("%d, ", retData[1]->arr[i]);
  //   printf ("%d, ", allLabels->arr[retData[1]->arr[i]]);
  // }
  // printf("\n");

  // printf("Length of allLabels here is: %d, its values are:\n",allLabels->len);
  // for (int i = 0; i < allLabels->len; i++)
  // {
  //   printf("%d, ", allLabels->arr[i]);
  // }
  // printf("\n");

/* /////////////////////////////////////DEBUGGING CODE\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

  return retData;
}

best_split_return getBestSplit(DoubleDataframe* dataP)
{
  // get the gini impurity before split:
  DoubleDataframe* dataPCpy = CopyDoubleDataframe(dataP);

  IntVector* labelsBefore = double_to_int_vector (dataPCpy->vec[dataPCpy->rows-1]);

  const double giniBefore = getGiniImpurity(labelsBefore->arr,labelsBefore->len);

  int features = dataPCpy->rows - 1;

  best_split_return bestChoice;
  bestChoice.resultant_gini = giniBefore;
  bestChoice.feature = 0;
  bestChoice.category = 0.0;

  // find the best feature for splitting criteria
  for (int feature = 0; feature < features; feature++)
  {
    if (feature % 10 == 0)
    {
      printf ("feature %d of 59\n", feature);
    }
    // get the number of categories in that feature
    Vector* featureVec = CopyVector (dataPCpy->vec[feature]);

/* /////////////////////////////////////DEBUGGING CODE\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

    // printf ("featureVec length here is %d, it's values are:", featureVec->len);
    // for (int i = 0; i < featureVec->len; i++)
    // {
    //   printf("%f, ", featureVec->arr[i]);
    // }
    // printf("\n");

/* /////////////////////////////////////DEBUGGING CODE\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

    if (feature == 6)
    {
      printf("BP\n");
    }

    // Calculate Gini Impurity for splitting every feature by every category
    for (int i = 0; i < featureVec->len; i++)
    {
      // get Splits
      IntVector** split = getSplitTargets(dataPCpy, feature, featureVec->arr[i]);

      // now we got split targets, calculate Gini impurity for both splits
      // create 2 temp nodes of these splits

      IntVector* trueSplitLabels = create_int_vector();
      IntVector* falseSplitLabels = create_int_vector();

/* /////////////////////////////////////DEBUGGING CODE\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

      // printf("Split[0] length is %d, values are:\n", split[0]->len);
      // for (int i = 0; i < split[0]->len; i++)
      // {
      //   printf("%d, ", split[0]->arr[i]);
      // }
      // printf("\n");

      // printf("Split[1] length is %d, values are:\n", split[1]->len);
      // for (int i = 0; i < split[1]->len; i++)
      // {
      //   printf("%d, ", split[1]->arr[i]);
      // }
      // printf("\n");

/* /////////////////////////////////////DEBUGGING CODE\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

      for (int i = 0; i < split[0]->len; i++)
      {
        push_back_intVec(trueSplitLabels, labelsBefore->arr[split[0]->arr[i]]);
      }
      for (int i = 0; i < split[1]->len; i++)
      {
        push_back_intVec(falseSplitLabels, labelsBefore->arr[split[1]->arr[i]]);
      }

      //calculate weighted Gini for splits that evaluate the given category to true
      double trueGini = getGiniImpurity (trueSplitLabels->arr, trueSplitLabels->len);
      double weightedTrueGini = (trueGini *  trueSplitLabels->len) / labelsBefore->len;

      double falseGini = getGiniImpurity (falseSplitLabels->arr, falseSplitLabels->len);
      double weightedFalseGini = (falseGini * falseSplitLabels->len) / labelsBefore->len;

      double weightedGiniSum = weightedTrueGini + weightedFalseGini;

      if (weightedGiniSum < bestChoice.resultant_gini)
      { //splitting here improves on current gini impurity
        bestChoice.resultant_gini = weightedGiniSum;
        bestChoice.feature = feature;
        bestChoice.category = featureVec->arr[i];
      }

      delete_int_vector(trueSplitLabels);
      delete_int_vector(falseSplitLabels);
      delete_int_vector (split[0]);
      delete_int_vector (split[1]);
      split = NULL;

    }
  }
  return bestChoice;
}
