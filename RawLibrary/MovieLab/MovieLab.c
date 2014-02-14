/*********************************************************************/
/* MovieLab.c: homework assignment #5, for EECS 22,	Fall 2011			 */
/*																																	 */
/* History:																													*/
/* 10/30/11 Weiwei Chen	updated for EECS22 assignment5 FAll2011		 */
/* 10/30/11 Weiwei Chen	: initial template version									 */
/*********************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "Constants.h"
#include "Movie.h"
#include "DIPs.h"
#include "time.h"


/*save the movie frames to the output file */
int SaveMovie(const char *fname, MOVIE *movie);

/*read one frame from the movie */
IMAGE* ReadOneFrame(const char* fname, int nFrame, unsigned int W, unsigned H);

/*read the movie frames from the input file */
int ReadMovie(const char *fname, int nFrame, unsigned int W, unsigned H, MOVIE *movie);

/* Print the command line parameter usage of the program*/
void PrintUsage();

/* type define the function pointer to the DIP function	*/
typedef void MOP_F(IMAGE *image);

/* the function for perform DIP operations on the movie*/
void Movie_DIP_Operation(MOVIE *movie, MOP_F* MovieOP);

int JuliaSetMovie(int nFrame, unsigned int W, unsigned H, MOVIE *movie);

