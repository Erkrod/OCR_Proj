#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "/home/group1/EECS22L/EECS22L_Project2/inc/Model/Model.h"

int main()
{
  IMAGE *img = NULL;

  int j;
  int k = 0;
  IMAGE *image = NULL;
  IMAGE *boxed_image = NULL;

  char fname[50] = "01_HelloWorld_Clean300DPI";
  char index[20];
  char sname[50];

  image = ReadImage(fname);
  img = Crop(image,275,309,1320,970); /*test crop dimensions for HelloWorld.ppm */
  /*img = Crop(image,50,200,1400,500); test crop dimensions for CourierNew12_300DPI.ppm*/
  boxed_image = BoxCharacters(img, 12, 300);
  j = SaveImage("meow", img);
  k = SaveImage("BoxedImage",boxed_image);

  return 0;

}
