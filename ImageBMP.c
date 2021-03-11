#include "ImageBMP.h"

struct Image_BMP openImageBMP(const char* path) {
	struct Image_BMP image = {.width = 0, .height = 0, .header = NULL, .color_table = NULL, .pixels = NULL};
	FILE* img = fopen(path, "rb");
	if(img != NULL) {
		image.header = (unsigned char*) malloc(HEADERSIZE * sizeof(unsigned char));
		if(image.header == NULL)
			return image;
		fread(image.header, sizeof(unsigned char), HEADERSIZE, img);
		image.width = *(int*) &image.header[18];
		image.height = *(int*) &image.header[22];
		image.BPP = *(short*) &image.header[28];
		image.color_table = (unsigned char*) malloc(COLORTABLESIZE * sizeof(unsigned char));
		if(image.color_table == NULL) {
			free(image.header);
			image.header = NULL;
			image.width = 0;
			image.height = 0;
			image.BPP = 0;
			return image;
		}
		fread(image.color_table, sizeof(unsigned char), COLORTABLESIZE, img);
		image.pixels = (struct Pixel*) malloc(image.width * image.height * sizeof(struct Pixel));
		if(image.pixels == NULL) {
			free(image.header);
			image.header = NULL;
			free(image.color_table);
			image.color_table = NULL;
			image.width = 0;
			image.height = 0;
			image.BPP = 0;
			return image;
		}
		for(unsigned int i = 0; i < image.width * image.height; ++i)
			fread(&(image.pixels[i]), image.BPP/8, 1, img);
	}
	return image;
}

struct Pixel* getPixelAt(struct Image_BMP* image, unsigned int col, unsigned int row) {
	unsigned int num_pixels = image->width * image->height;
	unsigned int index = num_pixels - 1 - row * image->width - col;
	return &(image->pixels[index]);
}

bool save_ImageBMP(struct Image_BMP* image, const char* location) {
	FILE* dest = fopen(location, "wb");
	if(image->header == NULL || image->color_table == NULL || image->pixels == NULL || dest == NULL)
		return false;
	fwrite(image->header, sizeof(unsigned char), HEADERSIZE, dest);
	fwrite(image->color_table, sizeof(unsigned char), COLORTABLESIZE, dest);
	
	for(unsigned int i = 0; i < image->width * image->height; ++i)
		fwrite(&(image->pixels[i]), image->BPP/8, 1, dest);
	return true;
}

void dispose_ImageBMP(struct Image_BMP* image) {
	image->width = 0;
	image->height = 0;
	image->BPP = 0;
	free(image->header);
	image->header = NULL;
	free(image->color_table);
	image->color_table = NULL;
	free(image->pixels);
	image->pixels = NULL;	
}