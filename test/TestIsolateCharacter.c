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
  
  
  char index[20];
  char sname[50];

  i=0;
#if 0
  char fname[50] = "Images/CourierNew12_300DPI.ppm";
  image = ReadImage(fname);
  img = CropImage(image,50,200,1400,750);
#else
  char fname[50] = "Images/01_HelloWorld_Clean300DPI.jpg";
  image = ReadImage(fname);
  img = CropImage(image,50,200,1450,1400);
#endif
  imglist = IsolateCharacter(img, 12, 300);
  DeleteImageList(imglist);
 

  return 0;

}
