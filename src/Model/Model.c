#include "Model.h"



ILIST * IsolateCharacter(IMAGE * image, int fontsize, int scanres)
{
  IMAGE * img;
  ILIST * imglist;
  int x,y;
  int start_y = 0;
  int i_max;
  int x_border_start=-1, x_border_end=-1;
  int char_width;
  int char_height;
  int i;
  double slice_color = 0.0;

  imglist = NewImageList();

  for ( y=0; y<image->Height; y++ )
    {
    for ( x=0; x<image->Width; x++ )
      {
	if (GetPixelR(image,x,y) + GetPixelG(image,x,y) + GetPixelB(image,x,y) < 100)
	  {
	    start_y = y; /*record start scan height, to go slices of fontsize down*/
	    break;
	  }
      }
    if (start_y > 0)
      break;
    }
  
  char_height = (int)((double)fontsize*(1.0/72.0)*(double)scanres); /*  height of each char = fontsize * (1 inch/ 72 points) * (300 pixels / 1 inch ) */
  i_max = (image->Height-start_y)/char_height;
  
  for ( i=1; i<i_max; i++)
    {
      for ( x=0; x<image->Width; x++)
	{
	  slice_color = 0.0;
	  for ( y=start_y*i; y<start_y*i+char_height; y++ )
	    {
	      slice_color = slice_color+ GetPixelR(image,x,y) + GetPixelG(image,x,y) + GetPixelB(image,x,y);
	    }
	  if ( slice_color > 37000.0) /* darker shades, leaning towards  black */
	    {
	      if (x_border_start != -1) /*border start has already been defined*/
		{
		  x_border_end = x-1;
		  break;
		}
	    }
	  else /* there exists char here */
	    {
	      if ((x > 235) && (x <265))
	      printf("x coordinate is %d and slice color is %lf\n", x,slice_color);
	      if (x_border_start == -1)
		x_border_start = x-1; 
	    }
	} /*for x*/
      if (x_border_end != -1) /* border start and end has been defined*/
	break;
    }
  char_width = x_border_end - x_border_start;
  for ( y=start_y; y<(image->Height-start_y-char_height); y=y+char_height )
    for ( x=x_border_start; x < image->Width-char_width; x=x+char_width)
      {
	img = Crop(image,x,y,char_width,char_height);
	AppendImage(imglist, img);
      }

  printf("The x_border_start is %d. The x_border_end is %d. The char_width is %d.\n", x_border_start, x_border_end, char_width);
  printf("char height is %d, start_y is %d, image height is %d\n", char_height, start_y, image->Height);
  return imglist;
}
