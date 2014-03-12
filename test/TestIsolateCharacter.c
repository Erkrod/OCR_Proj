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

#define IMAGE_CHOICE 5

int main()
{
  IMAGE *img = NULL;

  IMAGE *image = NULL;
  IMAGE *PreviewImage = NULL, *PreviewImage2 = NULL;
  ILIST *imglist = NULL, *imglist2 = NULL;  

  IENTRY *curr = NULL;
  int i=0;
  int k=0;
  char sname[50];
  char index[50];
 
#if IMAGE_CHOICE == 0
  char fname[50] = "Images/CourierNew12_300DPI.ppm";
  image = ReadImage(fname);
  img = CropImage(image,50,200,1400,750);
#elif IMAGE_CHOICE == 1
  char fname[50] = "Images/01_HelloWorld_Clean300DPI.jpg";
  image = ReadImage(fname);
  img = CropImage(image,50,200,1450,1400);
  SaveImage("Images/Cropped_01_HelloWorld_Clean300DPI", img);
#elif IMAGE_CHOICE == 2
  char fname[50] = "Images/31_OCRtest_Courier_Clean300DPI.jpg";
  image = ReadImage(fname);
  img = CropImage(image,100,250,2150,2750);  
#elif IMAGE_CHOICE == 3
  char fname[50] = "Images/LucidaConsole10_300DPI.jpg";
  image = ReadImage(fname);
  img = CropImage(image,200,200,1000,600); 
#elif IMAGE_CHOICE == 4
  char fname[50] = "Images/11_Eratosthenes_Clean300DPI.png";
  image = ReadImage(fname);
  img = CropImage(image,200,200,1800,3000); 
#elif IMAGE_CHOICE == 5
  char fname[50] = "Images/41_OCRtest_Lucida_Clean300DPI.png";
  image = ReadImage(fname);
  img = CropImage(image,280,200,2000,3000);
#endif
  
#if IMAGE_CHOICE == 0 || IMAGE_CHOICE == 1 || IMAGE_CHOICE == 2
  PreviewImage = PreviewLazyIsolateCharacter(img, CourierNew, 12, 300);
  imglist = LazyIsolateCharacter(img, CourierNew, 12, 300);  
  printf("Finished lazy algorithm\n");
  PreviewImage2 = PreviewActiveIsolateCharacter(img, CourierNew, 12, 300);
  SaveImage("CheckActiveIsolate", PreviewImage2);
  printf("Finished preview active algorithm\n");
  imglist2 = ActiveIsolateCharacter(img, CourierNew, 12, 300);  
  printf("Finished active algorithm\n");
#else
  PreviewImage = PreviewLazyIsolateCharacter(img, LucidaConsole, 10, 300);
  imglist = LazyIsolateCharacter(img, LucidaConsole, 10, 300);
  PreviewImage2 = PreviewActiveIsolateCharacter(img, LucidaConsole, 10, 300);
  imglist2 = ActiveIsolateCharacter(img, LucidaConsole, 10, 300);
#endif
  assert(imglist && PreviewImage && PreviewImage2 && imglist2);
  SaveImage("CheckLazyIsolate", PreviewImage);
  DeleteImage(PreviewImage);
  SaveImage("CheckActiveIsolate", PreviewImage2);
  DeleteImage(PreviewImage2);

  curr = imglist2->First;

  while (curr)
    {
      sprintf(index, "%d", i);
      strcpy(sname, "test");
      strcat(sname, index);
      
      if (curr->Image)
	{
	  SaveImage(sname, curr->Image);
	  i++;
	}
      else /*this 'else' to test if new line NULL indicators are working */
	{
	  printf("%d\n", k);
	  k++;
	}
      curr = curr->Next;
    }
  
  DeleteImageList(imglist);
  DeleteImageList(imglist2);

  return 0;

}
