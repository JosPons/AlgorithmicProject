#ifndef ALGORITHMICPROJECT_DATASTRUCTURES_H
#define ALGORITHMICPROJECT_DATASTRUCTURES_H

typedef uint8_t coordType;

typedef struct imageDataset_t
{
  int32_t magicNumber;
  int32_t numOfImages;
  int32_t rows;
  int32_t columns;
  uint32_t numOfPixels;
  coordType *imagesVectors;
} imageDataset_t;

void initializeImageDataset(int32_t, int32_t, int32_t, int32_t, imageDataset_t *);
coordType *createImagesVectors(imageDataset_t);

#endif //ALGORITHMICPROJECT_DATASTRUCTURES_H
