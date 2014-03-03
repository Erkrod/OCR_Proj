#include "Model.h"



UT_array * IdentifyCharacter( IMAGE * Image, ILIST * Template )
{
	UT_array * CharProbabilities;
	UT_icd CharProbabilities_icd = {sizeof(CharProbability), NULL, NULL, NULL);
	utarray_new(CharProbabilities, &CharProbability_icd);
	CharProbability * p;
	char CharTemplate[94] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890~!@#$%^&*()_+`-={}|[]\\:\"<>?;',./";
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
		
		for ( y = 0; y < Image->Height; y++)
		for ( x = 0; x < Image->Width; x++)
		{
			RTemplate = GetPixelR(CurrNode->Image, x, y);
			RImage = GetPixelR(Image, x, y);
			
			GTemplate = GetPixelG(CurrNode->Image, x, y);
			GImage = GetPixelG(Image, x, y);
			
			BTemplate = GetPixelB(CurrNode->Image, x, y);
			BIMage = GetPixelB(Image, x, y);
			
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