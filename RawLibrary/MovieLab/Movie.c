#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Movie.h"
#include "Image.h"
#include "ImageList.h"


/* allocate the memory spaces for the movie							*/
/* and the memory spaces for the frame list.				*/
/* return the pointer to the movie											 */
MOVIE *CreateMovie(unsigned int nFrames, unsigned int W, unsigned int H)
{
	MOVIE *movie = (MOVIE *)malloc(sizeof(MOVIE));

	if (movie != NULL)
	{
		movie->NumFrames	 = nFrames;
		movie->Width		= W;
		movie->Height		= H;
	}

	return movie;
}

/*release the memory spaces for the frames and the frame list. */
/*release the memory spaces for the movie.										 */
void DeleteMovie(MOVIE *movie)
{
	assert(movie);

	DeleteImageList(movie->Frames);
	
	free(movie);
}

/* convert the YUV image into the RGB image */
void YUV2RGBImage(IMAGE *Image)
{
        int x, y;
        int C, D, E, R, G, B;

        assert(Image);

        for(x = 0; x < Image->Width; x ++){
                for(y = 0; y < Image->Height; y ++){
                        C = GetPixelY(Image, x, y) - 16;
                        D = GetPixelU(Image, x, y) - 128;
                        E = GetPixelV(Image, x, y) - 128;

                        R = (298 * C + 409 * E + 128) >> 8;
                        G = (298 * C - 100 * D - 208 * E + 128) >> 8;
                        B = (298 * C + 516 * D + 128) >> 8;

                        R = R > 0 ? R : 0;
                        R = R < 255 ? R : 255;
                        G = G > 0 ? G : 0;
                        G = G < 255 ? G : 255;
                        B = B > 0 ? B : 0;
                        B = B < 255 ? B : 255;

                        SetPixelR(Image, x, y, (unsigned char)R);
                        SetPixelG(Image, x, y, (unsigned char)G);
                        SetPixelB(Image, x, y, (unsigned char)B);
                }
        }
}

void RGB2YUVImage(IMAGE *Image)
{
        int x, y;
        int R, G, B, Y, U, V;

        assert(Image);

        for (x = 0 ; x < Image->Width; x++) {
                for (y = 0; y < Image->Height; y++) {
                        R = GetPixelR(Image, x, y);
                        G = GetPixelG(Image, x, y);
                        B = GetPixelB(Image, x, y);

                        Y = ((66*R + 129*G + 25*B + 128) >>8) +16 ;
                        U = (( (-38) * R - 74 * G + 112 * B + 128) >> 8) + 128;
                        V = (( 112 * R - 94 * G - 18 * B + 128) >> 8) + 128;

                        Y = Y > 0 ? Y : 0;
                        Y = Y < 255 ? Y : 255;
                        U = U > 0 ? U : 0;
                        U = U < 255 ? U : 255;
                        V = V > 0 ? V : 0;
                        V = V < 255 ? V : 255;

                        SetPixelY(Image, x, y, (unsigned char)Y);
                        SetPixelU(Image, x, y, (unsigned char)U);
                        SetPixelV(Image, x, y, (unsigned char)V);
                }
        }

}


