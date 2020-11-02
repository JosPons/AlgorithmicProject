#ifndef ALGORITHMICPROJECT_UTILITYFUNCTIONS_H
#define ALGORITHMICPROJECT_UTILITYFUNCTIONS_H

#include <stdint.h>
#include "datasetStructure.h"
#include "searchAlgorithms.h"

int32_t littleToBigEndian(int32_t);
int32_t mod(int32_t, int32_t);
uint32_t modularPow(int32_t, int32_t, int32_t);
uint32_t fastModularPow(int32_t, int32_t, int32_t);
uint32_t concatenateIntegers(const uint32_t *, uint32_t, uint8_t);
uint32_t calculateHammingDistance(uint32_t, uint32_t);
uint32_t calculateManhattanDistance(const coordType *, const coordType *, uint32_t);
uint32_t removeDuplicates(resultNN_t *, uint32_t);
void createResultANN(resultANN_t *, uint32_t);
void destroyResultANN(resultANN_t);
void resizeArray(resultNN_t **, uint32_t *);
void quickSort(resultNN_t *, uint32_t);
void insertionSort(resultNN_t *, uint32_t);


#endif //ALGORITHMICPROJECT_UTILITYFUNCTIONS_H
