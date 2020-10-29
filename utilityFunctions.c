#include <stdio.h>
#include <stdlib.h>
#include "utilityFunctions.h"


int32_t littleToBigEndian(int32_t num)
{
  return (((num >> 24) & 0x000000ff) |
          ((num >> 8) & 0x0000ff00) |
          ((num << 8) & 0x00ff0000) |
          ((num << 24) & 0xff000000));
}

uint32_t calculateManhattanDistance(coordType *imageVectorA, coordType *imageVectorB,
                                    uint32_t vectorDimension)
{
  uint32_t distance = 0;

  for (uint32_t i = 0; i < vectorDimension; i++)
    distance = distance + (uint32_t) abs(imageVectorA[i] - imageVectorB[i]);
  return distance;
}

int32_t mod(int32_t x, int32_t y)
{
  return x > 0 ? x & ((1 << y) - 1) : -x & ((1 << y) - 1);
}

uint32_t modularPow(int32_t base, int32_t exponent, int32_t modulus)
{
  int32_t c = 1;

  if (modulus == 0)
    return 0;
  for (uint32_t exp = 0; exp < exponent; exp++)
    c = mod(c * base, modulus);
  return c;
}

uint32_t fastModularPow(int32_t base, int32_t exponent, int32_t modulus)
{
  int32_t result = 1;
  if (1 & exponent)
    result = base;
  while (1)
  {
    if (!exponent) break;
    exponent = exponent >> 1;
    base = mod(base * base, modulus);
    if (exponent & 1)
      result = mod(result * base, modulus);
  }
  return result;
}

uint32_t concatenateIntegers(const uint32_t *integersArray, uint32_t arraySize, uint8_t shiftValue)
{
  uint32_t finalInteger;

  finalInteger = integersArray[0];
  for (uint32_t i = 1; i < arraySize; i++)
  {
    finalInteger = (finalInteger << shiftValue) | integersArray[i];
  }
  return finalInteger;
}