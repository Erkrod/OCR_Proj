/* Stain Removal testing program */

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
	
	printf("Enter the name of the file: ");
	scanf("%s", filename);

	image = ReadImage(filename);
	StainRemoval(image, 9, 3, 15, 3);
	SaveImage("SR_output", image);

	return 0;
}
