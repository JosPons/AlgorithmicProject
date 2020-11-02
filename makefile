SOURCES = datasetStructure.c fileIOFunctions.c hashFunction.c hashTable.c main.c programParameters.c searchAlgorithms.c utilityFunctions.c
OBJECTS = datasetStructure.o fileIOFunctions.o hashFunction.o hashTable.o main.o programParameters.o searchAlgorithms.o utilityFunctions.o
EXECUTABLE_LSH = lsh
EXECUTABLE_CUBE = cube
CC = gcc
FLAGS = -Wall -g -c -O2

all: $(OBJECTS)
	$(CC) -o $(EXECUTABLE_LSH) datasetStructure.o fileIOFunctions.o hashFunction.o hashTable.o main.o programParameters.o searchAlgorithms.o utilityFunctions.o -lm
	$(CC) -o $(EXECUTABLE_CUBE) datasetStructure.o fileIOFunctions.o hashFunction.o hashTable.o main.o programParameters.o searchAlgorithms.o utilityFunctions.o -lm

datasetStructure.o: datasetStructure.c
	$(CC) $(FLAGS) datasetStructure.c

fileIOFunctions.o: fileIOFunctions.c
	$(CC) $(FLAGS) fileIOFunctions.c

hashFunction.o: hashFunction.c
	$(CC) $(FLAGS) hashFunction.c

hashTable.o: hashTable.c
	$(CC) $(FLAGS) hashTable.c

main.o: main.c
	$(CC) $(FLAGS) main.c

programParameters.o: programParameters.c
	$(CC) $(FLAGS) programParameters.c

searchAlgorithms.o: searchAlgorithms.c
	$(CC) $(FLAGS) searchAlgorithms.c

utilityFunctions.o: utilityFunctions.c
	$(CC) $(FLAGS) utilityFunctions.c

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE_LSH) $(EXECUTABLE_CUBE)