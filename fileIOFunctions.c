#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
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

void storeInputDatasetInMemory(FILE *fd, imageDataset_t *inputImageDataset)
{
  int32_t buffer[4];

  fread(buffer, sizeof(buffer), 1, fd);
  createImageDataset(littleToBigEndian(buffer[0]), littleToBigEndian(buffer[1]),
                     littleToBigEndian(buffer[2]), littleToBigEndian(buffer[3]),
                     inputImageDataset);
  fread(inputImageDataset->imagesVectors, sizeof(coordType), inputImageDataset->numOfPixels, fd);
}

void deleteInputDatasetFromMemory(imageDataset_t inputImageDataset)
{
  destroyImageDataset(inputImageDataset);
}

void storeQueryDatasetInMemory(FILE *fd, imageDataset_t *queryImageDataset)
{
  int32_t buffer[4];

  fread(buffer, sizeof(buffer), 1, fd);
  createImageDataset(littleToBigEndian(buffer[0]), littleToBigEndian(buffer[1]),
                     littleToBigEndian(buffer[2]), littleToBigEndian(buffer[3]),
                     queryImageDataset);
  fread(queryImageDataset->imagesVectors, sizeof(coordType), queryImageDataset->numOfPixels, fd);
}

void deleteQueryDatasetFromMemory(imageDataset_t queryImageDataset)
{
  destroyImageDataset(queryImageDataset);
}