#ifndef STDUTIL_MATRIX_H
#define STDUTIL_MATRIX_H

#include <stdbool.h>
#include <stddef.h>

struct fMatrix {
	float* elements;
	size_t rows, cols;
};

struct fMatrix create_fMatrix(size_t rows, size_t cols);

float fMatrix_get(struct fMatrix* mat, size_t row, size_t col);

bool fMatrix_set(struct fMatrix* mat, size_t row, size_t col, float data);

struct fMatrix fMatrix_multiply(struct fMatrix lmat, struct fMatrix rmat);

struct fMatrix fMatrix_add(struct fMatrix lmat, struct fMatrix rmat);

float fMatrix_determinant(struct fMatrix* mat);

void fMatrix_scale(struct fMatrix* mat, float scalar);

void fMatrix_print(struct fMatrix* mat);

#endif