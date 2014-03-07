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

#include "/home/group1/EECS22L/EECS22L_Project2/inc/Model/Model.h"

int main()
{
  IMAGE *img = NULL;
  int i;
  int j;
  IMAGE *image = NULL;
  ILIST *imglist = NULL;
  IENTRY *curr;
  char fname[50] = "01_HelloWorld_Clean300DPI";
  char index[20];
  char sname[50];

  i=0;

  image = ReadImage(fname);
  img = Crop(image,275,309,1320,970); /*test crop dimensions for HelloWorld.ppm */
  /*img = Crop(image,50,200,1400,500); test crop dimensions for CourierNew12_300DPI.ppm*/
  imglist = IsolateCharacter(img, 12, 300);
  curr = imglist->First;
  j = SaveImage("meow", img);


  while (curr)
    {
      sprintf(index, "%d", i);
      strcpy(sname, "test");
      strcat(sname, index);
      
      if (curr->Image)
	{
	  j = SaveImage(sname, curr->Image);
	  i++;
	}
      curr = curr->Next;
    }


  return 0;

}
