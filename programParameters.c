#include <stdlib.h>
#include <string.h>
#include "programParameters.h"


void initializeCmdLineParametersLSH(int argc, char **argv,
                                    cmdLineParametersLSH_t *cmdLineParametersLSH)
{
  /**
   * $./lsh
   * –d <input file>
   * –q <query file>
   * –k <int>
   * -L <int>
   * -ο <output file>
   * -Ν <number of nearest>
   * -R <radius>
   */

  if (argc < 7 || argc > 15)
  {
    printf("Expected number of arguments is between 7 and 15\n");
    exit(1);
  }

  /* Default Values */
  cmdLineParametersLSH->k = 4;
  cmdLineParametersLSH->L = 5;
  cmdLineParametersLSH->N = 1;
  cmdLineParametersLSH->R = 10000.00;

  for (int i = 1; i < argc; i += 2)
  {
    if (strcmp("-d", argv[i]) == 0)
      strcpy(cmdLineParametersLSH->inputFilePath, argv[i + 1]);
    else if (strcmp("-q", argv[i]) == 0)
      strcpy(cmdLineParametersLSH->queryFilePath, argv[i + 1]);
    else if (strcmp("-k", argv[i]) == 0)
      cmdLineParametersLSH->k = (uint32_t) atoi(argv[i + 1]);
    else if (strcmp("-L", argv[i]) == 0)
      cmdLineParametersLSH->L = (uint32_t) atoi(argv[i + 1]);
    else if (strcmp("-o", argv[i]) == 0)
      strcpy(cmdLineParametersLSH->outputFilePath, argv[i + 1]);
    else if (strcmp("-N", argv[i]) == 0)
      cmdLineParametersLSH->N = (uint32_t) atoi(argv[i + 1]);
    else if (strcmp("-R", argv[i]) == 0)
      cmdLineParametersLSH->R = (double) atof(argv[i + 1]);
    else
    {
      fprintf(stderr, "Wrong type of argument prefix.\nExpected list of \\"
                      "values: \' -d -q -k -L -o -N -R\'\n");
      exit(1);
    }
  }
}

void initializeCmdLineParametersCube(int argc, char **argv,
                                     cmdLineParametersCube_t *cmdLineParametersCube)
{
  /**
   * $./cube
   * –d <input file>
   * –q <query file>
   * –k <int>
   * -M <int>
   * -probes <int>
   * -ο <output file>
   * -Ν <number of nearest>
   * -R <radius>
   */

  if (argc < 7 || argc > 17)
  {
    printf("Expected number of arguments is between 7 and 17\n");
    exit(1);
  }

  /* Default Values */
  cmdLineParametersCube->k = 14;
  cmdLineParametersCube->M = 10;
  cmdLineParametersCube->probes = 2;
  cmdLineParametersCube->N = 1;
  cmdLineParametersCube->R = 10000.00;

  for (int i = 1; i < argc; i += 2)
  {
    if (strcmp("-d", argv[i]) == 0)
      strcpy(cmdLineParametersCube->inputFilePath, argv[i + 1]);
    else if (strcmp("-q", argv[i]) == 0)
      strcpy(cmdLineParametersCube->queryFilePath, argv[i + 1]);
    else if (strcmp("-k", argv[i]) == 0)
      cmdLineParametersCube->k = (uint32_t) atoi(argv[i + 1]);
    else if (strcmp("-M", argv[i]) == 0)
      cmdLineParametersCube->M = (uint32_t) atoi(argv[i + 1]);
    else if (strcmp("-probes", argv[i]) == 0)
      cmdLineParametersCube->probes = (uint32_t) atoi(argv[i + 1]);
    else if (strcmp("-o", argv[i]) == 0)
      strcpy(cmdLineParametersCube->outputFilePath, argv[i + 1]);
    else if (strcmp("-N", argv[i]) == 0)
      cmdLineParametersCube->N = (uint32_t) atoi(argv[i + 1]);
    else if (strcmp("-R", argv[i]) == 0)
      cmdLineParametersCube->R = (double) atof(argv[i + 1]);
    else
    {
      fprintf(stderr, "Wrong type of argument prefix.\nExpected list of \\"
                      "values: \' -d -q -k -M -probes -o -N -R\'\n");
      exit(1);
    }
  }
}

void printCmdLineParametersLSH(cmdLineParametersLSH_t cmdLineParametersLSH)
{
  printf("Input file path: %s\n", cmdLineParametersLSH.inputFilePath);
  printf("Query file path: %s\n", cmdLineParametersLSH.queryFilePath);
  printf("k: %u\n", cmdLineParametersLSH.k);
  printf("L: %u\n", cmdLineParametersLSH.L);
  printf("Output file path: %s\n", cmdLineParametersLSH.outputFilePath);
  printf("N: %u\n", cmdLineParametersLSH.N);
  printf("R: %lf\n", cmdLineParametersLSH.R);
}

void printCmdLineParametersCube(cmdLineParametersCube_t cmdLineParametersCube)
{
  printf("Input file path: %s\n", cmdLineParametersCube.inputFilePath);
  printf("Query file path: %s\n", cmdLineParametersCube.queryFilePath);
  printf("k: %u\n", cmdLineParametersCube.k);
  printf("M: %u\n", cmdLineParametersCube.M);
  printf("probes: %u\n", cmdLineParametersCube.probes);
  printf("Output file path: %s\n", cmdLineParametersCube.outputFilePath);
  printf("N: %u\n", cmdLineParametersCube.N);
  printf("R: %lf\n", cmdLineParametersCube.R);
}
