/* Stain Removal testing program */

#include <stdio.h>
#include <stdlib.h>
#include "Model.h"

#ifndef TESTCASE
#define TESTCASE 1
#endif

int main(){
	IMAGE *image;
	char filename[SLEN];
	
#if TESTCASE == 0
	printf("Enter the name of the file: ");
	scanf("%s", filename);
#elif TESTCASE == 1
	strcpy(filename, "Images/03_HelloWorld_Coffee300DPI.jpg");
	
#endif 
	image = ReadImage(filename);
	StainRemoval(image, 9, 3, 15, 3);
	SaveImage("SR_output", image);

	return 0;
}
