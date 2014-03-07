/* Rotate testing program */

#include "Image.h"
#include "FileIO.h"
#include "Dips.h"
#include "Constants.h"
#include <stdlib.h>
#include <stdio.h>


/* This test function assumes your terminal can open a display for viewing the image with eog image viewer */
/* RotTest function */
int main(){
	IMAGE *image;
	char filename[SLEN];
	int degrees;

	printf("Enter the name of the file: ");
	scanf("%s", filename);
	printf("Enter the degree of CW rotation: ");
	scanf("%d", &degrees);

	image = ReadImage(filename);
	Rotate(image, degrees);
	SaveImage("Rot_output", image);

	return 0;
}
