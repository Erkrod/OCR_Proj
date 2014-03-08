#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Dips.h"

/*
IMAGE *CropImage(IMAGE *image, int x1, int y1, int x2, int y2){
This function will crop the image into a smaller area between (x1,
y1) and (x2, y2). (x1,y1) is on top left and (x2, y2) is on lower
right. You can assume that the input is checked to be valid.

}
*/
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
				system("pamflip -ccw pre_rot.ppm > rot_o.ppm; rm pre_rot.ppm; mv rot_o.ppm pre_rot.ppm");
				ClockwiseDegree -= 270;
			}else{
				system("pamflip -rotate180 pre_rot.ppm > rot_o.ppm; rm pre_rot.ppm; mv rot_o.ppm pre_rot.ppm");
				ClockwiseDegree -= 180;
			}
		}else{
			system("pamflip -cw pre_rot.ppm > rot_o.ppm; rm pre_rot.ppm; mv rot_o.ppm pre_rot.ppm");
			ClockwiseDegree -= 90;
		}
	}

	if (ClockwiseDegree == 90){
		system("pamflip -cw pre_rot.ppm > rot_o.ppm; rm pre_rot.ppm");
	}else{
		sprintf(degrees, "%d", ClockwiseDegree * -1);	
		strcat(command, degrees);
		strcat(command, " pre_rot.ppm > rot_o.ppm");
		system(command);
		system("rm pre_rot.ppm");
	}

	DeleteImage(image);
	image = ReadImage("rot_o");
	system("rm rot_o.ppm");

	return image;

}

IMAGE *Resize(IMAGE *image, unsigned int percentage)
{
	unsigned int    x, y, x1, y1, x2, y2, i, j, tmpR, tmpG, tmpB;
	unsigned int 	NEW_WIDTH, NEW_HEIGHT;
	unsigned int WIDTH;
	unsigned int HEIGHT;
	IMAGE *image_tmp;

	assert(image);
	WIDTH 	= image->Width;
	HEIGHT = image->Height;

	if(percentage <= 0 || percentage > 500){
		printf("Resizing percentage %d%% is out of the range, Sorry! \n", percentage);
		return image;
	}

	NEW_WIDTH = WIDTH * percentage / 100;
	NEW_HEIGHT = HEIGHT * percentage / 100;
	image_tmp = CreateImage(NEW_WIDTH, NEW_HEIGHT);
	
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

	DeleteImage(image);
	image = NULL;
	return image_tmp;
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

IMAGE *CropImage(IMAGE *image, int x1, int y1, int x2, int y2){
	int i, j;
	unsigned W, H;
	int x_c, y_c;
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

	for (i = x1; i <= x2; i++) {
		for (j = y1; j <= y2; j++) {
				SetPixelR(image_tmp, i-x1, j-y1, GetPixelR(image, i, j));
				SetPixelG(image_tmp, i-x1, j-y1, GetPixelG(image, i, j));
				SetPixelB(image_tmp, i-x1, j-y1, GetPixelB(image, i, j));
		}
	}

	DeleteImage(image);
	image = NULL;
	return image_tmp;
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
