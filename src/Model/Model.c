#include "model.h"
#include "ImageList.h"
#include "Image.h"
UT_array * IdentifyCharacter( IMAGE * Image, ILIST * Template )
{
	UT_array * CharProbabilities;
	UT_icd CharProbabilities_icd = {sizeof(CharProbability), NULL, NULL, NULL);
	utarray_new(CharProbabilities, &CharProbability_icd);
	CharProbability * p;
	char CharTemplate[93] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890~!@#$%^&*()_+`-={}|[]\\:\"<>?;',./";
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

UT_string * postProcessing(UT_array * charList)
{
  UT_string * output;
  CharProfile * currCharProfile = currCharProfile = (CharProfile *) utarray_next(charList, currCharProfile);
  CharProbability * currCharProbability = (CharProbability *) utarray_next(currCharProfile->CharChoices, currCharProbability);
  int count1 = 1, count2 = 1;
  
  int percentage = currCharProbability->Probability;
  char chosen = currCharProbability->Char;
  
  
  while((currCharProfile = (CharProfile *) utarray_next(charList, currCharProfile)))
  {
    printf("counter 1 = %d\n", count++);
    count2 = 0;
    currCharProbability = NULL;
    
    while((currCharProbability = (CharProbability *) utarray_next(currCharProfile->CharChoices, currCharProbability)))
    {
      printf("counter 2 = %d\n", count2++);
      printf("Character is %c with probability %d\n", currCharProbability->Char, currCharProbability->Probability);
      
      /* found a character with a higher percentage */
/*      if (percentage < currCharProbability->Probability)
      {
	 percentage = currCharProbability->Probability;
	 chosen = currCharProbability->Char;
      }
*/    }
    
    /* adding the chosen character to the string */
/*    utstring_new(output);
    utstring_printf(output, chosen);
*/  }
/*  return output;
*/}
