#include "Model.h"



ILIST * IsolateCharacter(IMAGE * image, int fontsize, int scanres)
{
  IMAGE * img;
  ILIST * imglist;
  int x,y;
  int start_y;
  int i_max;
  int x_border_start, x_border_end;
  int char_width;
  int char_flag;
  int char_height;
  int i;

  imglist = NewImageList();

  for ( y=0; y<image->Height; y++ )
    for ( x=0; x<image->Width; x++ )
      {
	if (GetPixelR(image,x,y) + GetPixelG(image,x,y) + GetPixelB(image,x,y) != 0)
	  start_y = y; /*record start scan height, to go slices of fontsize down*/
      }
  
  char_height = fontsize*(1/72)*scanres; /*  height of each char = fontsize * (1 inch/ 72 points) * (300 pixels / 1 inch ) */
  i_max = (image->Height)/char_height;

  for ( i=1; i<=i_max; i++)
    {
      char_flag = 0;
      for ( x=0; x<image->Width; x++)
	{
	  for ( y=start_y*i; y<start_y*i+char_height; y++ )
	    {
	      if ( GetPixelR(image,x,y) + GetPixelG(image,x,y) + GetPixelB(image,x,y) != 0)
		char_flag = 1; /* there exists char here */
	      else
		{
		  if (char_flag == 1)
		    x_border_end = x-1;
		}
	    }
	  if (char_flag == 1)
	    x_border_start = x-1;
	}
      char_width = x_border_end - x_border_start;
      for ( x=x_border_start; x < image->Width; x=x+char_width)
	{
	  img = Crop(image,x,start_y*i,char_width,char_height);
	  AppendImage(imglist, img);
	}
    }
}
