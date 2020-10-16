#ifndef ALGORITHMICPROJECT_FILEIOFUNCTIONS_H
#define ALGORITHMICPROJECT_FILEIOFUNCTIONS_H

FILE *OpenInitializationDataset(char *);
void CloseInitializationDataset(char *, FILE *);
void ReadInitializationDataset(FILE *);

#endif //ALGORITHMICPROJECT_FILEIOFUNCTIONS_H
