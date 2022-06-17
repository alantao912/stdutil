#ifndef STDUTIL_IMAGEBMP_H
#define STDUTIL_IMAGEBMP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "Matrix.h"

typedef struct pixel {
	unsigned char R, G, B, A;
} pixel;

typedef struct bmp_image {
	size_t width, height, trailer_size;
	unsigned char *file_header, *bitmap_header, *trailer;
	pixel* pixels;
} bmp_image;

bmp_image openImageBMP(const char *path);

pixel* getPixelAt(bmp_image *image, unsigned int col, unsigned int row);

bool save_ImageBMP(bmp_image *image, const char *location);

void dispose_ImageBMP(bmp_image *image);

bmp_image convolution(bmp_image *image, struct fMatrix *kernel);

#endif