/* Crop testing program */

#include <stdio.h>
#include <stdlib.h>
#include "Model.h"

#ifndef TESTCASE
#define TESTCASE 1
#endif

int main(){
	IMAGE *image;
	char filename[SLEN];
	unsigned x1, x2, y1, y2;

#if TESTCASE == 0
	printf("Enter the name of the file: ");
	scanf("%s", filename);
	printf("Enter x1: ");
	scanf("%u", &x1);
	printf("Enter x2: ");
	scanf("%u", &x2);
	printf("Enter y1: ");
	scanf("%u", &y1);
	printf("Enter y2: ");
	scanf("%u", &y2);
#elif TESTCASE == 1
	strcpy(filename, "Images/03_HelloWorld_Coffee300DPI.jpg");
	x1 = 100; x2 = 500; y1 = 200; y2 = 700;
#endif
	
	image = ReadImage(filename);
	image = CropImage(image, x1, y1, x2, y2);
	SaveImage("Crop_output", image);

	return 0;

}
