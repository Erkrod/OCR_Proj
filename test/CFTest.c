/* Color Filter testing program */

#include <stdio.h>
#include <stdlib.h>
#include "Constants.h"
#include "Image.h"
#include "FileIO.h"
#include "Dips.h"
#include "Constants.h"

int main(){
	IMAGE *image, *ref_color;
	char filename[SLEN];
	int x, y, area_x1, area_x2, area_y1, area_y2, NewPixelValue, threshold;
	unsigned char refr, refg, refb;

	printf("Enter the name of the file: ");
	scanf("%s", filename);

	image = ReadImage(filename);
	ColorFilter(image, 100, 50, 0, 0, image->Width, image->Height, 255, 8);
	SaveImage("CF_output", image);

	return 0;

}
