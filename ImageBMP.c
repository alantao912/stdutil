#include "ImageBMP.h"

struct Image_BMP openImageBMP(const char* path) 
{
	struct Image_BMP image = {.width = 0, .height = 0, .header = NULL, .color_table = NULL, .pixels = NULL};
	FILE* img = fopen(path, "rb");

	if(img != NULL) 
	{
		
		image.header_size = 54;
		image.header = (unsigned char*) malloc(image.header_size * sizeof(unsigned char));

		if(image.header == NULL)
			return image;


		fread(image.header, sizeof(unsigned char), image.header_size, img);
		image.header_size += *(int*) &image.header[14] - 40;

		if(image.header_size > 54)
		{
			unsigned char *new_mem = (char*) realloc(image.header, image.header_size * sizeof(unsigned char));
			if(new_mem == NULL)
			{
				free(image.header);
				image.header = NULL;
				image.header_size = 0;
				return image;
			}
			image.header = new_mem;
			unsigned int nmemb = *(int*) &image.header[14] - 40;
			fread(&(image.header[54]), sizeof(unsigned char), nmemb, img);
		}
		

		image.width = *(int*) &image.header[18];
		image.height = *(int*) &image.header[22];
		image.BPP = *(short*) &image.header[28];
		image.colortable_size = 4 * (*(int*) &image.header[46]);

		{
			unsigned int compression = *(int*) &image.header[30];
			if(compression == 3)
				image.colortable_size += 12;
			else if(compression == 6)
				image.colortable_size += 16;
		}

		image.color_table = (unsigned char*) malloc(image.colortable_size * sizeof(unsigned char));
		if(image.color_table == NULL) 
		{
			free(image.header);
			image.header = NULL;
			image.header_size = 0;
			image.colortable_size = 0;
			image.width = 0;
			image.height = 0;
			image.BPP = 0;
			return image;
		}
		fread(image.color_table, sizeof(unsigned char), image.colortable_size, img);


		image.pixels = (struct Pixel*) malloc(image.width * image.height * sizeof(struct Pixel));
		if(image.pixels == NULL) {
			free(image.header);
			image.header = NULL;
			image.header_size = 0;
			free(image.color_table);
			image.color_table = NULL;
			image.colortable_size = 0;
	
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
	unsigned int index = row * image->width + image->width - col;
	return &(image->pixels[num_pixels - 1 - row * image->width - image->width + col]);
}

bool save_ImageBMP(struct Image_BMP* image, const char* location) {
	FILE* dest = fopen(location, "wb");
	if(image->header == NULL || (image->colortable_size > 0 && image->color_table == NULL) || image->pixels == NULL || dest == NULL)
		return false;

	fwrite(image->header, sizeof(unsigned char), image->header_size, dest);


	fwrite(image->color_table, sizeof(unsigned char), image->colortable_size, dest);
	
	for(unsigned int i = 0; i < image->width * image->height; ++i)
		fwrite(&(image->pixels[i]), image->BPP/8, 1, dest);

	unsigned int padding_size = 4 - ((image->BPP/8) * image->width % 4);
	if(padding_size == 4)
		padding_size = 0;

	unsigned char* padding = (unsigned char*) malloc(padding_size);
	memset(padding, 0, padding_size);

	fwrite(padding, padding_size, image->height, dest);
	free(padding);	
	
	return true;
}

void dispose_ImageBMP(struct Image_BMP* image) {
	image->width = 0;
	image->height = 0;
	image->BPP = 0;
	image->header_size = 0;
	image->colortable_size = 0;
	
	free(image->header);
	image->header = NULL;
	free(image->color_table);
	image->color_table = NULL;
	free(image->pixels);
	image->pixels = NULL;	
}