/*this file will be used to test isolate characters
Command line arguments should be like this:
<top first line> <bottom first line> <top second line>
top first line: the number of pixel from top to top of first line
bottom fist line: the number of pixel from top to bottom of first line
top second line: the number of pixel from top to bottom of first line
Output will be multiple ppm files, each file represents a character you isolate, space also counts. Images name should be number from 0.ppm or 1.ppm

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Model.h"

int main()
{
	UT_array * CharProbabilities;
	CharProbability * p;
	ILIST * Template;
	IENTRY * Curr;
	IMAGE * Image;
	int i;
	int test;
	
	i = 0;
	ILIST * Template = NewImageList();
	while (i < 94)
	{
		strcpy(fname, "Fonts\CourierNew12_300DPI\\");
		strcat(fname, i);
		strcat(fname, ".jpg");
		Image = ReadImage(fname);
		AppendImage(Template, Image);
		i++
	}
	
	test = 5;					/* Change this number as wanted. Make sure it is less than 94 */
	i = 0;
	Curr = Template->First;
	
	while (i < test)			/* Iterating though list */
	Curr = Curr->Next;
	
	CharProbabilities = IdentifyCharacter(curr->Image, Template);	/* Creating the array of character probabilities */
	
	/* Go through every element in array of character probability and display it. */
	for(p =(CharProbability*)utarray_front(CharProbabilities); p!=NULL; p=(CharProbability*)utarray_next(CharProbability,p))
	{
		printf("Chance of %c is %d percent\n", p->Char, p->Probability);
	}
	return 0;
 }

