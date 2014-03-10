#include "Model.h"
UT_icd CharProbability_icd = {sizeof(CharProbability), NULL, NULL, NULL};

UT_array * IdentifyCharacter( IMAGE * image, ILIST * Template )
{
	UT_array * CharProbabilities;
	utarray_new(CharProbabilities, &CharProbability_icd);
	CharProbability * p;
	char CharTemplate[62] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	IENTRY * CurrNode = Template->First;
	int Index;
	
	Index = 0;
	while (CurrNode)
	{
		int x, y;
		int counter, total;
		counter = 0;
		total = 0;
		unsigned char RTemplate, GTemplate, BTemplate;
		unsigned char RImage, GImage, BImage;
		assert(image);
		assert(Template);
		for ( y = 0; y < image->Height; y++)
		for ( x = 0; x < image->Width; x++)
		{
			printf (" x = %d, y = %d \n", x, y);
			RTemplate = GetPixelR(CurrNode->Image, x, y);
			RImage = GetPixelR(image, x, y);
			
			GTemplate = GetPixelG(CurrNode->Image, x, y);
			GImage = GetPixelG(image, x, y);
			
			BTemplate = GetPixelB(CurrNode->Image, x, y);
			BImage = GetPixelB(image, x, y);
			
			if (RTemplate == RImage && GTemplate == GImage && BTemplate == BImage)
			{
				counter++;
			}
			total++;
		}
		p->Char = CharTemplate[Index];
		p->Probability = (counter * 100 / total);
		utarray_push_back(CharProbabilities, p);
		CurrNode = CurrNode->Next;
		Index++;
	}
	return CharProbabilities;
}