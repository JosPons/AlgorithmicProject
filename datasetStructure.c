#include <stdio.h>
#include <stdlib.h>
#include "datasetStructure.h"


void createImageDataset(int32_t magicNumber, int32_t numOfImages,
                        int32_t rows, int32_t columns, imageDataset_t *imageDataset)
{
  imageDataset->magicNumber = magicNumber;
  imageDataset->numOfImages = numOfImages;
  imageDataset->rows = rows;
  imageDataset->columns = columns;
  imageDataset->numOfPixels = numOfImages * rows * columns;
  imageDataset->vectorDimension = rows * columns;
  imageDataset->imagesVectors = createImagesVectors(*imageDataset);
}

void destroyImageDataset(imageDataset_t imageDataset)
{
  free(imageDataset.imagesVectors);
}

coordType *createImagesVectors(imageDataset_t imageDataset)
{
  imageDataset.imagesVectors = (coordType *) calloc(imageDataset.numOfPixels, sizeof(coordType));
  if (imageDataset.imagesVectors == NULL)
  {
    perror("Error, couldn't allocate memory for \"imagesVectors\" array");
    exit(1);
  }
  return imageDataset.imagesVectors;
}
