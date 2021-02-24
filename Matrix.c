#include "Matrix.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct fMatrix create_fMatrix(size_t num_rows, size_t num_cols) {
	struct fMatrix matrix = {.elements = NULL, .rows = -1, .cols = -1};
	matrix.elements = malloc(num_rows * num_cols * sizeof(float));
	if(matrix.elements != NULL) {
		matrix.rows = num_rows;
		matrix.cols = num_cols;
	}
	return matrix;
}

float fMatrix_get(struct fMatrix* mat, size_t row, size_t col) {
	return mat->elements[row * mat->rows + col];
}

bool fMatrix_set(struct fMatrix* mat, size_t row, size_t col, float data) {
	if(row < mat->rows && col < mat->cols) {
		mat->elements[row * mat->cols + col] = data;
		return true;
	} else
		return false;	
}

struct fMatrix fMatrix_multiply(struct fMatrix lmat, struct fMatrix rmat) {
	struct fMatrix matrix = {.elements = NULL, .rows = -1, .cols = -1};
	if(lmat.cols == rmat.rows) {
		matrix.elements = malloc(lmat.rows * rmat.cols * sizeof(float));
		if(matrix.elements == NULL)
			return matrix;
		matrix.rows = lmat.rows;
		matrix.cols = rmat.cols;

		for(size_t i = 0; i < matrix.rows * matrix.cols; ++i) {
			size_t r = i / matrix.cols, c = i % matrix.cols;
			float accumulator = 0;
			for(size_t j = 0; j < lmat.cols; ++j)
				accumulator += lmat.elements[r * lmat.cols + j] * rmat.elements[j * rmat.cols + c];
			matrix.elements[i] = accumulator;
		}
		
	}
	return matrix;
}

struct fMatrix fMatrix_add(struct fMatrix lmat, struct fMatrix rmat) {
	struct fMatrix sum = {.elements = NULL, .rows = -1, .cols = -1};
	if(lmat.cols == rmat.cols && lmat.rows == rmat.rows) {
		sum.elements = malloc(lmat.rows * lmat.cols * sizeof(float));
		if(sum.elements == NULL)
			return sum;				
		sum.rows = lmat.rows;
		sum.cols = lmat.cols;
		for(size_t i = 0; i < lmat.cols * lmat.rows; ++i)
			sum.elements[i] = lmat.elements[i] + rmat.elements[i];
	}
	return sum;
}

void fMatrix_scale(struct fMatrix* mat, float scalar) {
	for(size_t i = 0; i < mat->cols * mat->rows; ++i) 
		mat->elements[i] *= scalar;
}

void fMatrix_invert(struct fMatrix* mat) {
	
}

void fMatrix_print(struct fMatrix* mat) {
	char useless_buffer[16];
	signed char max_length[mat->cols];

	for(size_t i = 0; i < mat->cols; ++i) {
		max_length[i] = 0;
		for(size_t j = 0; j < mat->rows; ++j) {
			signed char length = (signed char)sprintf(useless_buffer, "%f", mat->elements[j * mat->cols + i]);
			if(length > max_length[i])
				max_length[i] = length;
		}
	}
	for(size_t i = 0; i < mat->rows; ++i) {
		printf("[ ");
		for(size_t j = 0; j < mat->cols - 1; ++j) {
			signed char length = (signed char)sprintf(useless_buffer, "%f", mat->elements[i * mat->cols + j]);
			for(signed char k = 0; k < max_length[i] - length; ++k)
				printf(" ");
			printf("%.2f, ", mat->elements[i * mat->cols + j]);
		}
		signed char length = (signed char)sprintf(useless_buffer, "%f", mat->elements[mat->cols * (i + 1) - 1]);
		for(signed char k = 0; k < max_length[i] - length; ++k)
			printf(" ");
		printf("%.2f]\n", mat->elements[mat->cols * (i + 1) - 1]);


	}
}