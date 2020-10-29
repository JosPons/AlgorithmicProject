#include <stdlib.h>
#include <math.h>
#include "hashTable.h"
#include "utilityFunctions.h"


//**************************************************************************************//
void createHashFunctionFamilyH(hashFunctionsFamilyH_t *hashFunctionsFamilyH, uint32_t dimension, uint32_t k, uint32_t W)
{
  hashFunctionsFamilyH->hashFunctionsArray = calloc(k, sizeof(randomSNumbers_t));
  if (hashFunctionsFamilyH->hashFunctionsArray == NULL)
  {
    perror("Error, couldn't allocate memory for \"hashFunctionsArray\" array");
    exit(1);
  }
  for (uint32_t i = 0; i < k; i++)
  {
    hashFunctionsFamilyH->hashFunctionsArray[i].randomSArray = calloc(dimension, sizeof(double));
    if (hashFunctionsFamilyH->hashFunctionsArray[i].randomSArray == NULL)
    {
      perror("Error, couldn't allocate memory for \"randomSArray\" array");
      exit(1);
    }
  }
  hashFunctionsFamilyH->vectorDimension = dimension;
  hashFunctionsFamilyH->k = k;
  hashFunctionsFamilyH->W = W;
  hashFunctionsFamilyH->M = 32 / k;
  hashFunctionsFamilyH->m = (32 / k) - 1;
}

void destroyHashFunctionFamilyH(hashFunctionsFamilyH_t hashFunctionsFamilyH)
{
  for (uint32_t i = 0; i < hashFunctionsFamilyH.k; i++)
    free(hashFunctionsFamilyH.hashFunctionsArray[i].randomSArray);
  free(hashFunctionsFamilyH.hashFunctionsArray);
}
//**************************************************************************************//

//**************************************************************************************//
void generateSi(hashFunctionsFamilyH_t hashFunctionsFamilyH)
{
  uint32_t W = hashFunctionsFamilyH.W;

  for (uint32_t k = 0; k < hashFunctionsFamilyH.k; k++)
    for (uint32_t d = 0; d < hashFunctionsFamilyH.vectorDimension; d++)
      hashFunctionsFamilyH.hashFunctionsArray[k].randomSArray[d] = W * ((double) rand() / RAND_MAX);

}

void calculateAi(hashFunctionsFamilyH_t hashFunctionsFamilyH, uint32_t k,
                 const coordType *imageVector, int32_t *imageVectorA)
{
  uint32_t W = hashFunctionsFamilyH.W;
  double numeratorDiff;

  for (uint32_t d = 0; d < hashFunctionsFamilyH.vectorDimension; d++)
  {
    numeratorDiff = imageVector[d] - hashFunctionsFamilyH.hashFunctionsArray[k].randomSArray[d];
    imageVectorA[d] = floor(numeratorDiff / W);
  }
}

uint32_t calculateHi(hashFunctionsFamilyH_t hashFunctionsFamilyH, const coordType *imageVector)
{
  int32_t imageVectorA[hashFunctionsFamilyH.vectorDimension];
  uint32_t hashResultsArray[hashFunctionsFamilyH.k];
  int32_t tempResult1 = 0;
  int32_t tempResult2 = 0;
  int32_t tempResult3 = 0;
  int32_t hashResult = 0;
  uint32_t M = hashFunctionsFamilyH.M;
  uint32_t m = hashFunctionsFamilyH.m;

  for (uint32_t k = 0; k < hashFunctionsFamilyH.k; k++)
  {
    calculateAi(hashFunctionsFamilyH, k, imageVector, imageVectorA);
    for (uint32_t d = 0; d < hashFunctionsFamilyH.vectorDimension; d++)
    {
      //First calculate the m's
      tempResult1 = fastModularPow(m, d, M);
      //Secondly calculate the Ai's
      tempResult2 = mod(imageVectorA[hashFunctionsFamilyH.vectorDimension - 1 - d], M);
      tempResult3 = tempResult1 * tempResult2;
      hashResult = hashResult + tempResult3;
    }
    hashResultsArray[k] = mod(hashResult, M);
    hashResult = 0;
  }
  return concatenateIntegers(hashResultsArray, hashFunctionsFamilyH.k, M);
}

uint32_t hashFunctionG(hashFunctionsFamilyH_t hashFunctionsFamilyH, const coordType *imageVector)
{
  uint32_t hashResult;

  hashResult = calculateHi(hashFunctionsFamilyH, imageVector);
  return hashResult;
}
//**************************************************************************************//