#include <stdio.h>
#include "utilityFunctions.h"


int32_t LittleToBigEndian(int32_t num)
{
  return (((num >> 24) & 0x000000ff) |
          ((num >> 8) & 0x0000ff00) |
          ((num << 8) & 0x00ff0000) |
          ((num << 24) & 0xff000000));
}