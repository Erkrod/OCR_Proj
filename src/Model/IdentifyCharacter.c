#include "Model.h"
UT_icd CharProbability_icd = {sizeof(CharProbability), NULL, NULL, NULL};
UT_icd CharProfile_icd = {sizeof(CharProfile), NULL, NULL, NULL};

UT_array * IdentifyCharacter( ILIST * imglist, ILIST * Template )
{
	UT_array * CharProfiles;
	utarray_new(CharProfiles, &CharProfile_icd);
	IENTRY * Curr1 = imglist;
	while (Curr1)
	{
		UT_array * CharProbabilities;
		utarray_new(CharProbabilities, &CharProbability_icd);
		CharProbability temp;
		IMAGE * image = Curr1->Image;
		if (image == NULL)
		{
			temp.Probability = 100;
			temp.Char = "\n";
			Curr1 = Curr1->Next;
			continue;
		}
		char CharTemplate[62] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
		IENTRY * Curr2 = Template->First;
		int Index;
		IMAGE *newimage = Resize(image, Curr2->Image->Width, Curr2->Image->Height);
		BlackNWhite(newimage);
		Index = 0;
		while (Curr2)
		{
			int x, y;
			int newx, newy;
			int counter, total;
			counter = 0;
			total = 0;
			unsigned char RTemplate, GTemplate, BTemplate;
			unsigned char RImage, GImage, BImage;
			assert(image);
			assert(newimage);
			assert(Template);
			BlackNWhite(Curr2->Image);
			// if (image->Height > Curr2->Image->Height)
			// {newy = Curr2->Image->Height;}
			// else
			// {newy = image->Height;}
			
			// if (image->Width > Curr2->Image->Width)
			// {newx = Curr2->Image->Width;}
			// else
			// {newx = image->Width;}
			
			for ( y = 0; y < newimage->Height; y++)
			for ( x = 0; x < newimage->Width; x++)
			// for ( y = 0; y < newy; y++ )
			// for ( x = 0; x < newx; x++ )
			{
				RTemplate = GetPixelR(Curr2->Image, x, y);
				RImage = GetPixelR(newimage, x, y);
				
				GTemplate = GetPixelG(Curr2->Image, x, y);
				GImage = GetPixelG(newimage, x, y);
				
				BTemplate = GetPixelB(Curr2->Image, x, y);
				BImage = GetPixelB(newimage, x, y);
				
				if (RImage > 220 && RTemplate > 220 && GImage > 220 && GTemplate > 220 && BImage > 220 && BTemplate > 220)
				{
					counter++;
				}
				total++;
			}
			temp.Char = CharTemplate[Index];
			temp.Probability = (counter * 100 / total);
			utarray_push_back(CharProbabilities, &temp);
			Curr2 = Curr2->Next;
			Index++;
		}
		utarray_push_back(CharProfiles, CharProbabilities);
		Curr1 = Curr1->Next;
	}
	return CharProfiles;
}

ILIST * InitializeTemplate(void)
{
  ILIST *template = NewImageList();
  IMAGE *templateimage = NULL;
  int i;
	while( i < 95 )
	{
		char index[50];
		sprintf(index, "%d", i);
		
		char tempname[50] = "Fonts/CourierNew12_300DPI/";
		strcat(tempname, index);
		strcat(tempname, ".jpg");
		templateimage = ReadImage(tempname);
		AppendImage(template, templateimage);
		i++;
	}
}