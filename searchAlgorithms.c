#include <string.h>
#include <stdint.h>
#include <sys/time.h>
#include "searchAlgorithms.h"
#include "utilityFunctions.h"


void findTrueNN(imageDataset_t inputImageDataset, const coordType *queryVector,
                resultNN_t *resultArray, resultTime_t *resultTime)
{
  uint32_t vectorDimension = inputImageDataset.vectorDimension;
  uint32_t vectorDistance;
  struct timeval start, end;

  coordType inputVector[vectorDimension];
  memset(inputVector, 0, sizeof(inputVector));
  gettimeofday(&start, NULL);
  for (uint32_t i = 0; i < inputImageDataset.numOfImages; i++)
  {
    memcpy(inputVector, &inputImageDataset.imagesVectors[i * vectorDimension], sizeof(inputVector));
    vectorDistance = calculateManhattanDistance(queryVector, inputVector, vectorDimension);
    resultArray[i].inputVectorId = i + 1;
    resultArray[i].vectorDistance = vectorDistance;
  }
  quickSort(resultArray, inputImageDataset.numOfImages);
  gettimeofday(&end, NULL);
  resultTime->timeNN = ((end.tv_sec - start.tv_sec) * 1000000) + (end.tv_usec - start.tv_usec);
}

void findApproximateNNLSH(hashTable_t *arrayOfHashTables, uint32_t L, const coordType *queryVector,
                          resultANN_t *resultANN, resultTime_t *resultTime, double R)
{
  uint32_t vectorDimension = arrayOfHashTables[0].hashFunctionsFamilyH.vectorDimension;
  uint32_t vectorDistance;
  uint32_t hashValue;
  uint32_t hashKey;
  bucket_t tempBucket;
  bucketElement_t tempElement;
  struct timeval start, end;
  struct timeval startRange, endRange;
  int32_t totalRangeTime = 0;

  createResultANN(resultANN, 16);
  gettimeofday(&start, NULL);
  for (uint32_t i = 0; i < L; i++)
  {
    hashValue = searchHashTableLSH(arrayOfHashTables[i], queryVector);
    hashKey = hashValue % arrayOfHashTables[i].hashTableSize;
    tempBucket = arrayOfHashTables[i].hashTableArray[hashKey];
    for (uint32_t b = 0; b < tempBucket.bucketElements; b++)
    {
      tempElement = tempBucket.bucketImageVectors[b];
      if (tempElement.hashKeyG == hashValue)
      {
        vectorDistance = calculateManhattanDistance(queryVector, tempElement.imageVector, vectorDimension);
        if (resultANN->elementsResultArray == resultANN->sizeResultArray)
          resizeArray(&resultANN->resultArray, &resultANN->sizeResultArray);
        resultANN->resultArray[resultANN->elementsResultArray].inputVectorId = tempElement.imageVectorId;
        resultANN->resultArray[resultANN->elementsResultArray].vectorDistance = vectorDistance;
        resultANN->elementsResultArray++;
        gettimeofday(&start, NULL);
        if (vectorDistance <= R)
        {
          if (resultANN->elementsResultRangeArray == resultANN->sizeResultRangeArray)
            resizeArray(&resultANN->resultRangeArray, &resultANN->sizeResultRangeArray);
          resultANN->resultRangeArray[resultANN->elementsResultRangeArray].inputVectorId = tempElement.imageVectorId;
          resultANN->resultRangeArray[resultANN->elementsResultRangeArray].vectorDistance = vectorDistance;
          resultANN->elementsResultRangeArray++;
        }
        gettimeofday(&end, NULL);
        totalRangeTime = totalRangeTime
                         + ((endRange.tv_sec - startRange.tv_sec) * 1000000)
                         + (endRange.tv_usec - startRange.tv_usec);
      }
    }
  }
  insertionSort(resultANN->resultArray, resultANN->elementsResultArray);
  resultANN->sizeResultArray = removeDuplicates(resultANN->resultArray, resultANN->elementsResultArray);
  quickSort(resultANN->resultArray, resultANN->sizeResultArray);
  gettimeofday(&end, NULL);
  resultTime->timeANN = ((end.tv_sec - start.tv_sec) * 1000000) + (end.tv_usec - start.tv_usec) - totalRangeTime;

  insertionSort(resultANN->resultRangeArray, resultANN->elementsResultRangeArray);
  resultANN->sizeResultRangeArray = removeDuplicates(resultANN->resultRangeArray, resultANN->elementsResultRangeArray);
  quickSort(resultANN->resultRangeArray, resultANN->sizeResultRangeArray);
}

