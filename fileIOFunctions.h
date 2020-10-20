#ifndef ALGORITHMICPROJECT_FILEIOFUNCTIONS_H
#define ALGORITHMICPROJECT_FILEIOFUNCTIONS_H

#include "dataStructures.h"

FILE *OpenInitializationDataset(char *);
void CloseInitializationDataset(char *, FILE *);
void StoreInitializationDatasetInMemory(FILE *, imageDataset_t *);

#endif //ALGORITHMICPROJECT_FILEIOFUNCTIONS_H
