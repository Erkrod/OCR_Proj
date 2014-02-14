/*********************************************************************/ 
/* Movie.h: header file for basic movie manipulations				 */ 
/*                                                                   */
/* 10/27/11 Weiwei Chen: initial solution version                    */
/*                       for EECS22 assignment5 FAll2011             */
/*********************************************************************/ 
#ifndef MOVIE_H
#define MOVIE_H 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Image.h"
#include "ImageList.h"

/* the structure for MOVIE */
typedef struct{
    ILIST *Frames;          /* the pointer to the frame list */
    unsigned int Width;     /* movie frame width             */
    unsigned int Height;    /* movie frame height            */
    unsigned int NumFrames; /* total number of frames        */
}MOVIE;

/* allocate the memory spaces for the movie              */
/* and the memory spaces for the frame list. 			 */
/* return the pointer to the movie                       */
MOVIE *CreateMovie(unsigned int nFrames, unsigned int W, unsigned int H);

/*release the memory spaces for the frames and the frame list. */
/*release the memory spaces for the movie.                     */
void DeleteMovie(MOVIE *movie);


/* convert the YUV image into the RGB image */
void YUV2RGBImage(IMAGE *Image);

/* convert the RGB image into the YUV image */
void RGB2YUVImage(IMAGE *Image);


#endif
