#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "programParameters.h"
#include "fileIOFunctions.h"
#include "hashTable.h"


int main(int argc, char **argv)
{
  cmdLineParametersLSH_t cmdLineParametersLSH;
  cmdLineParametersCube_t cmdLineParametersCube;
  imageDataset_t imageDataset;
  hashTable_t hashTable;
  FILE *inputFd;
  FILE *outputFd;


  //**************************************************************************************//
  srand(time(NULL));

  strcpy(argv[0], "lsh"); //TODO: Temporary to change the executable name.
  //TODO: Erase it after I create the Makefile
  if (strcmp("lsh", argv[0]) == 0)
    initializeCmdLineParametersLSH(argc, argv, &cmdLineParametersLSH);
  else if (strcmp("cube", argv[0]) == 0)
    initializeCmdLineParametersCube(argc, argv, &cmdLineParametersCube);
  else
  {
    printf("Error, couldn't find executable file \"lsh\" or \"cube\"\n");
    exit(1);
  }
  //**************************************************************************************//
  inputFd = openInputDataset(cmdLineParametersLSH.inputFilePath);
  outputFd = openOutputFile(cmdLineParametersLSH.outputFilePath);
  storeInputDatasetInMemory(inputFd, &imageDataset);
  //**************************************************************************************//
  createHashTable(&hashTable, imageDataset.numOfImages / 16, imageDataset.vectorDimension,
                  cmdLineParametersLSH.k, 4000);
  //**************************************************************************************//
  coordType imageVector[imageDataset.vectorDimension];
  memset(imageVector, 0, sizeof(imageVector));
  for (uint32_t i = 0; i < imageDataset.numOfImages; i++)
  {
    memcpy(imageVector, &(imageDataset.imagesVectors[i * imageDataset.vectorDimension]), sizeof(imageVector));
    insertHashTable(&hashTable, imageVector);
  }
  printHashTable(hashTable, outputFd);
  //**************************************************************************************//
  destroyHashTable(hashTable);
  //**************************************************************************************//
  deleteInputDatasetFromMemory(imageDataset);
  closeOutputFile(cmdLineParametersLSH.outputFilePath, outputFd);
  closeInputDataset(cmdLineParametersLSH.inputFilePath, inputFd);
  //**************************************************************************************//
  return 0;
}