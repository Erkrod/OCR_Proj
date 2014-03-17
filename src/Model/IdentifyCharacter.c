#include "Model.h"
UT_icd CharProbability_icd = {sizeof(CharProbability), NULL, NULL, NULL};
UT_icd CharProfile_icd = {sizeof(CharProfile), NULL, NULL, NULL};

UT_array * IdentifyCharacter( ILIST * imglist, ILIST * Template )// if 0 is lazy, if 1 is hanchel
{
	UT_array * CharProfiles;
	utarray_new(CharProfiles, &CharProfile_icd);
	CharProfile NewCharProfile;
	IENTRY * Curr1 = imglist->First;
	ILIST * CroppedTemplate = NewImageList();;
	IENTRY * tempNode = Template->First;
	IMAGE * tempimage;
	
	while (tempNode)
	{ 	
		int x1, x2;
		int m, n;
		for (m = 0; m < tempNode->Image->Width; m++)
		for (n = 0; n < tempNode->Image->Height; n++)
		{
			if (IsPixelBlack(tempNode->Image, m, n))
			{
				x1 = m;
				goto nextstep1;
			}
		}
		nextstep1:
		for (m = tempNode->Image->Width; m = 0; m--)
		for (n = 0; n < tempNode->Image->Height; n++)
		{
			if (IsPixelBlack(tempNode->Image, m, n))
			{
				x2 = m;
				goto nextstep2;
			}
		}
		nextstep2:
		/*ILIST * templist = NewImageList();*/
		tempimage = CropImage(tempNode->Image, x1, 0, x2, tempNode->Image->Height-1);
		/*templist = ActiveIsolateCharacter(tempNode->Image, CourierNew, 12, 300);*/
		/*AppendImage(CroppedTemplate, templist->First->Image);*/
		AppendImage(CroppedTemplate, tempimage);
		tempNode = tempNode->Next;
	}
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
			NewCharProfile.CharChoices = CharProbabilities;
			utarray_push_back(CharProfiles, &NewCharProfile);
			Curr1 = Curr1->Next;
			continue;
		}
		if (image->Width >= 30)
		{
			temp.Probability = 100;
			temp.Char = " ";
			NewCharProfile.CharChoices = CharProbabilities;
			utarray_push_back(CharProfiles, &NewCharProfile);
			Curr1 = Curr1->Next;
			continue;
		}
		char CharTemplate[100] = "!'#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
		IENTRY * Curr2 = CroppedTemplate->First;
		int Index;
		BlackNWhite(image);
		Index = 0;
		while (Curr2)
		{
			printf("Got here\n");
			int x, y;
			int newx, newy;
			int counter, total;
			counter = 0;
			total = 0;
			unsigned char RTemplate;
			unsigned char RImage;
			assert(image);
			assert(Curr2->Image);
			BlackNWhite(Curr2->Image);
			
			if(Curr2->Image->Height > image->Height)
			{
				newy = image->Height;
			}
			else
			{
				newy = Curr2->Image->Height;
			}
			if(Curr2->Image->Width > image->Width)
			{
				newx = image->Width;
			}
			else
			{
				newx = Curr2->Image->Width;
			}

			for ( y = 0; y < newy; y++)
			for ( x = 0; x < newx; x++)
			{
				RTemplate = GetPixelR(Curr2->Image, x, y);
				RImage = GetPixelR(image, x, y);

				if (abs(RImage - RTemplate) < 20)
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
		NewCharProfile.CharChoices = CharProbabilities;
		utarray_push_back(CharProfiles, &NewCharProfile);
		Curr1 = Curr1->Next;
	}
	return CharProfiles;
}

ILIST * InitializeTemplate(void)
{
	ILIST *template = NewImageList();
	IMAGE *templateimage = NULL;
	int i;
	i = 0;
	while( i < 127 )
	{
		char index[50];
		sprintf(index, "%d", i);
		char tempname[50] = "Fonts/CourierNew12_300DPI/";
		strcat(tempname, index);
		strcat(tempname, ".jpg");
		if (file_exist(tempname))
		{
			templateimage = ReadImage(tempname);
			AppendImage(template, templateimage);
		}
		i++;
	}
	return template;
}