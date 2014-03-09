/*********************************************************************/
/* DIPs.h: homework assignment #3, for EECS 22,  Fall 2011       	 */
/*                                                                   */
/* History:                                                          */
/* 10/07/11 Weiwei Chen  updated for EECS22 assignment3 FAll2011     */
/* 						 initial version                			 */
/*********************************************************************/
#ifndef DIPS_H
#define DIPS_H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "Image.h"
/*#include "Constants.h"*/
#include <math.h>

/*rotate image*/
IMAGE *Rotate(IMAGE *image, int ClockwiseDegree);

/*crop*/
IMAGE *Crop(IMAGE *image, int x1, int y1, int width, int height);
IMAGE *CropImage(IMAGE *image, int x1, int y1, int x2, int y2);

/*duplicate image*/
IMAGE * DuplicateImage(IMAGE * image);

/* reverse image color */
void BlackNWhite(IMAGE *image) ; 

/* flip image vertically */
void VFlip(IMAGE *image) ;

/* mirror image horizontally */
void HMirror(IMAGE *image) ; 


/* sharpen the image */
void Sharpen(IMAGE *image) ; 

/* Find the edges in the image */
void Edge(IMAGE *image) ;

/* Posterization */
void Posterize(IMAGE *image) ; 

/* add noise to image */
void AddNoise(IMAGE *image) ;

/* Resize */
IMAGE *Resize(	unsigned int percentage, IMAGE *image) ; 

IMAGE *StainRemoval(IMAGE *image, int c_var1, int c_var2, int b_threshold, int darken_limiter);

IMAGE *ColorFilter(IMAGE *image, int x, int y, int area_x1, int area_y1, int area_x2, int area_y2, int NewPixelValue, int threshold);
#endif
