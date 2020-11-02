#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include "programParameters.h"
#include "fileIOFunctions.h"
#include "hashTable.h"
#include "searchAlgorithms.h"


int main(int argc, char **argv)
{
  cmdLineParametersLSH_t cmdLineParametersLSH;
  cmdLineParametersCube_t cmdLineParametersCube;
  imageDataset_t inputImageDataset;
  imageDataset_t queryImageDataset;
  hashTable_t *arrayOfHashTables;
  hashTable_t hashTable;
  FILE *inputFd;
  FILE *queryFd;
  FILE *outputFd;


  //**************************************************************************************//
  /* Program parameters */
  srand(time(NULL));

  strcpy(argv[0], "cube"); //TODO: Temporary to change the executable name.
  if (strcmp("./lsh", argv[0]) == 0)
    initializeCmdLineParametersLSH(argc, argv, &cmdLineParametersLSH);
  else if (strcmp("./cube", argv[0]) == 0)
    initializeCmdLineParametersCube(argc, argv, &cmdLineParametersCube);
  else
  {
    printf("Error, couldn't find executable file \"lsh\" or \"cube\"\n");
    exit(1);
  }


  //**************************************************************************************//
  if (strcmp("./lsh", argv[0]) == 0)
  {
    //**************************************************************************************//
    /* Open file streams and store datasets into memory */
    inputFd = openInputDataset(cmdLineParametersLSH.inputFilePath);
    queryFd = openQueryDataset(cmdLineParametersLSH.queryFilePath);
    outputFd = openOutputFile(cmdLineParametersLSH.outputFilePath);
    storeInputDatasetInMemory(inputFd, &inputImageDataset);
    storeQueryDatasetInMemory(queryFd, &queryImageDataset);
    printf("Loaded input dataset into memory.\n");
    printf("Loaded query dataset into memory.\n");
    //**************************************************************************************//
    /* Create LSH hash tables */
    printf("Initializing LSH hash tables...\n");
    createArrayOfHashTables(&arrayOfHashTables, cmdLineParametersLSH.L, inputImageDataset.numOfImages / 16,
                            inputImageDataset.vectorDimension, cmdLineParametersLSH.k, 40000);

    coordType inputVector[inputImageDataset.vectorDimension];
    memset(inputVector, 0, sizeof(inputVector));
    for (uint32_t i = 0; i < inputImageDataset.numOfImages; i++)
    {
      memcpy(inputVector, &(inputImageDataset.imagesVectors[i * inputImageDataset.vectorDimension]),
             sizeof(inputVector));
      insertArrayOfHashTable(arrayOfHashTables, cmdLineParametersLSH.L, inputVector, i);
    }
    printf("Finished initializing LSH hash tables...\n");
    //**************************************************************************************//
    /* Run query dataset through LSH search algorithm */
    printf("Initiating search algorithms for LSH...\n");
    resultNN_t resultNN[inputImageDataset.numOfImages];
    resultANN_t resultANN;
    resultTime_t resultTime;

    coordType queryVector[queryImageDataset.vectorDimension];
    memset(queryVector, 0, sizeof(queryVector));
    for (uint32_t i = 0; i < queryImageDataset.numOfImages; i++)
    {
      memcpy(queryVector, &(queryImageDataset.imagesVectors[i * queryImageDataset.vectorDimension]),
             sizeof(queryVector));
      findTrueNN(inputImageDataset, queryVector, resultNN, &resultTime);
      findApproximateNNLSH(arrayOfHashTables, cmdLineParametersLSH.L, queryVector,
                           &resultANN, &resultTime, cmdLineParametersLSH.R);
      printResults(resultNN, resultANN, resultTime, i, cmdLineParametersLSH.N, 0, outputFd);
      destroyResultANN(resultANN);
    }
    //**************************************************************************************//
    /* Release resources */
    printf("Deallocating memory of LSH hash tables...\n");
    destroyArrayOfHashTables(arrayOfHashTables, cmdLineParametersLSH.L);
    //**************************************************************************************//
    printf("Deleting input dataset from memory...\n");
    printf("Deleting query dataset from memory...\n");
    deleteQueryDatasetFromMemory(queryImageDataset);
    deleteInputDatasetFromMemory(inputImageDataset);
    closeOutputFile(cmdLineParametersLSH.outputFilePath, outputFd);
    closeQueryDataset(cmdLineParametersLSH.queryFilePath, queryFd);
    closeInputDataset(cmdLineParametersLSH.inputFilePath, inputFd);
    printf("Released all resources, exiting...\n");
    //**************************************************************************************//
  }
  else if (strcmp("./cube", argv[0]) == 0)
  {
    //**************************************************************************************//
    /* Open file streams and store datasets into memory */
    inputFd = openInputDataset(cmdLineParametersCube.inputFilePath);
    queryFd = openQueryDataset(cmdLineParametersCube.queryFilePath);
    outputFd = openOutputFile(cmdLineParametersCube.outputFilePath);
    storeInputDatasetInMemory(inputFd, &inputImageDataset);
    storeQueryDatasetInMemory(queryFd, &queryImageDataset);
    printf("Loaded input dataset into memory.\n");
    printf("Loaded query dataset into memory.\n");
    //**************************************************************************************//
    /* Create HyperCube hash table */
    printf("Initializing HyperCube hash table...\n");
    uint32_t hyperCubeSize = 1 << cmdLineParametersCube.k;
    createHashTable(&hashTable, hyperCubeSize, inputImageDataset.vectorDimension, cmdLineParametersCube.k, 40000);

    coordType inputVector[inputImageDataset.vectorDimension];
    memset(inputVector, 0, sizeof(inputVector));
    for (uint32_t i = 0; i < inputImageDataset.numOfImages; i++)
    {
      memcpy(inputVector, &(inputImageDataset.imagesVectors[i * inputImageDataset.vectorDimension]),
             sizeof(inputVector));
      insertHashTableCube(hashTable, inputVector, i);
    }
    printf("Finished initializing HyperCube hash table...\n");
    //**************************************************************************************//
    /* Run query dataset through HyperCube search algorithm */
    printf("Initiating search algorithms for HyperCube...\n");
    resultNN_t resultNN[inputImageDataset.numOfImages];
    resultANN_t resultANN;
    resultTime_t resultTime;

    coordType queryVector[queryImageDataset.vectorDimension];
    memset(queryVector, 0, sizeof(queryVector));
    for (uint32_t i = 0; i < queryImageDataset.numOfImages; i++)
    {
      memcpy(queryVector, &(queryImageDataset.imagesVectors[i * queryImageDataset.vectorDimension]),
             sizeof(queryVector));
      findTrueNN(inputImageDataset, queryVector, resultNN, &resultTime);
      findApproximateNNCube(hashTable, cmdLineParametersCube.M, cmdLineParametersCube.probes, queryVector,
                            &resultANN, &resultTime, cmdLineParametersCube.R, outputFd);
      printResults(resultNN, resultANN, resultTime, i, cmdLineParametersCube.N, 1, outputFd);
      destroyResultANN(resultANN);
    }
    //**************************************************************************************//
    /* Release resources */
    printf("Deallocating memory of HyperCube hash table...\n");
    destroyHashTable(hashTable);
    //**************************************************************************************//
    printf("Deleting input dataset from memory...\n");
    printf("Deleting query dataset from memory...\n");
    deleteQueryDatasetFromMemory(queryImageDataset);
    deleteInputDatasetFromMemory(inputImageDataset);
    closeOutputFile(cmdLineParametersCube.outputFilePath, outputFd);
    closeQueryDataset(cmdLineParametersCube.queryFilePath, queryFd);
    closeInputDataset(cmdLineParametersCube.inputFilePath, inputFd);
    printf("Released all resources, exiting...\n");
    //**************************************************************************************//
  }
  //**************************************************************************************//
  return 0;
}