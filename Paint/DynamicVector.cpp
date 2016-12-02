#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"conio2.h"

void push(wektor *vector, char input) {
	if ((*vector).actualPosition == (*vector).memorySize)
		changeMemory(vector, 2 * (*vector).memorySize);
	(*vector).vec[(*vector).actualPosition] = input;
	(*vector).actualPosition++;
}
char pop(wektor *vector) {
	(*vector).actualPosition--;
	char output = (*vector).vec[(*vector).actualPosition];
	if (3*(*vector).actualPosition < (*vector).memorySize)
		changeMemory(vector, (*vector).memorySize / 2);
	return output;
}
void newVector(wektor *vector) {
	(*vector).actualPosition = 0;
	(*vector).memorySize = 1;
	(*vector).vec = (char*)malloc((*vector).memorySize*sizeof(char));
}
void changeMemory(wektor *vector, int new_memorySize) {
	(*vector).memorySize = new_memorySize;
	char *buffer = (char*)malloc((*vector).memorySize * sizeof(char));
	memcpy(buffer, (*vector).vec, (*vector).actualPosition*sizeof(char));
	free((*vector).vec);
	(*vector).vec = buffer;
}




