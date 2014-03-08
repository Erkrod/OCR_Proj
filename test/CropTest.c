/* Crop testing program */

#include <stdio.h>
#include <stdlib.h>
#include "Constants.h"
#include "Image.h"
#include "FileIO.h"
#include "Dips.h"
#include "Constants.h"

int main(){
	IMAGE *image;
	char filename[SLEN];
	unsigned x1, x2, y1, y2;

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

	image = ReadImage(filename);
	image = CropImage(image, x1, y1, x2, y2);
	SaveImage("Crop_output", image);

	return 0;

}