int main(int argc, char *argv[])
{
	int x = 0, n = 0, h = 0, v = 0, e = 0, s = 0, p = 0, bw = 0, r = 0, j = 0, rs = 0, cat = 0, cut = 0, ff = 0 ;
	char *fin = NULL, *fout = NULL;
	char *fcat = NULL; 
	unsigned int Width = 0, Height = 0, NumFrames = 0, NumFramesCat = 0, NumFrames_All = 0, CutSF = 0, CutEF = 0;
	int rs_factor = 0, ff_factor = 0 ; 
	MOVIE *movie;

 /*entering while loop to check options entered*/
	while(x < argc)
	{
		/*specify input video*/
		if(0 == strcmp(&argv[x][0], "-i")) 
		{
			if(x < argc - 1)
			{
				fin = (char *)malloc(sizeof(char) * (strlen(&argv[x + 1][0]) + strlen(".yuv") + 1));
				if (fin != NULL)
				{
					strcpy(fin, argv[x + 1]);
					strcat( fin, ".yuv");
				}
				else
				{
					free (fin) ; 
					free (fout) ; 
					if (cat == 1)
						free (fcat) ; 
					return 5 ; 
				}
			}/*fi*/
			else
			{
				printf("Missing argument for input name!");
				free(fin);
				free(fout);
				if (cat == 1)
					free(fcat) ; 
				return 5;
			}/*esle*/
			x += 2;
			continue;
		}/*fi*/

		/*specify output video*/
		if(0 == strcmp(&argv[x][0], "-o")) 
		{
			if(x < argc - 1)
			{
				fout = (char *)malloc(sizeof(char) * (strlen(&argv[x + 1][0]) + strlen(".yuv") + 1));
				if (fout != NULL)
				{
					strcpy(fout, argv[x + 1]);
					strcat( fout, ".yuv");
				}
				else
				{
					free (fin) ; 
					free (fout) ; 
					if (cat == 1)
						free (fcat) ; 
					return 5 ; 
				}
			}/*fi*/
			else
			{
				printf("Missing argument for output name!");
				free(fin);
				free(fout);
				if (cat == 1)
					free(fcat) ; 
				return 5;
			}/*esle*/
			x += 2;
			continue;
		}/*fi*/

		/*specify video size*/
		if(0 == strcmp(argv[x], "-s")) 
		{
			if(x < argc - 1)
			{
				if (sscanf(argv[x + 1], "%dx%d", &Width, &Height) != 2)
				{
					printf("The format of the resolution information specified with -s is incorrect.\n");
					PrintUsage();
					free(fin);
					free(fout);
					if (cat == 1)
						free(fcat) ; 
					return 5;
				}
			}
			else
			{
				printf("Missing resolution information.\n");
				PrintUsage();
				free(fin);
				free(fout);
				if (cat == 1)
					free(fcat) ; 
				return 5;
			}
			x += 2;
			continue;
		}/*fi*/

		/*concatenate option, should provide the name of the second video*/
		if(0 == strcmp(argv[x], "-cat")) 
		{
			cat = 1 ; 
			if(x < argc - 1)
			{
				fcat = (char *)malloc(sizeof(char) * (strlen(&argv[x + 1][0]) + strlen(".yuv") + 1));
				
				if (fcat != NULL)
				{
					strcpy(fcat, argv[x + 1]);
					strcat(fcat, ".yuv");
				}
				else
				{
					free (fin) ; 
					free (fout) ; 
					if (cat == 1)
						free (fcat) ; 
					return 5; 
				}
			}/*fi*/
			else
			{
				printf("Missing argument for input name!\n");
				free(fin);
				free(fout);
				if (cat == 1)
					free(fcat) ; 
				return 5;
			}/*esle*/
			x += 2;
			continue;
		}/*fi*/

		/*specify start fame and end frame of cut function*/
		if(0 == strcmp(argv[x], "-cut")) 
		{
			cut = 1 ; 
			if(x < argc - 1)
			{
				if(argc < (x + 1) || (sscanf(argv[x + 1], "%d-%d", &CutSF, &CutEF) != 2) )
				{
					printf("The format of the cutting information specified with -cut is incorrect.\n");
					PrintUsage();
					free(fin);
					free(fout);
					if (cat == 1)
						free(fcat) ; 
					return 5;
				}
			}
			else
			{
				printf("Missing argument for cutting function!\n");
				free(fin);
				free(fout);
				if (cat == 1)
					free(fcat) ; 
				return 5;
			}/*esle*/
			x += 2;
			continue;
		}/*fi*/
		
		/*specify the length of the frame*/
		if(0 == strcmp(argv[x], "-f")) 
		{
			if(x < argc - 1)
			{
				if (sscanf(argv[x + 1], "%d", &NumFrames) != 1)
				{
					printf("The format of the resolution information specified with -f is incorrect..\n");
					PrintUsage();
					free(fin);
					free(fout);
					if (cat == 1)
						free(fcat) ; 
					return 5;
				}
			}
			else
			{
				printf("Missing frame number information.\n");
				PrintUsage();
				free(fin) ; 
				free(fout) ; 
				if (cat == 1)
					free(fcat) ; 
				return 5 ; 
			}
			x += 2;
			continue;
		}/*fi*/

		/*specify the length of the frame*/
		if(0 == strcmp(argv[x], "-fcat")) 
		{
			if(x < argc - 1)
			{
				if (sscanf(argv[x + 1], "%d", &NumFramesCat) != 1)
				{
					printf("The format of the resolution information specified with -fcat is incorrect..\n");
					PrintUsage();
					free(fin);
					free(fout);
					if (cat == 1)
						free(fcat) ; 
					return 5;
				}
			}
			else
			{
				printf("Missing frame number information for concatenate function.\n");
				PrintUsage();
				free(fin) ; 
				free(fout) ; 
				if (cat == 1)
					free(fcat) ; 
				return 5 ; 
			}
			x += 2;
			continue;
		}/*fi*/
		
		/*Julia Set*/
		if(0 == strcmp(&argv[x][0], "-j")) 
		{
			j = 1;
			x++;
			continue;
		}/*fi*/
		
		/* Resize*/
		if(0 == strcmp(argv[x], "-resize")) 
		{
			rs = 1 ; 
			if(x < argc - 1)
			{
				if (sscanf(argv[x + 1], "%d", &rs_factor) != 1)
				{
					printf("The format of the resolution information specified with -resize is incorrect..\n");
					PrintUsage();
					free(fin);
					free(fout);
					if (cat == 1)
						free(fcat) ; 
					return 5;
				}
			}
			else
			{
				printf("Missing resize factor information.\n");
				PrintUsage();
				free(fin) ; 
				free(fout) ; 				
				if (cat == 1)
					free(fcat) ; 
			}
			x += 2;
			continue;
		}/*fi*/

		/* Fast Forward */
		if(0 == strcmp(argv[x], "-fast")) 
		{
			ff = 1 ; 
			if(x < argc - 1)
			{
				if (sscanf(argv[x + 1], "%d", &ff_factor) != 1) 
				{
					printf("The format of the resolution information specified with -fast is incorrect..\n");
					PrintUsage();
					free(fin);
					free(fout);
					if (cat == 1)
						free(fcat) ; 
					return 5;
				}
			}
			else
			{
				printf("Missing fast forward factor information.\n");
				PrintUsage();
				free(fin) ; 
				free(fout) ; 				
				if (cat == 1)
					free(fcat) ; 
				return 5 ; 
			}
			x += 2;
			continue;
		}/*fi*/

		/*Black and White*/
		if(0 == strcmp(&argv[x][0], "-bw")) 
		{
			bw = 1;
			x++;
			continue;
		}/*fi*/
		
		/*Horizontal Mirror*/
		if(0 == strcmp(&argv[x][0], "-hmirror")) 
		{
			h = 1;
			x++;
			continue;
		}/*fi*/
		
		/*Vertical Flip*/
		if(0 == strcmp(&argv[x][0], "-vflip")) 
		{
			v = 1;
			x++;
			continue;
		}/*fi*/
		
		/*Add Noise*/
		if(0 == strcmp(&argv[x][0], "-noise")) 
		{
			n = 1;
			x++;
			continue;
		}/*fi*/
		
		/*Edge*/
		if(0 == strcmp(&argv[x][0], "-edge")) 
		{
			e = 1;
			x++;
			continue;
		}/*fi*/

		/*Sharpen*/
		if(0 == strcmp(&argv[x][0], "-sharpen")) 
		{
			s = 1;
			x++;
			continue;
		}/*fi*/

		/*Sharpen*/
		if(0 == strcmp(&argv[x][0], "-poster")) 
		{
			p = 1;
			x++;
			continue;
		}/*fi*/

		/* reverse */
		if(0 == strcmp(&argv[x][0], "-rvs")) 
		{
			r = 1;
			x++;
			continue;
		}/*fi*/
		if(0 == strcmp(&argv[x][0], "-h")) 
		{ 
			PrintUsage();
			free(fin);
			free(fout);
			if (cat == 1)
				free(fcat) ; 
			return 0;
		}/*fi*/
		x++;
	}/*elihw*/


 	if(Width == 0 || Height == 0){
		printf("Resolution information provided by -s parameter are not correct.\n");
		PrintUsage();
		free(fin);
		free(fout);
		if (cat == 1)
			free(fcat) ; 
		return 5;
	}

	if (NumFrames == 0)
	{
		printf("Frame number information provided by -f parameter is not correct.\n") ; 
		PrintUsage();
		free(fin);
		free(fout);
		if (cat == 1)
			free(fcat) ; 
		return 5;
	}

	if(!fin && !j){
		printf("Missing argument for input name!\n");
		PrintUsage();
		free(fin);
		free(fout);
		if (cat == 1)
			free(fcat) ; 
		return 5;
	}
	
	if(!fout){
		printf("Missing argument for output name!\n");
		PrintUsage();
		free(fin);
		free(fout);
		if (cat == 1)
			free(fcat) ; 
		return 5;
	}

	if (NumFramesCat == 0 && cat == 1 && j==0)
	{
		printf("Frame number information provided by -fcat parameter is not correct.\n");
		PrintUsage();
		free(fin);
		free(fout);
		if (cat == 1)
			free(fcat) ; 
		return 5;
	}

	
	if (rs == 1 && j == 0)
	{
		if (rs_factor == 0)
		{
			printf("Resize information provided by -resize parameter is not correct ( = 0 ).\n");
			PrintUsage();
			free(fin);
			free(fout);
			if (cat == 1)
				free(fcat) ; 
			return 5;
		}	
		if (rs_factor < 0 || rs_factor > 100)
		{
			printf("Resize factor should be an integer in the rane [1:100]\n") ; 
			PrintUsage();		
			free(fin) ; 
			free(fout) ; 
			if (cat == 1)
				free(fcat) ; 
			return 5 ; 
		}
		else if ((Height*rs_factor/100) < 1 || (Width*rs_factor/100) < 1)
		{
			printf("Height/Width of the Resized Image is less than 1 pixel.\n") ; 
			PrintUsage();		
			free(fin) ; 
			free(fout) ; 
			if (cat == 1)
				free(fcat) ; 
			return 5 ; 
		}		
	}

	if (ff_factor < 1 && ff == 1 && j==0)
	{
		printf("Resize information provided by -resize parameter is not correct ( < 1 ).\n");
		PrintUsage();
		free(fin);
		free(fout);
		if (cat == 1)
			free(fcat) ; 
		return 5;
	}

	if (cat == 1 && j==0) 
		NumFrames_All = NumFrames + NumFramesCat ; 		
	else
		NumFrames_All = NumFrames ; 

	if (cut == 1 && CutEF > NumFrames_All && j==0)
	{
		printf("End Frame Number of Cut function should be less than the number of total frame.\n") ; 
		PrintUsage();
		free(fin);
		free(fout);
		if (cat == 1)
			free(fcat) ; 
		return 5 ; 	
	}

	if (cut == 1 && (CutSF <= 0 || CutEF <= 0) && j==0)
	{
		printf("Start/End Frame Number cannot be less than 1.\n") ; 
		PrintUsage();
		free(fin);
		free(fout);
		if (cat == 1)
			free(fcat) ; 
		return 5 ; 	
	}
	
	if(cut == 1 && CutEF <= CutSF && j==0){
		printf("End Frame Number of the cuting function cannot be smaller than the Start Frame Number.\n");
		PrintUsage();
		free(fin);
		free(fout);
		if (cat == 1)
			free(fcat) ; 
		return 5 ; 	
	}
	

	movie = CreateMovie(NumFrames_All, Width, Height);
	if (movie == NULL)
	{
		free (fin) ; 
		free (fout) ; 
		if (cat == 1)
			free (fcat) ; 
		return 5 ; 
	}
	else
	{
		movie->Frames = NewImageList();
		if (movie->Frames == NULL)
		{
			free (fin) ; 
			free (fout) ; 
			if (cat == 1)
				free (fcat) ; 
			free (movie) ; 
		}
	}

	if(j == 1)
	{
		JuliaSetMovie(NumFrames, Width, Height, movie);
	}
	else
	{
		if ( 0 != ReadMovie(fin, NumFrames, Width, Height, movie) )
		{
			free (fin) ; 
			free (fout) ; 
			if (cat == 1)
				free (fcat) ;
			DeleteMovie(movie);
			return 5 ; 
		}

		if (cat == 1)
		{
			if (0 != ReadMovie(fcat, NumFramesCat, Width, Height, movie)) 
			{
				free (fin) ; 
				free (fout) ; 
			 	if (cat == 1)
			 		free (fcat) ; 
			 	DeleteMovie(movie);
			 	return 5 ; 
			}
			printf("Operation Concatenate is done! \n") ; 
		}
	
		if(bw == 1){
			Movie_DIP_Operation(movie, BlackNWhite);
			printf("Operation BlackNWhite is done! \n");
		}
		if(v == 1){
			Movie_DIP_Operation(movie, VFlip);
			printf("Operation VFlip is done! \n");
		}
		if(h == 1){
			Movie_DIP_Operation(movie, HMirror);
			printf("Operation HMirror is done! \n");
		}
		if(n == 1){
			srand(time(0));
			Movie_DIP_Operation(movie, AddNoise);
			printf("Operation AddNoise is done! \n");
		}
		if(e == 1){
			Movie_DIP_Operation(movie, Edge);
			printf("Operation Edge is done! \n");
		}
		if(s == 1){
			Movie_DIP_Operation(movie, Sharpen);
			printf("Operation Sharpen is done! \n");
		}
		if(p == 1){
			Movie_DIP_Operation(movie, Posterize);
			printf("Operation Posterize is done! \n");
		}
		if (rs ==1){
			movie->Height = movie->Height * rs_factor / 100; 
			movie->Width  = movie->Width  * rs_factor / 100;
			ResizeImageList(movie->Frames, rs_factor) ; 		
			printf("Operation Resize is done! New Width/Height = %dx%d \n", movie->Width, movie->Height);
		}
		if (cut == 1)
		{
			movie->NumFrames = CutEF - CutSF + 1; 
			CropImageList(movie->Frames, CutSF, CutEF) ; 
			printf("Operation Frame Cropping is done! \n") ; 
		}
		if (ff == 1)
		{
			movie->NumFrames = FastImageList(movie->Frames, ff_factor) ; 
			printf("Operation Fast Forward is done! Number of frames = %d\n", movie->NumFrames) ; 
		}
		if(r == 1){
			ReverseImageList(movie->Frames);
			printf("Operation ReverseMovie is done! \n");
		}		
	}

	SaveMovie(fout, movie);

	DeleteMovie(movie);
	movie = NULL;

	free(fin);
	free(fout);

 /* if (cat == 1) */
  	free(fcat) ; 

	return 0;
}


