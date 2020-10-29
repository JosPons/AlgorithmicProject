#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashTable.h"

#define BUCKET_SIZE 16


//**************************************************************************************//
void createHashTable(hashTable_t *hashTable, uint32_t hashTableSize, uint32_t vectorDimension, uint32_t k, uint32_t W)
{
  createHashFunctionFamilyH(&hashTable->hashFunctionsFamilyH, vectorDimension, k, W);
  generateSi(hashTable->hashFunctionsFamilyH);
  hashTable->hashTableArray = calloc(hashTableSize, sizeof(bucket_t));
  if (hashTable->hashTableArray == NULL)
  {
    perror("Error, couldn't allocate memory for \"hashTable\" array");
    exit(1);
  }
  hashTable->hashTableSize = hashTableSize;
  hashTable->hashTableElements = 0;
  for (uint32_t i = 0; i < hashTableSize; i++)
  {
    hashTable->hashTableArray[i].bucketImageVectors = calloc(BUCKET_SIZE, sizeof(bucketElement_t));
    if (hashTable->hashTableArray[i].bucketImageVectors == NULL)
    {
      perror("Error, couldn't allocate memory for \"hashTable bucket\"");
      exit(1);
    }
    hashTable->hashTableArray[i].bucketSize = BUCKET_SIZE;
    hashTable->hashTableArray[i].bucketElements = 0;
    hashTable->hashTableArray[i].freeBucketIndex = 0;
  }
}

void destroyHashTable(hashTable_t hashTable)
{
  for (uint32_t i = 0; i < hashTable.hashTableSize; i++)
  {
    for (uint32_t b = 0; b < hashTable.hashTableArray[i].bucketSize; b++)
    {
      if (hashTable.hashTableArray[i].bucketImageVectors[b].imageVector != NULL)
        free(hashTable.hashTableArray[i].bucketImageVectors[b].imageVector);
    }
    free(hashTable.hashTableArray[i].bucketImageVectors);
  }
  free(hashTable.hashTableArray);
  destroyHashFunctionFamilyH(hashTable.hashFunctionsFamilyH);
}

void insertHashTable(hashTable_t *hashTable, const coordType *imageVector)
{
  uint32_t hashValue;
  uint32_t hashKey;
  uint32_t freeBucketIndex;


  hashValue = hashFunctionG(hashTable->hashFunctionsFamilyH, imageVector);
  hashKey = hashValue % hashTable->hashTableSize;
  freeBucketIndex = hashTable->hashTableArray[hashKey].freeBucketIndex;
  if (hashTable->hashTableArray[hashKey].bucketElements == hashTable->hashTableArray[hashKey].bucketSize)
    resizeHashTableBucket(&hashTable->hashTableArray[hashKey]);
  hashTable->hashTableArray[hashKey].bucketImageVectors[freeBucketIndex].imageVector =
      calloc(hashTable->hashFunctionsFamilyH.vectorDimension, sizeof(coordType));
  if (hashTable->hashTableArray[hashKey].bucketImageVectors[freeBucketIndex].imageVector == NULL)
  {
    perror("Error, couldn't allocate memory for \"imageVector\" array inside hash table bucket");
    exit(1);
  }
  memcpy(hashTable->hashTableArray[hashKey].bucketImageVectors[freeBucketIndex].imageVector, imageVector,
         sizeof(coordType) * hashTable->hashFunctionsFamilyH.vectorDimension);
  hashTable->hashTableArray[hashKey].bucketImageVectors[freeBucketIndex].hashKeyG = hashValue;
  hashTable->hashTableArray[hashKey].bucketElements++;
  hashTable->hashTableArray[hashKey].freeBucketIndex++;
  hashTable->hashTableElements++;
}

void resizeHashTableBucket(bucket_t *bucket)
{
  uint32_t oldSize = bucket->bucketSize;
  bucket->bucketSize = bucket->bucketSize * 2;
  bucket->bucketImageVectors = realloc(bucket->bucketImageVectors, sizeof(bucketElement_t) * bucket->bucketSize);
  if (bucket->bucketImageVectors == NULL)
  {
    perror("Error, couldn't re-allocate memory for \"bucketElement\" array");
    exit(1);
  }
  memset(bucket->bucketImageVectors + oldSize, 0, sizeof(bucketElement_t) * oldSize);
}
//**************************************************************************************//

//**************************************************************************************//
void printHashTable(hashTable_t hashTable, FILE *outputFd)
{
  fprintf(outputFd, "------------------------------------------------------\n");
  fprintf(outputFd, "Hash table size: %u\n", hashTable.hashTableSize);
  fprintf(outputFd, "Hash table elements: %u\n", hashTable.hashTableElements);
  fprintf(outputFd, "------------------------------------------------------\n");
  for (uint32_t i = 0; i < hashTable.hashTableSize; i++)
  {
    fprintf(outputFd, "------------------------------------------------------\n");
    fprintf(outputFd, "Hash[%u] bucketSize: %u\n", i, hashTable.hashTableArray[i].bucketSize);
    fprintf(outputFd, "Hash[%u] bucketElements: %u\n", i, hashTable.hashTableArray[i].bucketElements);
    fprintf(outputFd, "Hash[%u] freeBucketIndex: %u\n", i, hashTable.hashTableArray[i].freeBucketIndex);
    fprintf(outputFd, "------------------------------------------------------\n");
    for (uint32_t b = 0; b < hashTable.hashTableArray[i].bucketSize; b++)
    {
      fprintf(outputFd, "\tBucket[%u] HashKey: %u\n", b, hashTable.hashTableArray[i].bucketImageVectors[b].hashKeyG);
      fprintf(outputFd, "\tBucket[%u] Vector: %p\n", b, hashTable.hashTableArray[i].bucketImageVectors[b].imageVector);
    }
  }
}

void printHashFunctionFamilyH(hashTable_t hashTable, FILE *outputFd)
{
  fprintf(outputFd, "Vector Dimension: %u\n", hashTable.hashFunctionsFamilyH.vectorDimension);
  fprintf(outputFd, "K: %u\n", hashTable.hashFunctionsFamilyH.k);
  fprintf(outputFd, "W: %u\n", hashTable.hashFunctionsFamilyH.W);
  fprintf(outputFd, "M: %u\n", hashTable.hashFunctionsFamilyH.M);
  fprintf(outputFd, "m: %u\n", hashTable.hashFunctionsFamilyH.m);

  uint32_t sum = 0;
  for (uint32_t k = 0; k < hashTable.hashFunctionsFamilyH.k; k++)
  {
    fprintf(outputFd, "H[%u]: ", k);
    for (uint32_t d = 0; d < hashTable.hashFunctionsFamilyH.vectorDimension; d++)
    {
      fprintf(outputFd, "%8.2f ", hashTable.hashFunctionsFamilyH.hashFunctionsArray[k].randomSArray[d]);
      if (hashTable.hashFunctionsFamilyH.hashFunctionsArray[k].randomSArray[d] < 256)
        sum++;
    }
    fprintf(outputFd, "\n");
  }
  fprintf(outputFd, "Numbers below 256 are: %u\n", sum);
}
//**************************************************************************************//