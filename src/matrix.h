#ifndef STDUTIL_MATRIX_H
#define STDUTIL_MATRIX_H

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct fMatrix {
	float *elements;
	size_t rows, cols;
} fMatrix;

fMatrix create_fMatrix(size_t rows, size_t cols);

float fMatrix_get(fMatrix *mat, size_t row, size_t col);

bool fMatrix_set(fMatrix *mat, size_t row, size_t col, float data);

fMatrix fMatrix_multiply(fMatrix lmat, fMatrix rmat);

fMatrix fMatrix_add(fMatrix lmat, fMatrix rmat);

float fMatrix_determinant(fMatrix *mat);

void fMatrix_scale(fMatrix *mat, float scalar);

void fMatrix_print(fMatrix *mat);

#endif
