#include "Model.h"
UT_icd CharProbability_icd = {sizeof(CharProbability), NULL, NULL, NULL};
UT_icd CharProfile_icd = {sizeof(CharProfile), NULL, NULL, NULL};

int CharProbSort(const void *a,const void*b) {
    CharProbability * one = (CharProbability *)a;
    CharProbability * two = (CharProbability *)b;
    
    if (one->Probability > two->Probability) return -1;
    else if (one->Probability == two->Probability) return 0;
    else return 1;
}

int IsNewLine(IMAGE* image)
{
	if (image == NULL)
	return 1;
	else
	return 0;
}

int IsSpace(IMAGE* image, int IsolateAlgorithm)
{
	if (!IsolateAlgorithm)
	{
		int count;
		int x, y;
		count  = 0;
		for (y = 0; y < image->Height; y++)
		for (x = 0; x < image->Width; x++)
		{
			if(IsPixelBlack(image, x, y))
				count++;
		}
		if (count < 5)
			return 1;
		else
			return 0;
	}
	else
	{
		if (image->Width > 30)
			return 1;
		else
			return 0;
	}
}

ILIST * Align(ILIST* imglist)
{
	IENTRY * Curr;
	IMAGE * tempimage;
	ILIST * Alignedimglist;
	int x, y;
	int newx, newy;
	char gothere[50] = "gotHere";
	
	Alignedimglist = NewImageList();
	Curr = imglist->First;
	while (Curr)
	{
		if (IsNewLine(Curr->Image))
		{
			tempimage = NULL;
			AppendImage(Alignedimglist, tempimage);
			Curr = Curr->Next;
			continue;
		}
		for (x = 0; x < Curr->Image->Width; x++)
		for (y = 0; y < Curr->Image->Height; y++)
		{
			if (IsPixelBlack(Curr->Image, x, y))
			{
				newx = x;
				goto nextstep;
			}
		}
		nextstep:
		for (y = 0; y < Curr->Image->Height; y++)
		for (x = 0; x < Curr->Image->Width; x++)
		{
			if (IsPixelBlack(Curr->Image, x, y))
			{
				newy = y;
				goto nextstep1;
			}
		}
		nextstep1:
		tempimage = CropImage(Curr->Image, newx, newy, Curr->Image->Width-1, Curr->Image->Height-1);
		AppendImage(Alignedimglist, tempimage);
		SaveImage(gothere, Curr->Image);
		Curr = Curr->Next;
	}
	return Alignedimglist;
}

