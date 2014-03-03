#include <stdio.h>
#include <stdlib.h>

#include "Model.h"

int main(void)
{
  UT_array * CharProbabilities;
  /*utarray_new(CharProbabilities , &CharProbability_icd);*/
  
  CharProbability * p;
  
  IMAGE *img = NULL;
  int i;
  int j;
  IMAGE *image = NULL;
  ILIST *imglist = NULL;
  IENTRY *curr;
  char fname[50] = "CourierNew12_300DPI";
  char index[20];
  char sname[50];

  i=0;

  image = ReadImage(fname);
  img = Crop(image,50,200,1400,500);
  imglist = IsolateCharacter(img, 12, 300);
  curr = imglist->First;
  j = SaveImage("meow", img);
  while (curr)
  { UT_array * CharProbabilities;
	CharProbabilities = IdentifyCharacter(curr->Image, imglist);
	 for(p=(CharProbability*) utarray_front(CharProbabilities); p!=NULL; p=(CharProbability*)utarray_next(CharProbability,p)) {
   	printf("Chance of %c is %d percent\n", p->Char, p->Probability);
  }
	curr = curr->Next;
  }
  return 0;
}