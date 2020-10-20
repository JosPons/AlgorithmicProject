#include <stdio.h>
#include <stdlib.h>
#include "fileIOFunctions.h"
#include "utilityFunctions.h"


FILE *OpenInitializationDataset(char *path)
{
  FILE *fd;

  fd = fopen(path, "rb");
  if (fd == NULL)
  {
    fprintf(stderr, "Error, couldn't open file at \"%s\" : ", path);
    perror("");
    exit(1);
  }

  return fd;
}

void CloseInitializationDataset(char *path, FILE *fd)
{

  if (fclose(fd) != 0)
  {
    fprintf(stderr, "Error, couldn't close file at \"%s\" : ", path);
    perror("");
    exit(1);
  }
}

void StoreInitializationDatasetInMemory(FILE *fd, imageDataset_t *imageDataset)
{
  int32_t buffer[4];

  fread(buffer, sizeof(buffer), 1, fd);
  initializeImageDataset(LittleToBigEndian(buffer[0]), LittleToBigEndian(buffer[1]),
                         LittleToBigEndian(buffer[2]), LittleToBigEndian(buffer[3]),
                         imageDataset);
  fread(imageDataset->imagesVectors, sizeof(coordType), imageDataset->numOfPixels, fd);
}