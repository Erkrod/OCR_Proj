/*********************************************************************/
/* DIPs.c: homework assignment #3, for EECS 22,Fall 2011		*/
/* */
/* History:*/
/* 10/30/12 Weiwei Chen: Add Mandelbrot							 */
/*						 for EECS22 assignment5 Fall2012			 */
/* 10/07/11 Weiwei Chenupdated for EECS22 assignment3 FAll2011 */
/*							initial version			 */
/*********************************************************************/

#include "Model.h"

/*rotate*/

IMAGE *Rotate(IMAGE *image, int ClockwiseDegree){
	char command[SLEN * 5] = "pnmrotate -background=rgb:ff/ff/ff ";
	char degrees[4];

	if (ClockwiseDegree == 360)
		return image;


	SaveImage("pre_rot", image);

	while(ClockwiseDegree > 360)
		ClockwiseDegree -= 360;
	if (ClockwiseDegree > 90){
		if (ClockwiseDegree > 180){
			if (ClockwiseDegree > 270){
				if (0 != system("pamflip -ccw pre_rot.ppm > rot_o.ppm; rm pre_rot.ppm; mv rot_o.ppm pre_rot.ppm")) return NULL;
				ClockwiseDegree -= 270;
			}else{
				if (0 != system("pamflip -rotate180 pre_rot.ppm > rot_o.ppm; rm pre_rot.ppm; mv rot_o.ppm pre_rot.ppm")) return NULL;
				ClockwiseDegree -= 180;
			}
		}else{
			if (0 != system("pamflip -cw pre_rot.ppm > rot_o.ppm; rm pre_rot.ppm; mv rot_o.ppm pre_rot.ppm")) return NULL;
			ClockwiseDegree -= 90;
		}
	}

	if (ClockwiseDegree == 90){
		if (0 != system("pamflip -cw pre_rot.ppm > rot_o.ppm; rm pre_rot.ppm")) return NULL;
	}else{
		sprintf(degrees, "%d", ClockwiseDegree * -1);	
		strcat(command, degrees);
		strcat(command, " pre_rot.ppm > rot_o.ppm");
		if (0 != system(command)) return NULL;
		if (0 != system("rm pre_rot.ppm")) {};
	}

	DeleteImage(image);
	image = ReadImage("rot_o.ppm");
	if (0 != system("rm rot_o.ppm")) {};

	return image;

}

/*crop*/
IMAGE *Crop(IMAGE *image, int x1, int y1, int width, int height){
	return CropImage(image, x1, y1, x1+width, y1+height);
}

IMAGE *CropImage(IMAGE *image, int x1, int y1, int x2, int y2){
	
	unsigned W, H;
	int j, x_c, y_c;
	IMAGE *image_tmp;

	assert(image);

	x_c = x1;
	x1 = (x1 < x2) ? x1 : x2;
	x2 = (x_c < x2) ? x2 : x_c;

	y_c = y1;
	y1 = (y1 < y2) ? y1 : y2;
	y2 = (y_c < y2) ? y2 : y_c;

	W = (x2 - x1) + 1;
	H = (y2 - y1) + 1;

	image_tmp = CreateImage(W, H);

#if 0
	int i;
	for (i = x1; i <= x2; i++) {
		for (j = y1; j <= y2; j++) {
				SetPixelR(image_tmp, i-x1, j-y1, GetPixelR(image, i, j));
				SetPixelG(image_tmp, i-x1, j-y1, GetPixelG(image, i, j));
				SetPixelB(image_tmp, i-x1, j-y1, GetPixelB(image, i, j));
		}
	}
#else
	for (j = y1; j <= y2; j++) {
		memcpy(image_tmp->R + (j-y1) * image_tmp->Width, image->R + x1 + j * image->Width, sizeof(unsigned char) * image_tmp->Width);
		memcpy(image_tmp->G + (j-y1) * image_tmp->Width, image->G + x1 + j * image->Width, sizeof(unsigned char) * image_tmp->Width);
		memcpy(image_tmp->B + (j-y1) * image_tmp->Width, image->B + x1 + j * image->Width, sizeof(unsigned char) * image_tmp->Width);
	}
#endif

	/*DeleteImage(image);*/
	image = NULL;
	return image_tmp;
}

