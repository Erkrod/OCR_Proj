/*This file will be used to test a normal workflow of the code
only argument is file name

	- Read an image file
	- Convert to ppm
	- Crop with pre defined parameters
	- Draw 3 lines with pre defined parameters
	- Isolate characters
	- Identify them
	- Post processing (may not by necessary at this stage)

*/

#include "Control.h"
#include "Model.h"

#ifndef TESTCASE
#define TESTCASE 1
#endif

int main(void){
	/*define variables*/
	char ImageName[SLEN * 5];
	IMAGE * image1, * image2;
#if TESTCASE == 0
	strcpy(ImageName, "CourierNew12_300DPI.jpg");
	crop_x1 = 200; crop_y1 = 200; crop_x2 = 1500; crop_y2 = 700;
#elif TESTCASE == 1

#endif

	image1 = ReadImage(ImageName);
	/*crop*/
	image2 = CropImage(image1, crop_x1, crop_y1, crop_x2, crop_y2);
	DeleteImage(image1);
	image1 = image2;
	/*isolate*/	
	ILIST * ilist = IsolateCharacter(image1, CourierNew, 12, 300);
	/*identify*/
	UT_array * WholeString = IdentifyCharacter(ilist, CourierNew, 12, 300);
	/*post processing*/
	UT_string * FinalString = PostProcessing(WholeString);
	/*print it*/
	printf("Final string is:\n%s", utstring_body(FinalString));
	
	
	/*clean up*/
	DeleteImage(image1);
	DeleteImageList(ilist);
	utarray_free(WholeString);
	utstring_free(FinalString);
	

	return 0;
	
	
}
