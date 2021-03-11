#ifndef STDUTIL_IMAGEBMP_H
#define STDUTIL_IMAGEBMP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static const unsigned int COLORTABLESIZE = 1024, HEADERSIZE = 54;

struct Pixel {
	unsigned char B, G, R, A;
};

struct Image_BMP {
	size_t width, height, BPP;
	unsigned char *header, *color_table;
	struct Pixel* pixels;
};

struct Image_BMP openImageBMP(const char* path);

struct Pixel* getPixelAt(struct Image_BMP* image, unsigned int col, unsigned int row);

bool save_ImageBMP(struct Image_BMP* image, const char* location);

void dispose_ImageBMP(struct Image_BMP* image);

#endif