void Movie_DIP_Operation(MOVIE *movie, MOP_F* MovieOP)
{
	IENTRY *curr;

	curr = movie->Frames->First;	

	while(curr){
		YUV2RGBImage(curr->Image);
		MovieOP(curr->Image);
		RGB2YUVImage(curr->Image);
		curr = curr->Next;
	}
}

void PrintUsage()
{
	printf("\nFormat on command line is:\n"
	"MovieLab [option]\n"
	"-i [file_name]    to provide the input file name\n"
	"-o [file_name]    to provide the	output file name\n"
	"-f [no_frames]    to determine how many frames desired in the input stream\n"
	"-s [WidthxHeight] to set resolution of the input stream (widthxheight)\n"
	"-j                to generate the movie with JuliaSet sequences\n"
	"-bw               to activate the conversion to black and white\n"
	"-vflip            to activate vertical flip\n"
	"-hmirror          to activate horizontal flip\n"
	"-noise            to add noise to the movie \n"
  "-edge             to activate edge filter\n"
  "-sharpen          to activate sharpen filter\n"
  "-poster           to activate posterize filter\n"
  "-cat [file_name]  to provide the file to concatenate with the input file\n"  
  "-fcat [no_frames] to determine how many frames desired in the stream to be concatenated\n"  
  "-cut [Start-End]  to crop the frame from the video from frame Start to frame End\n"  
  "-resize [factor]  to resize the video with the provided factor [1-100]\n"
  "-fast   [factor]  to fast forward the video with the provided factor [1+]\n"
	"-rvs              to reverse the frame order of the input stream\n"
	"-h                to show this usage information\n"
	);
}

