#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilityFunctions.h"

#define MAX_LEVELS 300


int32_t littleToBigEndian(int32_t num)
{
  return (((num >> 24) & 0x000000ff) |
          ((num >> 8) & 0x0000ff00) |
          ((num << 8) & 0x00ff0000) |
          ((num << 24) & 0xff000000));
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

uint32_t calculateHammingDistance(uint32_t numberA, uint32_t numberB)
{
  uint32_t xorOfNumbers = numberA ^numberB;
  uint32_t numOfSetBits = 0;

  while (xorOfNumbers > 0)
  {
    numOfSetBits = numOfSetBits + (xorOfNumbers & 1);
    xorOfNumbers = xorOfNumbers >> 1;
  }
  return numOfSetBits;
}

uint32_t calculateManhattanDistance(const coordType *imageVectorA, const coordType *imageVectorB,
                                    uint32_t vectorDimension)
{
  uint32_t distance = 0;

  for (uint32_t i = 0; i < vectorDimension; i++)
    distance = distance + (uint32_t) abs(imageVectorA[i] - imageVectorB[i]);
  return distance;
}

uint32_t removeDuplicates(resultNN_t *resultArray, uint32_t arraySize)
{
  int32_t j = 0;

  for (int32_t i = 1; i < arraySize; i++)
  {
    if (resultArray[i].inputVectorId != resultArray[j].inputVectorId)
    {
      j++;
      resultArray[j] = resultArray[i];
    }
  }
  arraySize = j + 1;
  return arraySize;
}

void createResultANN(resultANN_t *resultANN, uint32_t size)
{
  resultANN->resultArray = calloc(size, sizeof(resultNN_t));
  if (resultANN->resultArray == NULL)
  {
    perror("Error, couldn't allocate memory for \"resultArray\"");
    exit(1);
  }
  resultANN->resultRangeArray = calloc(size, sizeof(resultNN_t));
  if (resultANN->resultRangeArray == NULL)
  {
    perror("Error, couldn't allocate memory for \"resultRangeArray\"");
    exit(1);
  }
  resultANN->sizeResultArray = size;
  resultANN->sizeResultRangeArray = size;
  resultANN->elementsResultArray = 0;
  resultANN->elementsResultRangeArray = 0;
}

void destroyResultANN(resultANN_t resultANN)
{
  free(resultANN.resultArray);
  free(resultANN.resultRangeArray);
}

void resizeArray(resultNN_t **array, uint32_t *size)
{
  uint32_t oldSize = *size;
  *size = *size * 2;
  *array = realloc(*array, sizeof(resultNN_t) * (*size));
  if (*array == NULL)
  {
    perror("Error, couldn't re-allocate memory for result \"Array\"");
    exit(1);
  }
  memset(*array + oldSize, 0, sizeof(resultNN_t) * oldSize);
}

void quickSort(resultNN_t *array, uint32_t arraySize)
{
  resultNN_t piv;
  int32_t i = 0, L, R, swap;
  int32_t beg[MAX_LEVELS];
  int32_t end[MAX_LEVELS];

  beg[0] = 0;
  end[0] = arraySize;
  while (i >= 0)
  {
    L = beg[i];
    R = end[i] - 1;
    if (L < R)
    {
      piv = array[L];
      while (L < R)
      {
        while (array[R].vectorDistance >= piv.vectorDistance && L < R)
          R--;
        if (L < R)
          array[L++] = array[R];
        while (array[L].vectorDistance <= piv.vectorDistance && L < R)
          L++;
        if (L < R)
          array[R--] = array[L];
      }
      array[L] = piv;
      beg[i + 1] = L + 1;
      end[i + 1] = end[i];
      end[i++] = L;
      if (end[i] - beg[i] > end[i - 1] - beg[i - 1])
      {
        swap = beg[i];
        beg[i] = beg[i - 1];
        beg[i - 1] = swap;
        swap = end[i];
        end[i] = end[i - 1];
        end[i - 1] = swap;
      }
    }
    else
      i--;
  }
}

void insertionSort(resultNN_t *array, uint32_t arraySize)
{
  resultNN_t tempElement;
  int32_t j;

  for (int32_t i = 1; i < arraySize; i++)
  {
    tempElement = array[i];
    j = i - 1;
    while ((tempElement.inputVectorId < array[j].inputVectorId) && (j >= 0))
    {
      array[j + 1] = array[j];
      j = j - 1;
    }
    array[j + 1] = tempElement;
  }
}