void findApproximateNNCube(hashTable_t hashTable, uint32_t M, uint32_t probes, const coordType *queryVector,
                           resultANN_t *resultANN, resultTime_t *resultTime, double R, FILE *outputFd)
{
  uint32_t vectorDimension = hashTable.hashFunctionsFamilyH.vectorDimension;
  uint32_t vectorDistance;
  uint32_t curHammingDistance = 0;
  uint32_t hammingDistance = 0;
  uint32_t MsChecked = 0;
  uint32_t probesChecked = 0;
  uint32_t hashKey;
  uint8_t stopSearchFlag = 0;
  bucket_t tempBucket;
  bucketElement_t tempElement;
  struct timeval start, end;
  struct timeval startRange, endRange;
  int32_t totalRangeTime = 0;

  createResultANN(resultANN, 16);
  gettimeofday(&start, NULL);
  hashKey = searchHashTableCube(hashTable, queryVector);
  while (probesChecked != probes)
  {
    if (curHammingDistance == 0)
    {
      tempBucket = hashTable.hashTableArray[hashKey];
      for (uint32_t b = 0; b < tempBucket.bucketElements; b++)
      {
        tempElement = tempBucket.bucketImageVectors[b];
        vectorDistance = calculateManhattanDistance(queryVector, tempElement.imageVector, vectorDimension);
        if (resultANN->elementsResultArray == resultANN->sizeResultArray)
          resizeArray(&resultANN->resultArray, &resultANN->sizeResultArray);
        resultANN->resultArray[resultANN->elementsResultArray].inputVectorId = tempElement.imageVectorId;
        resultANN->resultArray[resultANN->elementsResultArray].vectorDistance = vectorDistance;
        resultANN->elementsResultArray++;
        gettimeofday(&startRange, NULL);
        if (vectorDistance <= R)
        {
          if (resultANN->elementsResultRangeArray == resultANN->sizeResultRangeArray)
            resizeArray(&resultANN->resultRangeArray, &resultANN->sizeResultRangeArray);
          resultANN->resultRangeArray[resultANN->elementsResultRangeArray].inputVectorId = tempElement.imageVectorId;
          resultANN->resultRangeArray[resultANN->elementsResultRangeArray].vectorDistance = vectorDistance;
          resultANN->elementsResultRangeArray++;
        }
        gettimeofday(&endRange, NULL);
        totalRangeTime = totalRangeTime
                         + ((endRange.tv_sec - startRange.tv_sec) * 1000000)
                         + (endRange.tv_usec - startRange.tv_usec);
        MsChecked++;
        if (MsChecked == M)
        {
          stopSearchFlag = 1;
          break;
        }
      }
      probesChecked++;
    }
    else
    {
      for (uint32_t i = 0; i < hashTable.hashTableSize; i++)
      {
        hammingDistance = calculateHammingDistance(hashKey, i);
        if (hammingDistance == curHammingDistance)
          tempBucket = hashTable.hashTableArray[i];
        else
          continue;

        for (uint32_t b = 0; b < tempBucket.bucketElements; b++)
        {
          tempElement = tempBucket.bucketImageVectors[b];
          vectorDistance = calculateManhattanDistance(queryVector, tempElement.imageVector, vectorDimension);
          if (resultANN->elementsResultArray == resultANN->sizeResultArray)
            resizeArray(&resultANN->resultArray, &resultANN->sizeResultArray);
          resultANN->resultArray[resultANN->elementsResultArray].inputVectorId = tempElement.imageVectorId;
          resultANN->resultArray[resultANN->elementsResultArray].vectorDistance = vectorDistance;
          resultANN->elementsResultArray++;
          gettimeofday(&startRange, NULL);
          if (vectorDistance <= R)
          {
            if (resultANN->elementsResultRangeArray == resultANN->sizeResultRangeArray)
              resizeArray(&resultANN->resultRangeArray, &resultANN->sizeResultRangeArray);
            resultANN->resultRangeArray[resultANN->elementsResultRangeArray].inputVectorId = tempElement.imageVectorId;
            resultANN->resultRangeArray[resultANN->elementsResultRangeArray].vectorDistance = vectorDistance;
            resultANN->elementsResultRangeArray++;
          }
          gettimeofday(&endRange, NULL);
          totalRangeTime = totalRangeTime
                           + ((endRange.tv_sec - startRange.tv_sec) * 1000000)
                           + (endRange.tv_usec - startRange.tv_usec);
          MsChecked++;
          if (MsChecked == M)
          {
            stopSearchFlag = 1;
            break;
          }
        }
        if (stopSearchFlag == 1)
          break;
        probesChecked++;
        if (probesChecked == probes)
        {
          stopSearchFlag = 1;
          break;
        }
      }
    }
    if (stopSearchFlag == 1)
      break;
    curHammingDistance++;
  }
  quickSort(resultANN->resultArray, resultANN->elementsResultArray);
  gettimeofday(&end, NULL);
  resultTime->timeANN = ((end.tv_sec - start.tv_sec) * 1000000) + (end.tv_usec - start.tv_usec) - totalRangeTime;
}

void printResults(resultNN_t *resultNN, resultANN_t resultANN, resultTime_t resultTime,
                  uint32_t queryVectorId, uint32_t N, uint8_t flag, FILE *outputFd)
{
  uint32_t outputSize;

  if (N <= resultANN.elementsResultArray)
    outputSize = N;
  else
    outputSize = resultANN.elementsResultArray;

  fprintf(outputFd, "-----------------------------------\n");
  fprintf(outputFd, "Query: %u\n", queryVectorId + 1);
  for (uint32_t i = 0; i < outputSize; i++)
  {
    fprintf(outputFd, "Nearest neighbor - %u: %u\n", i + 1, resultANN.resultArray[i].inputVectorId);
    if (flag == 0)
      fprintf(outputFd, "\tDistanceLSH: %u\n", resultANN.resultArray[i].vectorDistance);
    else
      fprintf(outputFd, "\tDistanceCube: %u\n", resultANN.resultArray[i].vectorDistance);
    fprintf(outputFd, "\tDistanceTrue: %u\n", resultNN[i].vectorDistance);
  }
  if (flag == 0)
    fprintf(outputFd, "tLSH: %d\n", resultTime.timeANN);
  else
    fprintf(outputFd, "tCube: %d\n", resultTime.timeANN);
  fprintf(outputFd, "tTrue: %d\n", resultTime.timeNN);

  fprintf(outputFd, "R-near neighbors:\n");
  for (uint32_t i = 0; i < resultANN.elementsResultRangeArray; i++)
    fprintf(outputFd, "\tImage[%u]: %u\n", i + 1, resultANN.resultRangeArray[i].inputVectorId);
  fprintf(outputFd, "-----------------------------------\n");
}