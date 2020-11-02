#ifndef ALGORITHMICPROJECT_SEARCHALGORITHMS_H
#define ALGORITHMICPROJECT_SEARCHALGORITHMS_H

#include <stdint.h>
#include "datasetStructure.h"
#include "hashTable.h"


typedef struct resultNN_t
{
  uint32_t inputVectorId;
  uint32_t vectorDistance;
} resultNN_t;

typedef struct resultANN_t
{
  resultNN_t *resultArray;
  resultNN_t *resultRangeArray;
  uint32_t sizeResultArray;
  uint32_t sizeResultRangeArray;
  uint32_t elementsResultArray;
  uint32_t elementsResultRangeArray;
} resultANN_t;

typedef struct resultTime_t
{
  int32_t timeNN;
  int32_t timeANN;
} resultTime_t;

void findTrueNN(imageDataset_t, const coordType *, resultNN_t *, resultTime_t *);
void findApproximateNNLSH(hashTable_t *, uint32_t, const coordType *, resultANN_t *, resultTime_t *, double);
void findApproximateNNCube(hashTable_t, uint32_t, uint32_t, const coordType *,
                           resultANN_t *, resultTime_t *, double, FILE *);
void printResults(resultNN_t *, resultANN_t, resultTime_t, uint32_t, uint32_t, uint8_t, FILE *);
#endif //ALGORITHMICPROJECT_SEARCHALGORITHMS_H
