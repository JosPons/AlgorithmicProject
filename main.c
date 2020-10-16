#include <stdio.h>
#include <stdlib.h>
#include "fileIOFunctions.h"


int main(int argc, char **argv)
{
  FILE *datasetFd;

  if (argc != 3)
  {
    printf("Expected number of arguments is 3\n");
    exit(1);
  }

  datasetFd = OpenInitializationDataset(argv[2]);
  ReadInitializationDataset(datasetFd);
  //TODO: Store everything "ReadInitializationDataset" fucntion does
  //      into a struct with all vector information and all vectors.


  return 0;
}