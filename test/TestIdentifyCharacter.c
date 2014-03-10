#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Model.h"

int main()
{
	int i;
	UT_array * CharProfiles;
	utarray_new(CharProfiles, &CharProfile_icd);
	char fname1[50] = "Fonts/CourierNew12_300DPI/48.jpg";	/*Comparing with 0*/
	char fname2[50] = "Fonts/CourierNew12_300DPI/79.jpg";	/*Comparing with O*/
	char fname3[50] = "Fonts/CourierNew12_300DPI/111.jpg";	/*Comparing with o*/
	IMAGE * image1 = ReadImage(fname1);
	IMAGE * image2 = ReadImage(fname2);
	IMAGE * image3 = ReadImage(fname3);
	ILIST *template = InitializeTemplate();
	ILIST *testlist = NewImageList();

	AppendImage(testlist, image1);
	AppendImage(testlist, image2);
	AppendImage(testlist, image3);
	CharProfiles = IdentifyCharacter(testlist, template);
	
	CharProfile *Curr1 = (CharProfile*)utarray_front(CharProfiles);
	i = 0;
	while ( Curr1 )
	{
		printf("---------- For character of index %d ----------\n", i);
		CharProbability * Curr2 = (CharProbability*)utarray_front(Curr1->CharChoices);
		while (Curr2)
		{
			printf("Chance of %c is %d percent.\n", Curr2->Char, Curr2->Probability);
			Curr2 = (CharProbability*)utarray_next(Curr1->CharChoices, Curr2);
		}
		Curr1 = (CharProfile*)utarray_next(CharProfiles, Curr1);
		i++;
	}
	return 0;
  }
