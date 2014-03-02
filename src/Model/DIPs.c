/*********************************************************************/
/* DIPs.c: homework assignment #3, for EECS 22,Fall 2011		*/
/* */
/* History:*/
/* 10/30/12 Weiwei Chen: Add Mandelbrot							 */
/*						 for EECS22 assignment5 Fall2012			 */
/* 10/07/11 Weiwei Chenupdated for EECS22 assignment3 FAll2011 */
/*							initial version			 */
/*********************************************************************/

#include "DIPs.h"

/*Duplicate image*/

IMAGE * DuplicateImage(IMAGE * image){
	IMAGE * NewImage = CreateImage(image->Width, image->Height);
	int i, j;
	for (i = 0; i < image->Width; i++){
		for (j = 0; j < image->Height; j++){
			SetPixelR(NewImage, i, j, GetPixelR(image, i, j));
			SetPixelG(NewImage, i, j, GetPixelG(image, i, j));
			SetPixelB(NewImage, i, j, GetPixelB(image, i, j));
		}
	}
	
	return NewImage;
}

/* reverse image color */
void BlackNWhite(IMAGE *image)
{
	int x, y;
	unsigned int WIDTH;
	unsigned int HEIGHT;
	unsigned int tmp;

	assert(image);
	WIDTH	= image->Width;
	HEIGHT = image->Height;

	for (y = 0; y < HEIGHT; y++)
		for (x = 0; x < WIDTH; x++) {
			tmp = (GetPixelR(image, x, y) + GetPixelG(image, x, y) + GetPixelB(image, x, y)) / 3;
			SetPixelR(image, x, y, tmp);
			SetPixelG(image, x, y, tmp);
			SetPixelB(image, x, y, tmp);
		}
}

/* flip image vertically */
void VFlip(IMAGE *image)
{
	int x, y;
	unsigned char r, g, b;
	unsigned int WIDTH;
	unsigned int HEIGHT;

	assert(image);
	WIDTH	= image->Width;
	HEIGHT = image->Height;

	for (y = 0; y < HEIGHT/2; y++) {
		for (x = 0; x < WIDTH; x++) {
			r = GetPixelR(image, x, HEIGHT - 1 - y);
			g = GetPixelG(image, x, HEIGHT - 1 - y);
			b = GetPixelB(image, x, HEIGHT - 1 - y);

			SetPixelR(image, x, HEIGHT - 1 - y, GetPixelR(image, x, y));
			SetPixelG(image, x, HEIGHT - 1 - y, GetPixelG(image, x, y));
			SetPixelB(image, x, HEIGHT - 1 - y, GetPixelB(image, x, y));

			SetPixelR(image, x, y, r);
			SetPixelG(image, x, y, g);
			SetPixelB(image, x, y, b);
		}
	}	
}

/* mirror image horizontally */
void HMirror(IMAGE *image)
{
	int x, y;
	unsigned int WIDTH;
	unsigned int HEIGHT;

	assert(image);
	WIDTH	 = image->Width;
	HEIGHT = image->Height;

	for (y = 0; y < HEIGHT; y++) {
		for (x = 0; x < WIDTH / 2; x++) {
			SetPixelR(image, x, y, GetPixelR(image, WIDTH - 1 - x, y));
			SetPixelG(image, x, y, GetPixelG(image, WIDTH - 1 - x, y));
			SetPixelB(image, x, y, GetPixelB(image, WIDTH - 1 - x, y));
		}
	}
}

