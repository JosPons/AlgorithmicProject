#ifndef ALGORITHMICPROJECT_UTILITYFUNCTIONS_H
#define ALGORITHMICPROJECT_UTILITYFUNCTIONS_H

#include "datasetStructure.h"

int32_t littleToBigEndian(int32_t);
uint32_t calculateManhattanDistance(coordType *, coordType *, uint32_t);
int32_t mod(int32_t, int32_t);
uint32_t modularPow(int32_t, int32_t, int32_t);
uint32_t fastModularPow(int32_t, int32_t, int32_t);
uint32_t concatenateIntegers(const uint32_t *, uint32_t, uint8_t);

#endif //ALGORITHMICPROJECT_UTILITYFUNCTIONS_H