IMAGE* ReadOneFrame(const char *fname, int nFrame, unsigned int W, unsigned H)
{
	/*defining local variables*/
	FILE *file;

	unsigned int x, y;
	unsigned char ch;
	IMAGE* image ; 	
 
	/*checking error*/
	assert(fname);
	assert(nFrame >= 0);

	image = CreateImage(W, H) ; 	
	if (image == NULL)
		return NULL ; 


	/*opening file stream*/
	file = fopen(fname, "r");
	if (file == NULL) 
		return NULL ; 

	/*find desired frame*/
	fseek(file, 1.5 * nFrame * W * H, SEEK_SET);

	for(y = 0; y < H; y ++){
		for(x = 0; x < W; x ++){
			ch = fgetc(file);
			SetPixelY(image, x, y, ch);
		}/*rof*/
	}
	

	for(y = 0; y < H ; y += 2){
		for(x = 0; x < W ; x += 2){
			ch = fgetc(file);
			SetPixelU(image, x, y, ch);
			SetPixelU(image, x + 1, y, ch);
			SetPixelU(image, x, y + 1, ch);
			SetPixelU(image, x + 1, y + 1, ch);
		}
	}

	for(y = 0; y < H ; y += 2){
		for(x = 0; x < W ; x += 2){
			ch = fgetc(file);
			SetPixelV(image, x, y, ch);
			SetPixelV(image, x + 1, y, ch);
			SetPixelV(image, x, y + 1, ch);
			SetPixelV(image, x + 1, y + 1, ch);
		}
	}
	
	/*checking for error*/

	assert(ferror(file) == 0) ; 

	/*closing stream and terminating*/
	fclose(file);
	file = NULL;
	return image;
}

