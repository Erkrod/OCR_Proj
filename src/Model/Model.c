#include "Model.h"



ILIST * IsolateCharacter(IMAGE * image, int fontsize, int scanres)
{
  IMAGE * img;
  ILIST * imglist;
  int x,y;
  int start_y = -1;
  int y_white_start = -1, y_white_end = -1, whitespace_height;
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
	    if (start_y == -1)
	      start_y = y; /*record start scan height, to go slices of fontsize down*/
	    if (y_white_start != -1)
	      y_white_end = y-1;
	    break;
	  }
	else
	  {
	    if ((x == image->Width-1) && (y_white_start == -1) && (start_y != -1)) /*after finding a line of characters, scan reached end of new line and no shade of black found */
	      y_white_start = y;
	  }
      }
    if (y_white_end != -1)
      {
	whitespace_height = y_white_end - y_white_start;
	break;
      }
    }
  
  char_height = (int)((double)fontsize*(1.0/72.0)*(double)scanres); /*  height of each char = fontsize * (1 inch/ 72 points) * (300 pixels / 1 inch ) */
  i_max = (image->Height-start_y)/(char_height+whitespace_height);
  
  printf("y_white_start is %d, y_white_end is %d.\n", y_white_start, y_white_end);
  
  for ( i=1; i<i_max; i++)
    {
      for ( x=0; x<image->Width; x++)
	{
	  slice_color = 0.0;
	  for ( y=start_y*i; y<start_y*i+(char_height); y++ )
	    {
	      slice_color = slice_color+ GetPixelR(image,x,y) + GetPixelG(image,x,y) + GetPixelB(image,x,y);
	    }
	  if ( slice_color > 37000.0) /* light shades, leaning towards white -- THIS TEST METHOD NEEDS TO BE IMPROVED*/
	    {
	      if (x_border_start != -1) /*character border start has already been defined*/
		{
		  x_border_end = x-1;
		  break;
		  /*
		  if (x_border_end == -1)
		    {
		      x_border_end = x-1;
		      char_width = x_border_end - x_border_start;
		      img = Crop(image,x_border_start,y,char_width,char_height);
		      AppendImage(imglist,img);
		      x_border_start = -1;
		      x_border_end = -1;
		    }
		  */
		}
	    }
	  else /* there exists char here */
	    {
	      if (x_border_start == -1)
		x_border_start = x-1;
	    }
	} /*for x*/
      if (x_border_end != -1) /* character border start and end and whitespace start and end have been defined */
	break;
    }
  char_width = x_border_end - x_border_start;
  /* whitespace_width = white_border_end - white_border_start;*/
  for ( y=start_y; y<(image->Height-start_y-char_height-whitespace_height); y=y+char_height+whitespace_height )
    for ( x=x_border_start; x < image->Width-(char_width); x=x+char_width)
      {
	img = Crop(image,x,y,char_width,char_height);
	AppendImage(imglist, img);
	}

  printf("The x_border_start is %d. The x_border_end is %d. The char_width is %d.\n", x_border_start, x_border_end, char_width);
  printf("char height is %d, start_y is %d, image height is %d\n", char_height, start_y, image->Height);
  printf("imax is %d.\n", i_max);
  return imglist;
}
