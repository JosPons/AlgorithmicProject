#ifndef ALGORITHMICPROJECT_DATASETSTRUCTURE_H
#define ALGORITHMICPROJECT_DATASETSTRUCTURE_H


typedef uint8_t coordType;

typedef struct imageDataset_t
{
  int32_t magicNumber;
  int32_t numOfImages;
  int32_t rows;
  int32_t columns;
  uint32_t numOfPixels;
  uint32_t vectorDimension;
  coordType *imagesVectors;
} imageDataset_t;

void createImageDataset(int32_t, int32_t, int32_t, int32_t, imageDataset_t *);
void destroyImageDataset(imageDataset_t);
coordType *createImagesVectors(imageDataset_t);

#endif //ALGORITHMICPROJECT_DATASETSTRUCTURE_H
