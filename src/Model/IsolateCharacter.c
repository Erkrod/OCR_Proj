#include "Model.h"
ILIST * IsolateCharacter(IMAGE * image, int fontsize, int scanres)
{
  IMAGE * img;
  ILIST * imglist;
  int x,y;
  int start_y = 0;
  int x_border_start=-1, x_border_end=-1;
  int char_width;
  int char_height;
  int line, max_lines;
  int y_flag;
  double slice_color = 0.0;

  char_height = (int)((double)fontsize*(1.0/72.0)*(double)scanres); /*  height of each char = fontsize * (1 inch/ 72 points) * (300 pixels / 1 inch ) */
  max_lines = (image->Height-start_y)/char_height;

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
  /* FIXXXXXXX MEEEE these two 'for' loops above and below can be merged maybe? */

  for ( line=0; line<max_lines; line++)
    {
      for ( x=0; x<image->Width; x++)
	{
	  slice_color = 0.0;
	  for ( y=start_y; y<start_y+char_height; y++ )
	    {
	      slice_color = slice_color+ GetPixelR(image,x,y) + GetPixelG(image,x,y) + GetPixelB(image,x,y);
	    }
	  if ( slice_color > 37000.0) /* lighter shades, leaning towards white*/
	    {
	      if (x_border_start != -1) /*border start has already been defined*/
		{
		  x_border_end = x-1;
		  /* append image & reinitialize x_border_start and x_border_end as -1 */
		  char_width = x_border_end - x_border_start;
		  img = Crop(image,x_border_start,start_y,char_width,char_height);
		  AppendImage(imglist, img);
		  x_border_start = -1;
		  x_border_end = -1;
		}
	    }
	  else /* there exists char here */
	    {
	      if (x_border_start == -1)
		x_border_start = x-1; 
	    }
	} /*for x*/

      /*recalibrate start_y*/
      for ( y=start_y + char_height; y<image->Height; y++ )
	{
	  y_flag = 0;
	  for ( x=0; x<image->Width; x++ )
	    {
	      if (GetPixelR(image,x,y) + GetPixelG(image,x,y) + GetPixelB(image,x,y) < 100)
		{
		  start_y = y; /*record start scan height, to go slices of fontsize down*/
		  y_flag = start_y;
		  break;
		}
	    }
	  if (y_flag > 0)
	    break;
	}
      if (start_y + char_height > (image->Height-1))
	break;
    }
  /*
  char_width = x_border_end - x_border_start;
  IMAGE * TempImage;
  for ( y=start_y; y<(image->Height-start_y-char_height); y=y+char_height )
    for ( x=x_border_start; x < image->Width-char_width; x=x+char_width)
      {
	TempImage = DuplicateImage(image);
	img = CropImage(TempImage,x,y,x+char_width,y+char_height);
	AppendImage(imglist, img);
      }
  */
  /*printf("The x_border_start is %d. The x_border_end is %d. The char_width is %d.\n", x_border_start, x_border_end, char_width);*/
  /*printf("char height is %d, start_y is %d, image height is %d\n", char_height, start_y, image->Height);*/
  return imglist;
}
