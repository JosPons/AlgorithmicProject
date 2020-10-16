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

void ReadInitializationDataset(FILE *fd)
{
  int32_t buffer[4];
  uint8_t pixelBuffer[784];

  int32_t magicNumber;
  int32_t numOfImages;
  int32_t rows;
  int32_t columns;
  uint8_t pixelValue;

  fread(buffer, sizeof(buffer), 1, fd);
  magicNumber = LittleToBigEndian(buffer[0]);
  numOfImages = LittleToBigEndian(buffer[1]);
  rows = LittleToBigEndian(buffer[2]);
  columns = LittleToBigEndian(buffer[3]);

  while (fread(pixelBuffer, sizeof(pixelBuffer), 1, fd))
  {
    for (int i = 0; i < 784; i++)
      printf("%u ", pixelBuffer[i]);
    printf("\n");
  }
}