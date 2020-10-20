#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "programParameters.h"
#include "fileIOFunctions.h"


int main(int argc, char **argv)
{
  cmdLineParametersLSH_t cmdLineParametersLSH;
  cmdLineParametersCube_t cmdLineParametersCube;
  FILE *datasetFd;
  FILE *outputFd;
  imageDataset_t imageDataset;


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


//  datasetFd = OpenInitializationDataset(argv[2]);
//  StoreInitializationDatasetInMemory(datasetFd, &imageDataset);


//  outputFd = fopen("C:\\Users\\User\\Desktop\\output.txt", "w");
//  if (outputFd == NULL)
//  {
//    fprintf(stderr, "Error, couldn't open file at \"C:\\Users\\User\\Desktop\" : ");
//    perror("");
//    exit(1);
//  }
//
//  for (int i = 0; i < imageDataset.numOfPixels; i++)
//  {
//    fprintf(outputFd, "%u ", imageDataset.imagesVectors[i]);
//    if (((i + 1) % 784) == 0)
//      fprintf(outputFd, "\n");
//  }
//
//  if (fclose(outputFd) != 0)
//  {
//    fprintf(stderr, "Error, couldn't close file at \"C:\\Users\\User\\Desktop\\output.txt\" : ");
//    perror("");
//    exit(1);
//  }

  return 0;
}