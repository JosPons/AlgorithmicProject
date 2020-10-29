#include <stdio.h>
#include <stdlib.h>
#include "fileIOFunctions.h"
#include "utilityFunctions.h"


FILE *openInputDataset(char *path)
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

FILE *openQueryDataset(char *path)
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

FILE *openOutputFile(char *path)
{
  FILE *fd;

  fd = fopen(path, "w");
  if (fd == NULL)
  {
    fprintf(stderr, "Error, couldn't open file at \"%s\" : ", path);
    perror("");
    exit(1);
  }
  return fd;
}

void closeInputDataset(char *path, FILE *fd)
{
  if (fclose(fd) != 0)
  {
    fprintf(stderr, "Error, couldn't close file at \"%s\" : ", path);
    perror("");
    exit(1);
  }
}

void closeQueryDataset(char *path, FILE *fd)
{
  if (fclose(fd) != 0)
  {
    fprintf(stderr, "Error, couldn't close file at \"%s\" : ", path);
    perror("");
    exit(1);
  }
}

void closeOutputFile(char *path, FILE *fd)
{
  if (fclose(fd) != 0)
  {
    fprintf(stderr, "Error, couldn't close file at \"%s\" : ", path);
    perror("");
    exit(1);
  }
}

void storeInputDatasetInMemory(FILE *fd, imageDataset_t *imageDataset)
{
  int32_t buffer[4];

  fread(buffer, sizeof(buffer), 1, fd);
  createImageDataset(littleToBigEndian(buffer[0]), littleToBigEndian(buffer[1]),
                     littleToBigEndian(buffer[2]), littleToBigEndian(buffer[3]),
                     imageDataset);
  fread(imageDataset->imagesVectors, sizeof(coordType), imageDataset->numOfPixels, fd);
}

void deleteInputDatasetFromMemory(imageDataset_t imageDataset)
{
  destroyImageDataset(imageDataset);
}