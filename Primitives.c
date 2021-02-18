#include <stdlib.h>
#include "Primitives.h"

int* Integer(int i) {
	int* ptr = (int*) malloc(sizeof(int));
	*ptr = i;	
	return ptr;
}

double* Double(double d) {
	double* ptr = (double*) malloc(sizeof(double));
	*ptr = d;
	return ptr;
}

float* Float(float f) {
	float* ptr = (float*) malloc(sizeof(float));
	*ptr = f;
	return ptr;
}

char* Character(char c) {
	char* ptr = (char*) malloc(sizeof(char));
	*ptr = c;
	return ptr;
}

short* Short(short s) {
	short* ptr = (short*) malloc(sizeof(short));
	*ptr = s;
	return ptr;
}

long* Long(long l) {
	long* ptr = (long*) malloc(sizeof(long));
	*ptr = l;
	return ptr;
}
