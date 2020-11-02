#ifndef ALGORITHMICPROJECT_HASHTABLE_H
#define ALGORITHMICPROJECT_HASHTABLE_H

#include <stdint.h>
#include "programParameters.h"
#include "datasetStructure.h"

//**************************************************************************************//

typedef struct hashFunctionProperties_t
{
  double *randomSArray;
  int32_t *randomBitNumbersMap;
} hashFunctionProperties_t;

typedef struct hashFunctionsFamilyH_t
{
  hashFunctionProperties_t *hashFunctionsArray;
  uint32_t vectorDimension;
  uint32_t k;
  uint32_t W;
  uint32_t M;
  uint32_t m;
} hashFunctionsFamilyH_t;
//**************************************************************************************//
//**************************************************************************************//
typedef struct bucketElement_t
{
  coordType *imageVector;
  uint32_t imageVectorId;
  uint32_t hashKeyG;
} bucketElement_t;

typedef struct bucket_t
{
  bucketElement_t *bucketImageVectors;
  uint32_t bucketSize;
  uint32_t bucketElements;
  uint32_t freeBucketIndex;
} bucket_t;

typedef struct hashTable_t
{
  hashFunctionsFamilyH_t hashFunctionsFamilyH;
  bucket_t *hashTableArray;
  uint32_t hashTableSize;
  uint32_t hashTableElements;
} hashTable_t;
//**************************************************************************************//
void createHashFunctionFamilyH(hashFunctionsFamilyH_t *, uint32_t, uint32_t, uint32_t);
void destroyHashFunctionFamilyH(hashFunctionsFamilyH_t);
void generateSi(hashFunctionsFamilyH_t);
void calculateAi(hashFunctionsFamilyH_t, uint32_t, const coordType *, int32_t *);
uint32_t calculateHi(hashFunctionsFamilyH_t, const coordType *);
uint32_t calculateFi(hashFunctionsFamilyH_t, const coordType *);
uint32_t hashFunctionGLSH(hashFunctionsFamilyH_t, const coordType *);
uint32_t hashFunctionGCube(hashFunctionsFamilyH_t, const coordType *);
//**************************************************************************************//
void createHashTable(hashTable_t *, uint32_t, uint32_t, uint32_t, uint32_t);
void destroyHashTable(hashTable_t);
void insertHashTableLSH(hashTable_t, const coordType *, uint32_t);
void insertHashTableCube(hashTable_t, const coordType *, uint32_t);
uint32_t searchHashTableLSH(hashTable_t, const coordType *);
uint32_t searchHashTableCube(hashTable_t, const coordType *);
void createArrayOfHashTables(hashTable_t **, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);
void destroyArrayOfHashTables(hashTable_t *, uint32_t);
void insertArrayOfHashTable(hashTable_t *, uint32_t, const coordType *, uint32_t);
void resizeHashTableBucket(bucket_t *);
void printHashTable(hashTable_t, FILE *);
void printHashFunctionFamilyH(hashTable_t, FILE *);
//**************************************************************************************//

#endif //ALGORITHMICPROJECT_HASHTABLE_H