/*Duplicate image*/

IMAGE * DuplicateImage(IMAGE * image){
	IMAGE * NewImage = CreateImage(image->Width, image->Height);
	/*int i, j;*/
	memcpy(NewImage->R, image->R, sizeof(unsigned char) * image->Width * image->Height);
	memcpy(NewImage->G, image->G, sizeof(unsigned char) * image->Width * image->Height);
	memcpy(NewImage->B, image->B, sizeof(unsigned char) * image->Width * image->Height);
	/*for (i = 0; i < image->Width; i++){
		for (j = 0; j < image->Height; j++){
			SetPixelR(NewImage, i, j, GetPixelR(image, i, j));
			SetPixelG(NewImage, i, j, GetPixelG(image, i, j));
			SetPixelB(NewImage, i, j, GetPixelB(image, i, j));
		}
	}*/
	
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
static unsigned char enlarge_compute_intensity(IMAGE * image, int x_big, int y_big, int xpercentage, int ypercentage, int intensity_type){
	double x_small = x_big * 100.0 / xpercentage;
	double y_small = y_big * 100.0 / ypercentage;
	unsigned char temp[4];
	unsigned char return_value;	
	double x_factor = 1 - fmod(x_small, 1.0); double y_factor = 1 - fmod(y_small, 1.0);
	switch (intensity_type){
		case 0:
			temp[0] = GetPixelR(image, floor(x_big * 100 / xpercentage), floor(y_big * 100 / ypercentage));
			temp[1] = GetPixelR(image, floor(x_big * 100 / xpercentage), ceil(y_big * 100 / ypercentage));
			temp[2] = GetPixelR(image, ceil(x_big * 100 / xpercentage), floor(y_big * 100 / ypercentage));
			temp[3] = GetPixelR(image, ceil(x_big * 100 / xpercentage), ceil(y_big * 100 / ypercentage));
			break;
		case 1:
			temp[0] = GetPixelG(image, floor(x_big * 100 / xpercentage), floor(y_big * 100 / ypercentage));
			temp[1] = GetPixelG(image, floor(x_big * 100 / xpercentage), ceil(y_big * 100 / ypercentage));
			temp[2] = GetPixelG(image, ceil(x_big * 100 / xpercentage), floor(y_big * 100 / ypercentage));
			temp[3] = GetPixelG(image, ceil(x_big * 100 / xpercentage), ceil(y_big * 100 / ypercentage));
			break;
		case 2:
			temp[0] = GetPixelB(image, floor(x_big * 100 / xpercentage), floor(y_big * 100 / ypercentage));
			temp[1] = GetPixelB(image, floor(x_big * 100 / xpercentage), ceil(y_big * 100 / ypercentage));
			temp[2] = GetPixelB(image, ceil(x_big * 100 / xpercentage), floor(y_big * 100 / ypercentage));
			temp[3] = GetPixelB(image, ceil(x_big * 100 / xpercentage), ceil(y_big * 100 / ypercentage));
			break;
	}
		
	return_value = temp[0] * x_factor * y_factor + temp[1] * (1 - x_factor) * y_factor + temp[2] * x_factor * (1 - y_factor) + temp[3] * (1-x_factor) * (1-y_factor);
	return return_value;
	
}

/*Resize*/
IMAGE *Resize(IMAGE *image, unsigned int newWidth, unsigned int newHeight){
	unsigned int out_height = newHeight;
	unsigned int out_width = newWidth;
	int ypercentage = newHeight*100/image->Height;
	int xpercentage = newWidth*100/image->Width;
	IMAGE * image_out = CreateImage(out_width, out_height);
	if (image_out == NULL) {printf("ERROR: Out of memory\n"); return image;}
	int i,j;
	
	for (i = 0; i < image_out->Width; i++){
		for (j = 0; j < image_out->Height; j++){			
			if (newWidth != image->Width || newHeight != image->Height){
				/*enlarge*/
				SetPixelR(image_out, i, j, enlarge_compute_intensity(image, i, j, xpercentage,ypercentage, 0));
				SetPixelG(image_out, i, j, enlarge_compute_intensity(image, i, j, xpercentage,ypercentage, 1));
				SetPixelB(image_out, i, j, enlarge_compute_intensity(image, i, j, xpercentage,ypercentage, 2));
				
			} else {
				DeleteImage(image_out);
				return DuplicateImage(image);
			}

		}
	}
	/*DeleteImage(image);*/
	return image_out;
}

IMAGE *StainRemoval(IMAGE *image, int c_var1, int c_var2, int b_threshold, int darken_limiter){
	int i, j;
	int R_samp, G_samp, B_samp;
	int d_thresh, c1_thresh, c2_thresh, b_thresh;
	assert(image);

	d_thresh = 5 * darken_limiter;
	c1_thresh = 5 * c_var1;
	c2_thresh = 5 * c_var2;
	b_thresh = 10 * b_threshold;

	for (i = 0; i < image->Width; i++){
		for (j = 0; j < image->Height; j++){
			SetPixelR(image, i, j, GetPixelR(image, i, j) > d_thresh ? GetPixelR(image, i, j) - d_thresh : GetPixelR(image, i, j));
			SetPixelG(image, i, j, GetPixelG(image, i, j) > d_thresh ? GetPixelG(image, i, j) - d_thresh : GetPixelG(image, i, j));
			SetPixelB(image, i, j, GetPixelB(image, i, j) > d_thresh ? GetPixelB(image, i, j) - d_thresh : GetPixelB(image, i, j));

			R_samp = (int)GetPixelR(image, i, j);
			G_samp = (int)GetPixelG(image, i, j);
			B_samp = (int)GetPixelB(image, i, j);

			if( (abs(R_samp - G_samp) > c1_thresh) || (abs(R_samp - B_samp) > c1_thresh) || (abs(G_samp - B_samp) > c1_thresh) ){
				SetPixelR(image, i, j, 255);
				SetPixelG(image, i, j, 255);
				SetPixelB(image, i, j, 255);
			}

			if ( (R_samp > b_thresh) || (G_samp > b_thresh) || (B_samp > b_thresh)){
				if( (abs(R_samp - G_samp) > c2_thresh) || (abs(R_samp - B_samp) > c2_thresh) || (abs(G_samp - B_samp) > c2_thresh) ){
					SetPixelR(image, i, j, 255);
					SetPixelG(image, i, j, 255);
					SetPixelB(image, i, j, 255);
				}
			}
		}
	}
	return image;
}

IMAGE *ColorFilter(IMAGE *image, int x, int y, int area_x1, int area_y1, int area_x2, int area_y2, int NewPixelValue, int threshold){
	int i, j;
	int degree;
	unsigned char xy_valueR, xy_valueG, xy_valueB, r, g , b;
	int x_c, y_c;

	x_c = area_x1;
	area_x1 = (area_x1 < area_x2) ? area_x1 : area_x2;
	area_x2 = (x_c < area_x2) ? area_x2 : x_c;

	y_c = area_y1;
	area_y1 = (area_y1 < area_y2) ? area_y1 : area_y2;
	area_y2 = (y_c < area_y2) ? area_y2 : y_c;

	assert(image);

	xy_valueR = GetPixelR(image, x, y);
	xy_valueG = GetPixelG(image, x, y);
	xy_valueB = GetPixelB(image, x, y);

	degree = 5 * threshold;

	for (j = area_y1; j <= area_y2; j++)
		for (i = area_x1; i < area_x2; i++){
			r = GetPixelR(image, i, j);
			g = GetPixelG(image, i, j);
			b = GetPixelB(image, i, j);
			if ( ((r > xy_valueR - degree) && (r < xy_valueR + degree)) && ((g > xy_valueG - degree) && (g < xy_valueG + degree)) && ((b > xy_valueB - degree) && (b < xy_valueB + degree))){
				SetPixelR(image, i, j, NewPixelValue);
				SetPixelG(image, i, j, NewPixelValue);
				SetPixelB(image, i, j, NewPixelValue);
			}
		}

	return image;
}