/* sharpen the image */
void Sharpen(IMAGE *image)
{
	int x, y, m, n, a, b;
	int tmpR = 0;
	int tmpG = 0;
	int tmpB = 0;
	unsigned int WIDTH;
	unsigned int HEIGHT;

	assert(image);
	WIDTH	 = image->Width;
	HEIGHT = image->Height;

	IMAGE *image_tmp = CreateImage(WIDTH, HEIGHT);

	for (y = 0; y < HEIGHT; y++)
		for (x = 0; x < WIDTH; x++) {
			SetPixelR(image_tmp, x, y, GetPixelR(image, x, y));
			SetPixelG(image_tmp, x, y, GetPixelG(image, x, y));
			SetPixelB(image_tmp, x, y, GetPixelB(image, x, y));
		}

	for (y = 0; y < HEIGHT; y++)
		for (x = 0; x < WIDTH; x++) 
		{
			for (n = -1; n <= 1; n++)
			{
				for (m = -1; m <= 1; m++)
				{
					a = x + m;
					b = y + n;
					if (a > WIDTH - 1)
						a = WIDTH - 1;
					if (a < 0)
						a = 0;
					if (b > HEIGHT - 1)
						b = HEIGHT - 1;
					if (b < 0)
						b = 0;
					
					if ((n==0)&&(m==0))
					{
						tmpR += 9*GetPixelR(image_tmp, a, b);
						tmpG += 9*GetPixelG(image_tmp, a, b);
						tmpB += 9*GetPixelB(image_tmp, a, b);
					}
					else
					{
						tmpR -= GetPixelR(image_tmp, a, b);
						tmpG -= GetPixelG(image_tmp, a, b);
						tmpB -= GetPixelB(image_tmp, a, b);
					}
				}
			}	

		SetPixelR(image, x, y, ((tmpR > 255)? 255 : (tmpR <0)? 0 : tmpR));
		SetPixelG(image, x, y, ((tmpG > 255)? 255 : (tmpG <0)? 0 : tmpG));
		SetPixelB(image, x, y, ((tmpB > 255)? 255 : (tmpB <0)? 0 : tmpB));

		tmpR = tmpG = tmpB = 0; 
		}

	DeleteImage(image_tmp);
}

/* Find the edges in the image */
void Edge(IMAGE *image)
{
	int	x, y, m, n, a, b;
	int	tmpR = 0;
	int	tmpG = 0;
	int	tmpB = 0;
	unsigned int WIDTH;
	unsigned int HEIGHT;
	IMAGE *image_tmp;

	assert(image);
	WIDTH  = image->Width;
	HEIGHT = image->Height;

	image_tmp = CreateImage(WIDTH, HEIGHT);

	for (y = 0; y < HEIGHT; y++)
		for (x = 0; x < WIDTH; x++) {
			SetPixelR(image_tmp, x, y, GetPixelR(image, x, y));
			SetPixelG(image_tmp, x, y, GetPixelG(image, x, y));
			SetPixelB(image_tmp, x, y, GetPixelB(image, x, y));
		}

	for (y = 0; y < HEIGHT; y++)
		for (x = 0; x < WIDTH; x++) 
		{
			for (n = -1; n <= 1; n++)
				for (m = -1; m <= 1; m++)
				{
					a = x + m;
					b = y + n;
					if (a > WIDTH - 1)
						a = WIDTH - 1;
					if (a < 0)
						a = 0;
					if (b > HEIGHT - 1)
						b = HEIGHT - 1;
					if (b < 0)
						b = 0;

					if ((n==0)&&(m==0))
					{
						tmpR += 8*GetPixelR(image_tmp, a, b);
						tmpG += 8*GetPixelG(image_tmp, a, b);
						tmpB += 8*GetPixelB(image_tmp, a, b);
					}
					else
					{
						tmpR -= GetPixelR(image_tmp, a, b);
						tmpG -= GetPixelG(image_tmp, a, b);
						tmpB -= GetPixelB(image_tmp, a, b);
					}
				}
		SetPixelR(image, x, y, ((tmpR > 255)? 255 : (tmpR <0)? 0 : tmpR));
		SetPixelG(image, x, y, ((tmpG > 255)? 255 : (tmpG <0)? 0 : tmpG));
		SetPixelB(image, x, y, ((tmpB > 255)? 255 : (tmpB <0)? 0 : tmpB));

		tmpR = tmpG = tmpB = 0;
		}

	DeleteImage(image_tmp);
}