/*save the movie frames to the output file */
int SaveMovie(const char *fname, MOVIE *movie)
{
	int i ; 
	int x, y;
	FILE *file;
	IENTRY *currFrame;

	 /*opening file stream*/
	 if(!(file = fopen(fname, "w"))){
			return 1;
	 }
	 
	 i = 0 ; 
	 currFrame = movie->Frames->First;
	 while(currFrame){
		for(y = 0; y < movie->Height; y ++){ 
			for(x = 0; x < movie->Width; x ++){
				fputc(GetPixelY(currFrame->Image, x, y), file);
			}
		}
		for(y = 0; y < movie->Height; y += 2){ 
			for(x = 0; x < movie->Width; x += 2){
				fputc(GetPixelU(currFrame->Image, x, y), file);
			}
		}
		for(y = 0; y < movie->Height; y += 2){ 
			for(x = 0; x < movie->Width; x += 2){
				fputc(GetPixelV(currFrame->Image, x, y), file);
			}
		}
		currFrame = currFrame->Next;	 
		i++ ; 
	 }

	 fclose(file);
	 file = NULL;

	 printf("The movie file %s has been written successfully! \n", fname);
	 printf("%d frames are written to the file %s in total \n", i, fname); 
	 return 0;
}

/*read the movie frames from the input file */
int ReadMovie(const char *fname, int nFrame, unsigned int W, unsigned H, MOVIE *movie)
{
	int i;
	IMAGE *image;

	for(i = 0; i < nFrame; i ++){
		image = ReadOneFrame(fname, i, W, H) ; 
		if (image == NULL)
			return 1 ; 
		AppendImage(movie->Frames, image);
	}
	printf("The movie file %s has been read successfully! \n", fname);
	return 0;
}

/*Fill the juliaset images as the frames to the input file */
int JuliaSetMovie(int nFrame, unsigned int W, unsigned H, MOVIE *movie)
{
	int i;
	IMAGE *image;
	long double z = 1.0L ; 
	unsigned int max_iteration = 512 ; 

	for(i = 1; i <= nFrame; i ++)
	{
		image = Juliaset(W, H, max_iteration, z);

		RGB2YUVImage(image);
		AppendImage(movie->Frames, image);

		printf("Creating JuliaSet frame #%d\n", i);
		z *= 1.17;
	}

	return 0;
}

