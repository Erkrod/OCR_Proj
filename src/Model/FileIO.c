
/*********************************************************************/ 
/* FileIO.c: program file for I/O module	                     */ 
/*                                                                   */
/* History:                                                          */
/* 10/29/13 Alex Chu  updated for EECS22 assignment4 Fall2013	     */
/* 10/16/11 Weiwei Chen  updated for EECS22 assignment3 FAll2012     */
/* 10/07/11 Weiwei Chen: initial solution version                    */
/*                       for EECS22 assignment3 FAll2011             */
/*********************************************************************/
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include "Model.h"

/*** function definitions ***/
IMAGE * ReadImage(char *ImageFileName) {
  FILE           *File;
  /*char           *Type, *TypeTest;*/
  char            MagicNum[5];
  int             W, H, MaxValue;
  unsigned int    x, y;
  IMAGE			*image;
  /*int i;
  int testFlag = 0;*/
  UT_string       *command;


  // create command to convert image
  utstring_new(command);
  utstring_printf(command, "anytopnm %s > imageToPNM.ppm", ImageFileName);

  if(0 != system(utstring_body(command))) {
    //fprintf(stderr, "Conversion failed!\n");
    //exit(10);
#ifdef DEBUG
    printf("Conversion failed!\n";
#endif
    return NULL;
   }


  // reading the .ppm file based on FileIO from last qtr
  // includes finding the 'magic number' and calling either pgmtoppm, pbmtopgm then pgmtoppm, or leaving as is
  File = fopen("imageToPNM.ppm", "r");
  if (!File) {
#ifdef DEBUG
    printf("\nCan't open file \"%s\" for reading!\n", ImageFileName);
#endif
    return NULL;
  }

  fscanf(File, "%79s", MagicNum);
  // check for pbm
  if (MagicNum[0] == 'P' && ( MagicNum[1] == '1' || MagicNum[1] == '4')) {
#ifdef DEBUG
    printf("Case: .pbm\n");
#endif
    if(0 != system("pbmtopgm imageToPNM.ppm > imageToPGM.ppm")) {
    //fprintf(stderr, "Conversion failed!\n");
    //exit(10);
#ifdef DEBUG
    printf("Conversion failed!\n";
#endif
    return NULL;
    }
    if(0 != system("pgmtoppm imageToPGM.ppm > image.ppm")) {
    //fprintf(stderr, "Conversion failed!\n");
    //exit(10);
#ifdef DEBUG
    printf("Conversion failed!\n";
#endif
    return NULL;
    }
  }
  else if(MagicNum[0] == 'P' && (MagicNum[1] == '2' || MagicNum[1] == '5')) {
#ifdef DEBUG
    printf("Case: .pgm\n");
#endif
    if(0 != system("pgmtoppm imageToPNM.ppm > image.ppm")) {
     //fprintf(stderr, "Conversion failed!\n");
     //exit(10);
#ifdef DEBUG
    printf("Conversion failed!\n";
#endif
    return NULL;
    }
  }
  else if(MagicNum[0] == 'P' && (MagicNum[1] == '3' || MagicNum[1] == '6')) {
#ifdef DEBUG
    printf("Case: .ppm\n");
#endif
  }
  else {
#ifdef DEBUG
    printf("\nUnsupported file format!\n");
#endif
    fclose(File);
    return NULL;
  }

  fscanf(File, "%d", &W);
  if (W <= 0) {
#ifdef DEBUG
    printf("\nUnsupported image width %d!\n", W);
#endif
    fclose(File);
    return NULL;
  }

  fscanf(File, "%d", &H);
  if (H <= 0) {
#ifdef DEBUG
    printf("\nUnsupported image height %d!\n", H);
#endif
    fclose(File);
    return NULL;
  }

  fscanf(File, "%d", &MaxValue);
  if (MaxValue != 255) {
#ifdef DEBUG
    printf("\nUnsupported image maximum value %d!\n", MaxValue);
#endif
    fclose(File);
    return NULL;
  }
  if ('\n' != fgetc(File)) {
#ifdef DEBUG
    printf("\nCarriage return expected at the end of the file!\n");
#endif
    fclose(File);
    return NULL;
  }

  image = CreateImage(W, H);

  if (!image) {
#ifdef DEBUG
    printf("\nError creating image from %s!\n", ImageFileName);
#endif		
    DeleteImage(image);
    fclose(File);
    return NULL;
  }
  else {
    for (y = 0; y < image->Height; y++)
      for (x = 0; x < image->Width; x++) {
	SetPixelR(image, x, y, fgetc(File));
	SetPixelG(image, x, y, fgetc(File));
	SetPixelB(image, x, y, fgetc(File));
      }

    if (ferror(File)) {
#ifdef DEBUG
      printf("\nFile error while reading from file!\n");
#endif
      DeleteImage(image);
      return NULL;
    }

#ifdef DEBUG
    printf("%s was read successfully!\n", ImageFileName);
#endif
    fclose(File);
  }


  return image;
}


/* Save Image */
int SaveImage(const char fname[SLEN], IMAGE *image)
{
	FILE           *File;
	int             x, y;

	char            ftype[] = ".ppm";
	char            fname_tmp[SLEN];  /*avoid to modify on the original pointer, 11/10/10, X.Han*/
        char            fname_tmp2[SLEN];

	unsigned int	WIDTH = image->Width;
	unsigned int	HEIGHT = image->Height;

	strcpy(fname_tmp, fname);
        strcpy(fname_tmp2, fname);
	strcat(fname_tmp2, ftype);

	File = fopen(fname_tmp2, "w");
	if (!File) {
#ifdef DEBUG
		printf("\nCan't open file \"%s\" for writing!\n", fname);
#endif
		return 1;
	}
	fprintf(File, "P6\n");
	fprintf(File, "%d %d\n", WIDTH, HEIGHT);
	fprintf(File, "255\n");

	for (y = 0; y < HEIGHT; y++)
		for (x = 0; x < WIDTH; x++) {
			fputc(GetPixelR(image, x, y), File);
			fputc(GetPixelG(image, x, y), File);
			fputc(GetPixelB(image, x, y), File);
		}

	if (ferror(File)) {
#ifdef DEBUG
		printf("\nError while writing to file!\n");
#endif
		return 2;
	}
	fclose(File);
#ifdef DEBUG
	printf("%s was saved successfully. \n", fname_tmp2);

#endif

	return (0);
}

/* EOF FileIO.c */
