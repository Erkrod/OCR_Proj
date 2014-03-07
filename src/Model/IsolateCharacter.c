
#include "Model.h"
ILIST * IsolateCharacter(IMAGE * image, int fontsize, int scanres)
{
  IMAGE * img;
  ILIST * imglist;
  int x,y;
  int start_y = 0;
  int x_border_start=-1, x_border_end=-2, old_border_end=-1;
  int char_width = 0, space_width = 0;
  int width = 0;
  int char_height;
  int line, max_lines;
  int y_flag;
  double slice_color = 0.0;

  char_height = (int)((double)fontsize*(1.0/72.0)*(double)scanres); /*  height of each char = fontsize * (1 inch/ 72 points) * (300 pixels / 1 inch ) */

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

  max_lines = ((image->Height)-start_y)/(1.2*char_height);
  /* printf("max lines is %d. Image height is %d. Start_y is %d.\n", max_lines, image->Height, start_y); */

  /* NOTE: " GETS ISOLATED AS '', SINGLE APOSTROPHES BACK TO BACK. TELL KEVIN OR ANDREW*/
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
		  if (old_border_end != -1) /*at least one character has already been identified, since reinitialization is -1, not -2*/
		    {
		      space_width = x_border_start-old_border_end; /*spaces occur after at least the first character has been ID'd*/
		      /* printf("The x_border_start is %d. The old_border_end is %d.\n", x_border_start, old_border_end); */
		    }
		  x_border_end = x-1;
		  /* append image & reinitialize x_border_start and x_border_end as -1 */
		  char_width = x_border_end - x_border_start;
		  /* printf("Spade Width is %d. Character Width is %d.\n", space_width, char_width); */
		  if (space_width > (char_height/2))
		    {
		      width = space_width;
		      img = Crop(image,old_border_end,start_y,width,char_height);
		      AppendImage(imglist, img);
		      width = char_width;
		      img = Crop(image,x_border_start,start_y,width,char_height);
		      /* printf("!!Space width is %d.\n", width); */
		    }
		  else
		    {
		      width = char_width;
		      img = Crop(image,x_border_start,start_y,width,char_height);
		      /* printf("??Character width is %d.\n", width); */
		    }
		  
		  /* printf("The x_border_start is %d. The x_border_end is %d. The char_width is %d.\n", x_border_start, x_border_end, char_width); */
		  /* printf("space_width is %d. x_border_start is %d. old_border_end is %d.\n", space_width, x_border_start, old_border_end); */

		  AppendImage(imglist, img);
		  old_border_end = x_border_end + 1;
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
      
      old_border_end = -1;
      img = NULL;
      AppendImage(imglist, img);

      /*recalibrate start_y*/
      for ( y=start_y + char_height; y<image->Height; y++ )
	{
	  y_flag = 0;
	  for ( x=0; x<image->Width; x++ )
	    {
	      if (GetPixelR(image,x,y) + GetPixelG(image,x,y) + GetPixelB(image,x,y) < 100)
		{
		  if (y-start_y > 1.2*char_height)
		    {
		      img = NULL;
		      AppendImage(imglist, img);
		    }
		  start_y = y; /*record start scan height, to go slices of fontsize down*/
		  y_flag = start_y;
		  break;
		}
	    }
	  if (y_flag > 0)
	    break;
	}
      if (start_y + char_height > (image->Height-1))
	{
	  break;
	}
    }
  /*printf("The x_border_start is %d. The x_border_end is %d. The char_width is %d.\n", x_border_start, x_border_end, char_width);*/
  /*printf("char height is %d, start_y is %d, image height is %d\n", char_height, start_y, image->Height);*/
  return imglist;
}
