#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Model.h"

int main()
{
  UT_array * CharProbabilities;
  IMAGE *image = NULL;
  ILIST *template = NewImageList();
  IMAGE *templateimage = NULL;
  CharProbability *curr;
  int i;
  char fname[50] = "\Fonts\TestFonts\CourierNew_Test\1.ppm";  
  i=1;
	while( i < 95 )
	{
		char index;
		sprintf(index, "%d", i);
		
		char tempname[50] = "\Fonts\CourierNew12_300D\\";
		strcat(tempname, index);
		strcat(tempname, ".jpg");
		templateimage = ReadImage(tempname);
		AppendImage(template, templateimage);
	}
    image = ReadImage(fname);
  	CharProbabilities = IdentifyCharacter(image, template);
	curr = (CharProbability*)utarray_front(CharProbabilities);
	while (curr)
	{
		printf("Chance of %c is %d percent\n", curr->Char, curr->Probability);
		curr = (CharProbability*)utarray_next(CharProbabilities, curr);
	}
	return 0;
  }