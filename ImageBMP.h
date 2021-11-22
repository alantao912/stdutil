#ifndef STDUTIL_IMAGEBMP_H
#define STDUTIL_IMAGEBMP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "Matrix.h"

struct Pixel {
	unsigned char R, G, B, A;
};

struct Image_BMP {
	size_t width, height;
	unsigned char *file_header, *bitmap_header;
	struct Pixel* pixels;
};

struct Image_BMP openImageBMP(const char* path);

struct Pixel* getPixelAt(struct Image_BMP* image, unsigned int col, unsigned int row);

bool save_ImageBMP(struct Image_BMP* image, const char* location);

void dispose_ImageBMP(struct Image_BMP* image);

struct Image_BMP convolution(struct Image_BMP* image, struct fMatrix* kernel);

#endif