/*this file will be used to test isolate characters
Command line arguments should be like this:
<top first line> <bottom first line> <top second line>
top first line: the number of pixel from top to top of first line
bottom fist line: the number of pixel from top to bottom of first line
top second line: the number of pixel from top to bottom of first line
Output will be multiple ppm files, each file represents a character you isolate, space also counts. Images name should be number from 0.ppm or 1.ppm

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Model.h"

int main()
{
  IMAGE *img = NULL;
  int i;
  int j;
  IMAGE *image = NULL;
  ILIST *imglist = NULL;
  IENTRY *curr;
  char fname[50] = "Images/CourierNew12_300DPI.ppm";
  char index[20];
  char sname[50];

  i=0;

  image = ReadImage(fname);
  img = CropImage(image,50,200,1450,700);
  imglist = IsolateCharacter(img, 12, 300);
  curr = imglist->First;
  j = SaveImage("meow", img);


  while (curr)
    {
      sprintf(index, "%d", i);
      strcpy(sname, "test");
      strcat(sname, index);
      
      j = SaveImage(sname, curr->Image);
      curr = curr->Next;
      i++;
      
    }


  return 0;

}
