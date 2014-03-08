/* Color Filter testing program */

#include <stdio.h>
#include <stdlib.h>
#include "Model.h"

#define TESTCASE 1

int main(){
	IMAGE *image, *ref_color;
	char filename[SLEN];
	/*int x, y, area_x1, area_x2, area_y1, area_y2, NewPixelValue, threshold;
	unsigned char refr, refg, refb;*/

#if TESTCASE == 0	
	strcpy(filename, "Images/03_HelloWorld_Coffee300DPI.jpg");	
	image = ReadImage(filename);
	ColorFilter(image, 100, 50, 0, 0, image->Width, image->Height, 255, 8);
#elif TESTCASE == 1
	strcpy(filename, "Images/02_HelloWorld_Wrinkles300DPI.jpg");	
	image = ReadImage(filename);
	ColorFilter(image, 100, 50, 0, 0, image->Width, image->Height, 255, 8);
#endif
	SaveImage("CF_output", image);

	return 0;

}
