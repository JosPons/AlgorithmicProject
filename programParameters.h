#ifndef ALGORITHMICPROJECT_PROGRAMPARAMETERS_H
#define ALGORITHMICPROJECT_PROGRAMPARAMETERS_H

#include <stdio.h>

typedef struct cmdLineParametersLSH_t
{
  char inputFilePath[FILENAME_MAX];
  char queryFilePath[FILENAME_MAX];
  char outputFilePath[FILENAME_MAX];
  uint32_t k;
  uint32_t L;
  uint32_t N;
  double R;
} cmdLineParametersLSH_t;

typedef struct cmdLineParametersCube_t
{
  char inputFilePath[FILENAME_MAX];
  char queryFilePath[FILENAME_MAX];
  char outputFilePath[FILENAME_MAX];
  uint32_t k;
  uint32_t M;
  uint32_t probes;
  uint32_t N;
  double R;
} cmdLineParametersCube_t;

void initializeCmdLineParametersLSH(int, char **, cmdLineParametersLSH_t *);
void initializeCmdLineParametersCube(int, char **, cmdLineParametersCube_t *);
void printCmdLineParametersLSH(cmdLineParametersLSH_t);
void printCmdLineParametersCube(cmdLineParametersCube_t);

#endif //ALGORITHMICPROJECT_PROGRAMPARAMETERS_H