UT_array * IdentifyCharacter( ILIST * imglist, ILIST * Template, int IsolateAlgorithm )// 0 is lazy
{
	#if 0
	utarray_new(CharProfiles, &CharProfile_icd);
	CharProfile NewCharProfile;
	CharProbability temp;
	ILIST * CroppedTemplate = NewImageList();
	ILIST * Croppedimglist = NewImageList();
	IENTRY * Curr1;
	IENTRY * tempNode = Template->First;
	IENTRY * tempNode1 = imglist->First;
	IMAGE * tempimage;
	IMAGE * tempimage1;

	next:
	while (tempNode1)
	{ 	
		int x1, x2;
		int y1;
		int m, n;
			if (tempNode1->Image == NULL)
			{
				temp.Probability = 100;
				temp.Char = "\n";
				utarray_push_back(CharProbabilities, &temp);
				NewCharProfile.CharChoices = CharProbabilities;
				tempNode1 = tempNode1->Next;
				goto next;
			}
			if (tempNode1->Image->Width < 3)
			{
				tempNode1 = tempNode1->Next;
				goto next;
			}
			
		for (n = 0; n < tempNode1->Image->Height; n++)
		for (m = 0; m < tempNode1->Image->Width; m++)
		{
			if (IsPixelBlack(tempNode1->Image, m, n))
			{
				y1 = n;
				goto nextstep;
			}
		}
		nextstep:
		for (m = 0; m < tempNode1->Image->Width; m++)
		for (n = 0; n < tempNode1->Image->Height; n++)
		{
			if (IsPixelBlack(tempNode1->Image, m, n))
			{
				x1 = m;
				goto nextstep1;
			}
		}
		nextstep1:
		if (y1 < 3)
		{
			tempNode1 = tempNode1->Next;
			continue;
		}
		tempimage1 = CropImage(tempNode1->Image, x1, y1, tempNode1->Image->Width-1, tempNode1->Image->Height-1);
		AppendImage(Croppedimglist, tempimage1);
		Curr1 = Croppedimglist->First;
		tempNode1 = tempNode1->Next;
	}
	while (tempNode)
	{ 	
		int x1, x2;
		int y1;
		int m, n;

		for (n = 0; n < tempNode->Image->Height; n++)
		for (m = 0; m < tempNode->Image->Width; m++)
		{
			if (IsPixelBlack(tempNode->Image, m, n))
			{
				y1 = n;
				goto nextstep3;
			}
		}
		nextstep3:
		for (m = 0; m < tempNode->Image->Width; m++)
		for (n = 0; n < tempNode->Image->Height; n++)
		{
			if (IsPixelBlack(tempNode->Image, m, n))
			{
				x1 = m;
				goto nextstep4;
			}
		}
		nextstep4:
		m = tempNode->Image->Width-1;
		for (m; m >= 0; m--)
		for (n = 0; n < tempNode->Image->Height; n++)
		{
			if (IsPixelBlack(tempNode->Image, m, n))
			{
				x2 = m;
				goto nextstep5;
			}
		}
		nextstep5:
		tempimage = CropImage(tempNode->Image, x1, 0, tempNode->Image->Width-1, tempNode->Image->Height-1);
		AppendImage(CroppedTemplate, tempimage);
		tempNode = tempNode->Next;
	}
	while (Curr1)
	{
		UT_array * CharProbabilities;
		utarray_new(CharProbabilities, &CharProbability_icd);
		IMAGE * image = Curr1->Image;
		if (image == NULL)
		{
			temp.Probability = 100;
			temp.Char = "\n";
			utarray_push_back(CharProbabilities, &temp);
			NewCharProfile.CharChoices = CharProbabilities;
			utarray_push_back(CharProfiles, &NewCharProfile);
			Curr1 = Curr1->Next;
			continue;
		}
		if (image->Width > 30)
		{
			temp.Probability = 100;
			temp.Char = " ";
			utarray_push_back(CharProbabilities, &temp);
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
			int count;
		

			
			
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

				/*if (abs(RImage - RTemplate) < 20 && RImage>20)*/
				if (abs(RImage-RTemplate) < 10)
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
		utarray_sort(CharProbabilities, CharProbSort);
		utarray_push_back(CharProfiles, &NewCharProfile);
		Curr1 = Curr1->Next;
	}
#endif	

	UT_array * CharProfiles;
	utarray_new(CharProfiles, &CharProfile_icd);
	CharProfile NewCharProfile;
	UT_array * CharProbabilities;
	utarray_new(CharProbabilities, &CharProbability_icd);
	CharProbability temp;
	IENTRY * Curr1;
	IENTRY * Curr2;
	IENTRY * Curr3;
	ILIST * AlignedTemplate;
	ILIST * Alignedimglist;


	AlignedTemplate = Align(Template);
	Alignedimglist = Align(imglist);
	Curr1 = imglist->First;
	Curr2 = Alignedimglist->First;
	Curr3 = AlignedTemplate->First;

	while(Curr1)
	{
		if (IsNewLine(Curr1->Image))
		{
			temp.Probability = 100;
			temp.Char = '\n';
			utarray_push_back(CharProbabilities, &temp);
		}
		else if (Curr1->Image->Width < 3 || Curr1->Image->Height < 3)
		{
			Curr1 = Curr1->Next;
			Curr2 = Curr2->Next;
			continue;
		}
		else if (IsSpace(Curr1->Image, IsolateAlgorithm))
		{
			temp.Probability = 100;
			temp.Char = ' ';
			utarray_push_back(CharProbabilities, &temp);
		}
		else
		{
			int Index;
			char CharTemplate[100] = "!'#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
			Index = 0;

			while (Curr3)
			{
				int x, y, newx, newy;
				int counter, total;
				unsigned char RImage, RTemplate;
				counter = 0;
				total = 0;

				if(Curr2->Image->Height > Curr3->Image->Height)
				{
					newy = Curr3->Image->Height;
				}
				else
				{
					newy = Curr2->Image->Height;
				}
				if(Curr2->Image->Width > Curr3->Image->Width)
				{
					newx = Curr3->Image->Width;
				}
				else
				{
					newx = Curr2->Image->Width;
				}

				for ( y = 0; y < newy; y++ )
				for ( x = 0; x < newx; x++ )
				{
					RImage = GetPixelR(Curr2->Image, x, y);
					RTemplate = GetPixelR(Curr3->Image, x, y);
					if (abs(RImage - RTemplate) < 20)
					{
						counter++;
					}
					total++;
				}
				temp.Char = CharTemplate[Index];
				temp.Probability = (counter * 100 / total);
				utarray_push_back(CharProbabilities, &temp);
				Curr3 = Curr3->Next;
				Index++;
			}
		}
		NewCharProfile.CharChoices = CharProbabilities;
		utarray_sort(CharProbabilities, CharProbSort);
		utarray_push_back(CharProfiles, &NewCharProfile);
		Curr1 = Curr1->Next;
		Curr2 = Curr2->Next;
	}	
	return CharProfiles;
}

ILIST * InitializeTemplateCourier(void)
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

ILIST * InitializeTemplateLucida(void)
{
	ILIST *template = NewImageList();
	IMAGE *templateimage = NULL;
	int i;
	i = 0;
	while( i < 127 )
	{
		char index[50];
		sprintf(index, "%d", i);
		char tempname[50] = "Fonts/LucidaConsole10_300DPI/";
		strcat(tempname, index);
		strcat(tempname, ".png");
		if (file_exist(tempname))
		{
			templateimage = ReadImage(tempname);
			AppendImage(template, templateimage);
		}
		i++;
	}
	return template;
}
