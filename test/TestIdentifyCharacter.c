#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Model.h"

UT_icd CharProfile_icd = {sizeof(CharProfile), NULL, NULL, NULL};

int main()
{
	int i;
	UT_array * CharProfiles;
	utarray_new(CharProfiles, &CharProfiles_icd);
	char fname1[50] = "Fonts/TestFonts/CourierNew_Test/Courier08.ppm";
	char fname2[50] = "Fonts/TestFonts/CourierNew_Test/Courier09.ppm";
	char fname3[50] = "Fonts/TestFonts/CourierNew_Test/Courier10.ppm";
	IMAGE * image1 = ReadImage(fname1);
	IMAGE * image2 = ReadImage(fname2);
	IMAGE * image3 = ReadImage(fname3);
	ILIST *template = InitializeTemplate(void);
	ILIST *testlist = NewImageList();
	
	CharProfile *Curr1 = (CharProfile*)utarray_front(CharProfiles);
	CharProbability * Curr2 = (CharProbability*)utarray_front(CharProfiles->CharChoices);
	
	AppendImage(testlist, image1);
	AppendImage(testlist, image2);
	AppendImage(testlist, image3);
	CharProfiles = IdentifyCharacter(testlist, template);
	
	i = 0;
	while ( Curr1 )
	{
		printf("---------- For character of index %d ----------\n", i);
		while (Curr2)
		{
			printf("Chance of %c is %d percent.\n", Curr2->Char, Curr2->Probability);
			Curr2 = (CharProfile*)utarray_next(CharProfiles->CharChoices, Curr2);
		}
		Curr1 = (CharProfile*)utarray_next(CharProfiles, Curr1);
		i++;
	}
	return 0;
  }