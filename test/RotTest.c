/* Rotate testing program */


#include <stdlib.h>
#include <stdio.h>
#include "Model.h"

#ifndef TESTCASE
#define TESTCASE 1
#endif


/* This test function assumes your terminal can open a display for viewing the image with eog image viewer */
/* RotTest function */
int main(){
	IMAGE *image;
	char filename[SLEN];
	int degrees;

#if TESTCASE == 0
	printf("Enter the name of the file: ");
	scanf("%s", filename);
	printf("Enter the degree of CW rotation: ");
	scanf("%d", &degrees);
#elif TESTCASE == 1
	strcpy(filename, "Images/03_HelloWorld_Coffee300DPI.jpg");
	degrees = 30;
#endif
	
	image = ReadImage(filename);
	image = Rotate(image, degrees);
	assert(image);
	SaveImage("Rot_output", image);

	return 0;
}
