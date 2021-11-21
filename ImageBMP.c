#include "ImageBMP.h"

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

int main() {
	struct Image_BMP tank = openImageBMP("C:\\Users\\Alan Tao\\Pictures\\pictures\\tank.bmp");
	for (size_t row = 0; row < tank.height; ++row) {
		for (size_t col = 0; col < tank.width; ++col) {
			if ((row + col) % 2 == 0) {
				struct Pixel *p = getPixelAt(&tank, col, row);
				p->R ^= 255;
				p->G ^= 255;
				p->B ^= 255;
			}	
		}
	}
	save_ImageBMP(&tank, "C:\\Users\\Alan Tao\\Pictures\\pictures\\tank1.bmp");
	dispose_ImageBMP(&tank);
	tank = openImageBMP("C:\\Users\\Alan Tao\\Pictures\\pictures\\bmp.bmp");
	for (size_t row = 0; row < tank.height; ++row) {
		for (size_t col = 0; col < 5 * row && col < tank.width; ++col) {
			{
				struct Pixel *p = getPixelAt(&tank, col, row);
				p->R ^= 255;
				p->G ^= 255;
				p->B ^= 255;
			}	
		}
	}
	save_ImageBMP(&tank, "C:\\Users\\Alan Tao\\Pictures\\pictures\\bmp1.bmp");
	dispose_ImageBMP(&tank);
	tank = openImageBMP("C:\\Users\\Alan Tao\\Pictures\\pictures\\vehicle.bmp");
	for (size_t row = 0; row < tank.height; ++row) {
		for (size_t col = 0; col < tank.width; ++col) {
			if ((row + col) % 2 == 0) {
				struct Pixel *p = getPixelAt(&tank, col, row);
				p->R ^= 255;
				p->G ^= 255;
				p->B ^= 255;
			}	
		}
	}
	save_ImageBMP(&tank, "C:\\Users\\Alan Tao\\Pictures\\pictures\\vehicle1.bmp");
	dispose_ImageBMP(&tank);
	return 0;
}