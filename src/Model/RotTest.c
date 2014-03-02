#include "Image.h"
#include "FileIO.h"
#include "Dips.h"
#include "Constants.h"
#include <stdlib.h>
#include <stdio.h>

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

	SaveImage("output", image);

	system("eog output.ppm; rm output.ppm");	

	return 0;
}
