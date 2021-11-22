#include "ImageBMP.h"
#include <string.h>

static const size_t FILE_HEADER_SIZE = 14;

struct Image_BMP openImageBMP(const char* path) 
{
	struct Image_BMP image = {.width = 0, .height = 0, .file_header = NULL, .bitmap_header = NULL, .pixels = NULL};
	FILE* img = fopen(path, "rb");
	if (img) {
		image.file_header = (unsigned char*) malloc(FILE_HEADER_SIZE * sizeof(unsigned char));
		if (!image.file_header) {
			return image;
		}
		
		int n = fread(image.file_header, sizeof(unsigned char), FILE_HEADER_SIZE, img);
		if (n != FILE_HEADER_SIZE) {
			free(image.file_header);
			image.file_header = NULL;
			return image;
		}
		
		int pixel_array_offset = *(int*)&image.file_header[10];
		image.bitmap_header = (unsigned char*) malloc((pixel_array_offset - FILE_HEADER_SIZE) * sizeof(unsigned char));
		if (!image.bitmap_header) {
			free(image.file_header);
			image.file_header = NULL;
			return image;
		}
		
		n = fread(image.bitmap_header, sizeof(unsigned char), pixel_array_offset - FILE_HEADER_SIZE, img);
		if (n != pixel_array_offset - FILE_HEADER_SIZE) {
			free(image.file_header);
			image.file_header = NULL;
			free(image.bitmap_header);
			image.bitmap_header = NULL;
			return image;
		}
		image.width = *(int*)&image.bitmap_header[4];
		image.height = *(int*)&image.bitmap_header[8];

		image.pixels = (struct Pixel*) malloc(image.width * image.height * sizeof(struct Pixel));
		if (!image.pixels) {
			free(image.file_header);
			image.file_header = NULL;
			free(image.bitmap_header);
			image.bitmap_header = NULL;
			return image;
		}
		short bpp = *(short*)&image.bitmap_header[14];
		long int padding = ceil(bpp * image.width / 32.0) * 4 - image.width * bpp /  8;
		for (size_t row = 0; row < image.height; ++row) {
			for (size_t col = 0; col < image.width; ++col) {
				unsigned char *pixel_component = (unsigned char*) &image.pixels[row * image.width + col];
				n = fread(pixel_component, sizeof(unsigned char), bpp / 8, img);
				if (n != bpp / 8) {
					free(image.file_header);
					image.file_header = NULL;
					free(image.bitmap_header);
					image.bitmap_header = NULL;
					free(image.pixels);
					image.pixels = NULL;
					image.width = 0;
					image.height = 0;
					return image;
				}
			}
			fseek(img, padding, SEEK_CUR);
		}
		
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
	if (!dest) {
		return false;
	}
	fwrite(image->file_header, sizeof(unsigned char), FILE_HEADER_SIZE, dest);
	fwrite(image->bitmap_header, sizeof(unsigned char), *(int*)&image->bitmap_header[0], dest);
	
	short bpp = *(short*)&image->bitmap_header[14];
	
	size_t padding = ceil(bpp * image->width / 32.0) * 4 - image->width * bpp /  8;
	unsigned char *buffer = (unsigned char*) malloc(padding * sizeof(unsigned char));
	for (size_t i = 0; i < padding; ++i) {
		buffer[i] = 0;
	}

	for (size_t row = 0; row < image->height; ++row) {
		for (size_t col = 0; col < image->width; ++col) {
			unsigned char *pixel = (unsigned char*)&image->pixels[row * image->width + col];
			fwrite(pixel, sizeof(unsigned char), bpp / 8, dest);	
		}
		fwrite(buffer, sizeof(unsigned char), padding, dest);
	}
	return true;
}

void dispose_ImageBMP(struct Image_BMP* image) {
	image->width = 0;
	image->height = 0;
	free(image->file_header);
	image->file_header = NULL;
	free(image->bitmap_header);
	image->bitmap_header = NULL;
	free(image->pixels);
	image->pixels = NULL;
}

struct Image_BMP convolution(struct Image_BMP* image, struct fMatrix* kernel) {
	struct Image_BMP convolved_image = {.width = 0, .height = 0, .file_header = NULL, .bitmap_header = NULL, .pixels = NULL};

	if (kernel->rows % 2 == 0 || kernel->cols % 2 == 0) {
		return convolved_image;
	}
	
	convolved_image.file_header = (unsigned char*) malloc(FILE_HEADER_SIZE * sizeof(unsigned char));
	if (!convolved_image.file_header) {
		return convolved_image;
	}

	convolved_image.width = image->width;
	convolved_image.height = image->height;
	memcpy(convolved_image.file_header, image->file_header, FILE_HEADER_SIZE * sizeof(unsigned char));

	int pixel_array_offset = *(int*)&image->file_header[10];
	convolved_image.bitmap_header = (unsigned char*) malloc((pixel_array_offset - FILE_HEADER_SIZE) * sizeof(unsigned char));
	
	if (!convolved_image.bitmap_header) {
		free(convolved_image.file_header);
		convolved_image.file_header = NULL;
		convolved_image.width = 0;
	convolved_image.height = 0;
		return convolved_image;
	}
	memcpy(convolved_image.bitmap_header, image->bitmap_header, (pixel_array_offset - FILE_HEADER_SIZE) * sizeof(unsigned char));
	
	short bpp = *(short*)&image->bitmap_header[14];
	
	convolved_image.pixels = (struct Pixel*) malloc(convolved_image.width * convolved_image.height * sizeof(struct Pixel));
	if (!convolved_image.pixels) {
		free(convolved_image.file_header);
		convolved_image.file_header = NULL;
		free(convolved_image.bitmap_header);
		convolved_image.bitmap_header = NULL;
		convolved_image.width = 0;
		convolved_image.height = 0;
		return convolved_image;
	}
	memset(convolved_image.pixels, 255, convolved_image.width * convolved_image.height * sizeof(struct Pixel));
	printf("starting convolution\n");
	
	float *accumulator = (float*) malloc(bpp * sizeof(float) / 8);
	
	for (int row = 0; row < image->height; ++row)
	{
		for (int col = 0; col < image->width; ++col)
		{
			for (int i = 0; i < bpp / 8; ++i) {
				accumulator[i] = 0.0f;
			}
			
			for (int i = 0; i < kernel->rows; ++i)
			{
				for (int j = 0; j < kernel->cols; ++j)
				{
					int adjusted_row = row + i - (kernel->rows / 2);
					int adjusted_col = col + j - (kernel->cols / 2);
					if (adjusted_row >= 0 && adjusted_row < image->height && adjusted_col >= 0 && adjusted_col < image->width)
 					{
						unsigned char *src_pixel = (unsigned char*) getPixelAt(image, adjusted_col, adjusted_row);
						for (int k = 0; k < bpp / 8; ++k) {
							accumulator[k] += src_pixel[k] * fMatrix_get(kernel, i, j);
						}
					}
				}	
			}
			unsigned char *dest_pixel = (unsigned char*) getPixelAt(&convolved_image, col, row);
			for (int i = 0; i < bpp / 8; ++i) {
				dest_pixel[i] = accumulator[i];
			}

		}
	}
	printf("Finished convolution\n");
	return convolved_image;
}