/*********************************************************************/ 
/* FileIO.c: program file for I/O module	                     */ 
/*                                                                   */
/* History:                                                          */
/* 10/16/13 Yasaman : updated for EECS22 assignment3 Fall13          */
/* 10/16/11 Weiwei Chen  updated for EECS22 assignment3 FAll2012     */
/* 10/07/11 Weiwei Chen: initial solution version                    */
/*                       for EECS22 assignment3 FAll2011             */
/*********************************************************************/
#include "FileIO.h"
/*** function definitions ***/

int
ReadImage(char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	FILE           *File;
	char            Type[SLEN];
	int             Width, Height, MaxValue;
	int             x, y;
	char            ftype[] = ".ppm";
        char            fname_tmp[SLEN];  /*avoid to modify on the original pointer, 11/10/10, X.Han*/

        strcpy(fname_tmp, fname);
	strcat(fname_tmp, ftype);

	File = fopen(fname_tmp, "r");
	if (!File) {
#ifdef DEBUG
		printf("\nCan't open file \"%s\" for reading!\n", fname);
#endif
		return 1;
	}
	fscanf(File, "%79s", Type);
	if (Type[0] != 'P' || Type[1] != '6' || Type[2] != 0) {
#ifdef DEBUG
		printf("\nUnsupported file format!\n");
#endif
		return 2;
	}
	fscanf(File, "%d", &Width);
	if (Width != WIDTH) {
#ifdef DEBUG
		printf("\nUnsupported image width %d!\n", Width);
#endif
		return 3;
	}
	fscanf(File, "%d", &Height);
	if (Height != HEIGHT) {
#ifdef DEBUG
		printf("\nUnsupported image height %d!\n", Height);
#endif
		return 4;
	}
	fscanf(File, "%d", &MaxValue);
	if (MaxValue != 255) {
#ifdef DEBUG
		printf("\nUnsupported image maximum value %d!\n", MaxValue);
#endif
		return 5;
	}
	if ('\n' != fgetc(File)) {
#ifdef DEBUG
		printf("\nCarriage return expected!\n");
#endif
		return 6;
	}
	for (y = 0; y < HEIGHT; y++)
		for (x = 0; x < WIDTH; x++) {
			R[x][y] = fgetc(File);
			G[x][y] = fgetc(File);
			B[x][y] = fgetc(File);
		}
	if (ferror(File)) {
#ifdef DEBUG
		printf("\nFile error while reading from file!\n");
#endif
		return 7;
	}
#ifdef DEBUG
	printf("%s was read successfully!\n", fname_tmp);
#endif
	fclose(File);
	return 0;
}

int
SaveImage(char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	FILE           *File;
	int             x, y;
	char            SysCmd[SLEN * 5];

	char            ftype[] = ".ppm";
	char            fname_tmp[SLEN];  /*avoid to modify on the original pointer, 11/10/10, X.Han*/
        char            fname_tmp2[SLEN];

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
			fputc(R[x][y], File);
			fputc(G[x][y], File);
			fputc(B[x][y], File);
		}

	if (ferror(File)) {
#ifdef DEBUG
		printf("\nFile error while writing to file!\n");
#endif
		return 2;
	}
	fclose(File);
#ifdef DEBUG
	printf("%s was saved successfully. \n", fname_tmp2);
#endif
	/*
	 * rename file to image.ppm, convert it to ~/public_html/<fname>.jpg
	 * and make it world readable
	 */
	sprintf(SysCmd, "/users/grad2/doemer/eecs22/bin/pnmtojpeg_hw2.tcsh %s",
		fname_tmp2);
	if (system(SysCmd) != 0) {
#ifdef DEBUG
		printf("\nError while converting to JPG:\nCommand \"%s\" failed!\n", SysCmd);
#endif
		return 3;
	}
#ifdef DEBUG
	printf("%s.jpg was stored for viewing. \n", fname_tmp);
#endif

	return (0);
}

/* EOF FileIO.c */
