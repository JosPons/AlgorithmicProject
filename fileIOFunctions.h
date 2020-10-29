#ifndef ALGORITHMICPROJECT_FILEIOFUNCTIONS_H
#define ALGORITHMICPROJECT_FILEIOFUNCTIONS_H

#include "datasetStructure.h"

FILE *openInputDataset(char *);
FILE *openQueryDataset(char *);
FILE *openOutputFile(char *);
void closeInputDataset(char *, FILE *);
void closeQueryDataset(char *, FILE *);
void closeOutputFile(char *, FILE *);
void storeInputDatasetInMemory(FILE *, imageDataset_t *);
void deleteInputDatasetFromMemory(imageDataset_t);

#endif //ALGORITHMICPROJECT_FILEIOFUNCTIONS_H
