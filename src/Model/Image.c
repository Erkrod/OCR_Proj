#include "Image.h"
#include <stdlib.h>
#include <assert.h>

/*Get the color intensity of the Red channel of pixel (x, y) in image */
unsigned char GetPixelR(IMAGE *image, unsigned int x,  unsigned int y)
{
	assert(image);
	assert(image->R);
	assert(image->G);
	assert(image->B);
	assert(x<=image->Width);
	assert(y<=image->Height);

	return image->R[x + y * image->Width];
}

/*Get the color intensity of the Green channel of pixel (x, y) in image */
unsigned char GetPixelG(IMAGE *image, unsigned int x,  unsigned int y)
{
	assert(image);
	assert(image->R);
	assert(image->G);
	assert(image->B);
	assert(x<=image->Width);
	assert(y<=image->Height);

	return image->G[x + y * image->Width];
}

/*Get the color intensity of the Blue channel of pixel (x, y) in image */
unsigned char GetPixelB(IMAGE *image, unsigned int x,  unsigned int y)
{
	assert(image);
	assert(image->R);
	assert(image->G);
	assert(image->B);
	assert(x<=image->Width);
	assert(y<=image->Height);

	return image->B[x + y * image->Width];
}

/*Set the color intensity of the Red channel of pixel (x, y) in image with value r*/
void SetPixelR(IMAGE *image, unsigned int x,  unsigned int y, unsigned char r)
{
	assert(image);
	assert(image->R);
	assert(image->G);
	assert(image->B);
	assert(x<=image->Width);
	assert(y<=image->Height);

	image->R[x + y * image->Width] = r;
}

/*Set the color intensity of the Green channel of pixel (x, y) in image with value g */
void SetPixelG(IMAGE *image, unsigned int x,  unsigned int y, unsigned char g)
{
	assert(image);
	assert(image->R);
	assert(image->G);
	assert(image->B);
	assert(x<=image->Width);
	assert(y<=image->Height);

	image->G[x + y * image->Width] = g;
}

/*Set the color intensity of the Blue channel of pixel (x, y) in image with value b */
void SetPixelB(IMAGE *image, unsigned int x,  unsigned int y, unsigned char b)
{	
	assert(image);
	assert(image->R);
	assert(image->G);
	assert(image->B);
	assert(x<=image->Width);
	assert(y<=image->Height);

	image->B[x + y * image->Width] = b;
}

/* allocate the memory spaces for the image              */
/* and the memory spaces for the color intensity values. */
/* return the pointer to the image                       */
IMAGE *CreateImage(unsigned int Width, unsigned int Height)
{
	IMAGE *image;
	if(!( image = (IMAGE *)malloc(sizeof(IMAGE)))){
		return NULL;
	}
	image->Width 	= Width;
	image->Height 	= Height;
	if(!(image->R = (unsigned char*)malloc(Width * Height * sizeof(unsigned char)))){
			return NULL;
	}
	if(!(image->G = (unsigned char*)malloc(Width * Height * sizeof(unsigned char)))){
			return NULL;
	}
	if(!(image->B = (unsigned char*)malloc(Width * Height * sizeof(unsigned char)))){
			return NULL;
	}
	return image;
}

/*release the memory spaces for the pixel color intensity values */
/*release the memory spaces for the image                        */
/*set the image pointer to be NULL                               */
void DeleteImage(IMAGE *image)
{
	assert(image);
	assert(image->R);
	assert(image->G);
	assert(image->B);
		
	free(image->R);
	free(image->G);
	free(image->B);
	image->R = NULL;
	image->G = NULL;
	image->B = NULL;
		
	free(image);
}
