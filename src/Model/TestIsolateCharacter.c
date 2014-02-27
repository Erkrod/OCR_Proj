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
  
  int i;
  int j;
  IMAGE *image = NULL;
  ILIST *imglist = NULL;
  IENTRY *curr;
  char fname[50] = "CourierNew12_300DPI";
  char index[20];
  char sname[50];

  i=0;
  curr = imglist->First;
  

  image = ReadImage(fname);
  imglist = IsolateCharacter(image, 12, 300);


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
