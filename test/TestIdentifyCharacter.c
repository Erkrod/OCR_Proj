#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Model.h"
#define TEST_CHOICE 0    /* <<<<<<<<<<---------------- Change test there ~~~~~~~~~~~~ */


int main()
{
	int i;
	UT_array * CharProfiles;
	utarray_new(CharProfiles, &CharProfile_icd);
	
	IMAGE *img = NULL;
	IMAGE *image = NULL;
	IMAGE *PreviewImage = NULL;
	ILIST *imglist = NULL;

#if TEST_CHOICE == 0 || TEST_CHOICE == 1
	char fname[50] = "Images/01_HelloWorld_Clean300DPI.jpg";
	image = ReadImage(fname);
	img = CropImage(image,50,200,1450,1400);
	SaveImage("img", img);
	ILIST *template = InitializeTemplateCourier();
#elif TEST_CHOICE == 2 || TEST_CHOICE == 3
	char fname[50] = "Images/41_OCRtest_Lucida_Clean300DPI.png";
	image = ReadImage(fname);
  	img = CropImage(image,280,200,2000,3000);
	SaveImage("img", img);
	ILIST *template = InitializeTemplateLucida();
#endif
#if TEST_CHOICE == 0
	PreviewImage = PreviewLazyIsolateCharacter(img, CourierNew, 12, 300);
	SaveImage("CheckLazyIsolateCourier", PreviewImage);
	imglist = LazyIsolateCharacter(img, CourierNew, 12, 300);  
	assert(imglist && PreviewImage);
	DeleteImage(PreviewImage);
	CharProfiles = IdentifyCharacter(imglist, template, 0);
#elif TEST_CHOICE == 1
	PreviewImage = PreviewActiveIsolateCharacter(img, CourierNew, 12, 300);
	SaveImage("CheckActiveIsolateCourier", PreviewImage);
	imglist = ActiveIsolateCharacter(img, CourierNew, 12, 300);  
	assert(imglist && PreviewImage);
	DeleteImage(PreviewImage);
	CharProfiles = IdentifyCharacter(imglist, template, 1);
#elif TEST_CHOICE == 2
	PreviewImage = PreviewLazyIsolateCharacter(img, LucidaConsole, 10, 300);
	SaveImage("CheckLazyIsolateLucida", PreviewImage);
	imglist = LazyIsolateCharacter(img, LucidaConsole, 10, 300);  
	assert(imglist && PreviewImage);
	DeleteImage(PreviewImage);
	CharProfiles = IdentifyCharacter(imglist, template, 0);
#elif TEST_CHOICE == 3
	PreviewImage = PreviewActiveIsolateCharacter(img, LucidaConsole, 10, 300);
	SaveImage("CheckActiveIsolateLucida", PreviewImage);
	imglist = LazyIsolateCharacter(img, LucidaConsole, 10, 300);  
	assert(imglist && PreviewImage);
	DeleteImage(PreviewImage);
	CharProfiles = IdentifyCharacter(imglist, template, 0);
#endif

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