/* Posterization */
void Posterize(IMAGE *image)
{

	unsigned char maskzero[8]={0xff-0x1, 0xff-0x2, 0xff-0x4, 0xff-0x8, 0xff-0x10, 0xff-0x20, 0xff-0x40, 0xff-0x80};
	unsigned char maskone[8]={0x0, 0x1, 0x3, 0x7, 0xf, 0x1f, 0x3f, 0x7f};
	int x, y;
	unsigned r, g, b;

	assert(image);

	for(x = 0; x < image->Width; x ++)
	{
		for(y = 0; y < image->Height; y ++)
		{
			r = GetPixelR(image, x, y);
			r &= maskzero[5];
			r |= maskone[5];
			SetPixelR(image, x, y, r);

			g = GetPixelG(image, x, y);
			g &= maskzero[5];
			g |= maskone[5];
			SetPixelG(image, x, y, g);

			b = GetPixelB(image, x, y);
			b &= maskzero[5];
			b |= maskone[5];
			SetPixelB(image, x, y, b);
		}
	}
}

/* add noise to image */
void AddNoise(IMAGE *image)
{
	int x, y, i;
	int num; /* number of noise added */

	assert(image);

	num = (20*image->Height*image->Width )/100;

	for ( i = 0; i < num; i++ )
	{
		x = ( (double)rand()/RAND_MAX )*(image->Width-1);
		y = ( (double)rand()/RAND_MAX )*(image->Height-1);
		SetPixelR(image, x, y, 255);
		SetPixelG(image, x, y, 255);
		SetPixelB(image, x, y, 255);
	}
}


/* Resize */
IMAGE* Resize(unsigned int percentage, IMAGE *image)
{
	unsigned int x, y, x1, y1, x2, y2, i, j, tmpR, tmpG, tmpB;
	unsigned int NEW_WIDTH, NEW_HEIGHT;
	unsigned int WIDTH;
	unsigned int HEIGHT;
	IMAGE *image_tmp;

	assert(image);
	WIDTH	 = image->Width;
	HEIGHT = image->Height;

	if(percentage <= 0 || percentage > 500){
		printf("Resizing percentage %d%% is out of the range, Sorry! \n", percentage);
		return image;
	}

	NEW_WIDTH = WIDTH * percentage / 100;
	NEW_HEIGHT = HEIGHT * percentage / 100;
	image_tmp = CreateImage(NEW_WIDTH, NEW_HEIGHT);
	
	if (image_tmp != NULL)
	{
		for(x = 0; x < NEW_WIDTH; x ++){
			for(y = 0; y < NEW_HEIGHT; y++){
				x1 = (unsigned int)(x / (percentage / 100.00));
				y1 = (unsigned int)(y / (percentage / 100.00));
				x2 = (unsigned int)((x + 1) / (percentage / 100.00));
				y2 = (unsigned int)((y + 1) / (percentage / 100.00));
				tmpR = tmpB = tmpG = 0;
				
				if(percentage < 100){
					for(i = x1; i < x2; i ++){
						for(j = y1; j < y2; j ++){
							tmpR += GetPixelR(image, i, j);
							tmpG += GetPixelG(image, i, j);
							tmpB += GetPixelB(image, i, j);
						}
					}
					SetPixelR(image_tmp, x, y, tmpR / ((x2 - x1) * (y2 - y1)));
					SetPixelG(image_tmp, x, y, tmpG / ((x2 - x1) * (y2 - y1)));
					SetPixelB(image_tmp, x, y, tmpB / ((x2 - x1) * (y2 - y1)));
  	
				}
				else{
					SetPixelR(image_tmp, x, y, GetPixelR(image, x1, y1));
					SetPixelG(image_tmp, x, y, GetPixelG(image, x1, y1));
					SetPixelB(image_tmp, x, y, GetPixelB(image, x1, y1));
				}
			}
		}
	}
	
	DeleteImage(image);
	return image_tmp ; 
}