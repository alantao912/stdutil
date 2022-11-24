#include "matrix.h"

fMatrix create_fMatrix(size_t num_rows, size_t num_cols) {
	fMatrix matrix = {.elements = NULL, .rows = -1, .cols = -1};
	matrix.elements = (float *) malloc(num_rows * num_cols * sizeof(float));
	if (matrix.elements != NULL) {
		matrix.rows = num_rows;
		matrix.cols = num_cols;
		for (size_t i = 0; i < matrix.rows; ++i) {
			for (size_t j = 0; j < matrix.cols; ++j) {
				if (i == j) {
					matrix.elements[i * matrix.cols + j] = 1.0f;
				} else {
					matrix.elements[i * matrix.cols + j] = 0.0f;
				}
			}
		}
	}
	return matrix;
}

float fMatrix_get(fMatrix *mat, size_t row, size_t col) {
	return mat->elements[row * mat->rows + col];
}

bool fMatrix_set(fMatrix *mat, size_t row, size_t col, float data) {
	if (row < mat->rows && col < mat->cols) {
		mat->elements[row * mat->cols + col] = data;
		return true;
	} else {
		return false;
	}
}

fMatrix fMatrix_multiply(fMatrix lmat, fMatrix rmat) {
	fMatrix matrix = {.elements = NULL, .rows = -1, .cols = -1};
	if (lmat.cols == rmat.rows) {
		matrix.elements = malloc(lmat.rows * rmat.cols * sizeof(float));
		if (matrix.elements == NULL) {
			return matrix;
		}
		matrix.rows = lmat.rows;
		matrix.cols = rmat.cols;
		for (size_t i = 0; i < matrix.rows * matrix.cols; ++i) {
			size_t r = i / matrix.cols, c = i % matrix.cols;
			float accumulator = 0;
			for (size_t j = 0; j < lmat.cols; ++j) {
				accumulator += lmat.elements[r * lmat.cols + j] * rmat.elements[j * rmat.cols + c];
			}
			matrix.elements[i] = accumulator;
		}
	}
	return matrix;
}

fMatrix fMatrix_add(fMatrix lmat, fMatrix rmat) {
	fMatrix sum = {.elements = NULL, .rows = -1, .cols = -1};
	if (lmat.cols == rmat.cols && lmat.rows == rmat.rows) {
		sum.elements = calloc(lmat.rows * lmat.cols, sizeof(float));
		if (sum.elements == NULL) {
			return sum;	
		}			
		sum.rows = lmat.rows;
		sum.cols = lmat.cols;
		for (size_t i = 0; i < lmat.cols * lmat.rows; ++i) {
			sum.elements[i] = lmat.elements[i] + rmat.elements[i];
		}
	}
	return sum;
}

static fMatrix *createSubMatrix(fMatrix *parent, size_t row, size_t col) {
	fMatrix *subMatrix = (fMatrix*) malloc(sizeof(fMatrix));
	subMatrix->rows = parent->rows - 1;
	subMatrix->cols = parent->cols - 1;
	subMatrix->elements = (float*) malloc(subMatrix->rows * subMatrix->cols * sizeof(float));
	for (unsigned int i = 0; i < parent->rows; ++i) {
		if (i == row) {
			continue;
		}
		int y_offset = 0;
		if (i > row) {
			y_offset = 1;
		}

		for (unsigned int j = 0; j < parent->cols; ++j) {
			if (j == col) {
				continue;
			}
			int x_offset = 0;	
			if (j > col) {
				x_offset = 1;
			}
			fMatrix_set(subMatrix, i - y_offset, j - x_offset, fMatrix_get(parent, i, j));
		}
	}
	return subMatrix;
}

float fMatrix_determinant(fMatrix *mat) {
	if (mat->rows != mat->cols) {
		return 0.0f;
	}
	if (mat->rows == 1) {
		return mat->elements[0];
	}
	bool isNegative = false;
	float determinant = 0.0f;
	for (size_t i = 0; i < mat->cols; ++i) {
		fMatrix *subMatrix = createSubMatrix(mat, 0, i);
		float term = fMatrix_get(mat, 0, i) * fMatrix_determinant(subMatrix);
		free(subMatrix);

		if (isNegative) {
			determinant -= term;
		} else {
			determinant += term;
		}
		isNegative = !isNegative;
	}
	return determinant;
}

void fMatrix_scale(fMatrix *mat, float scalar) {
	for (size_t i = 0; i < mat->cols * mat->rows; ++i) {
		mat->elements[i] *= scalar;
	}
}

void fMatrix_print(fMatrix *mat) {
	char useless_buffer[16];
	signed char max_length[mat->cols];

	for (size_t i = 0; i < mat->cols; ++i) {
		max_length[i] = 0;
		for (size_t j = 0; j < mat->rows; ++j) {
			signed char length = (signed char)sprintf(useless_buffer, "%f", mat->elements[j * mat->cols + i]);
			if (length > max_length[i]) {
				max_length[i] = length;
			}
		}
	}
	for (size_t i = 0; i < mat->rows; ++i) {
		printf("[ ");
		for (size_t j = 0; j < mat->cols - 1; ++j) {
			signed char length = (signed char) sprintf(useless_buffer, "%f", mat->elements[i * mat->cols + j]);
			for (signed char k = 0; k < max_length[i] - length; ++k) {
				printf(" ");
			}
			printf("%.2f, ", mat->elements[i * mat->cols + j]);
		}
		signed char length = (signed char) sprintf(useless_buffer, "%f", mat->elements[mat->cols * (i + 1) - 1]);
		for (signed char k = 0; k < max_length[i] - length; ++k) {
			printf(" ");
		}
		printf("%.2f]\n", mat->elements[mat->cols * (i + 1) - 1]);
	}
}
