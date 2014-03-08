#include "Model.h"
IMAGE * BoxCharacters(IMAGE * image, int fontsize, int scanres)
{
  IMAGE * boxed_image;
  int x,y;
  int a,b;
  unsigned char temp_R, temp_G, temp_B;
  int start_y = 0;
  int x_border_start=-1, x_border_end=-2, old_border_end=-1;
  int char_width = 0, space_width = 0;
  int width = 0;
  int char_height;
  int line, max_lines;
  int y_flag;
  double slice_color = 0.0;

  /* make a copy of image */
  boxed_image = CreateImage(image->Width, image->Height);
  for (y=0; y<image->Height; y++)
    for(x=0; x<image->Width; x++)
      {
	temp_R = GetPixelR(image,x,y);
	temp_G = GetPixelG(image,x,y);
	temp_B = GetPixelB(image,x,y);
	
	SetPixelR(boxed_image,x,y,temp_R);
	SetPixelG(boxed_image,x,y,temp_G);
	SetPixelB(boxed_image,x,y,temp_B);
      }

  char_height = (int)((double)fontsize*(1.0/72.0)*(double)scanres); /*  height of each char = fontsize * (1 inch/ 72 points) * (300 pixels / 1 inch ) */

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
		    }
		  x_border_end = x-1;
		  /* border image & reinitialize x_border_start and x_border_end as -1 */
		  char_width = x_border_end - x_border_start;
		  if (space_width > (char_height/2))
		    {
		      width = space_width;
		      for (a=old_border_end; a < old_border_end + width; a++)
			{
			  /* blacken upper border */
			  SetPixelR(boxed_image, a, start_y, 0);
			  SetPixelG(boxed_image, a, start_y, 0);
			  SetPixelB(boxed_image, a, start_y, 0);

			  /* blacken bottom border */
			  SetPixelR(boxed_image, a, start_y+char_height, 0);
			  SetPixelG(boxed_image, a, start_y+char_height, 0);
			  SetPixelB(boxed_image, a, start_y+char_height, 0);
			}
		      for (b=start_y; b<start_y + char_height; b++)
			{
			  /* blacken left border */
			  SetPixelR(boxed_image, old_border_end, b, 0);
			  SetPixelG(boxed_image, old_border_end, b, 0);
			  SetPixelB(boxed_image, old_border_end, b, 0);	

			  /* blacken right border */
			  SetPixelR(boxed_image, old_border_end+width, b, 0);
			  SetPixelG(boxed_image, old_border_end+width, b, 0);
			  SetPixelB(boxed_image, old_border_end+width, b, 0);			  
			}

		      width = char_width;
		    }
		  else
		    {
		      width = char_width;
		    }

		  for (a=x_border_start; a < x_border_start + width; a++)
		    {
		      /* blacken upper border */
		      SetPixelR(boxed_image, a, start_y, 0);
		      SetPixelG(boxed_image, a, start_y, 0);
		      SetPixelB(boxed_image, a, start_y, 0);

		      /* blacken bottom border */
		      SetPixelR(boxed_image, a, start_y+char_height, 0);
		      SetPixelG(boxed_image, a, start_y+char_height, 0);
		      SetPixelB(boxed_image, a, start_y+char_height, 0);
		    }
		  for (b=start_y; b<start_y + char_height; b++)
		    {
		      /* blacken left border */
		      SetPixelR(boxed_image, x_border_start, b, 0);
		      SetPixelG(boxed_image, x_border_start, b, 0);
		      SetPixelB(boxed_image, x_border_start, b, 0);	

		      /* blacken right border */
		      SetPixelR(boxed_image, x_border_start+width, b, 0);
		      SetPixelG(boxed_image, x_border_start+width, b, 0);
		      SetPixelB(boxed_image, x_border_start+width, b, 0);			  
		    }
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
      space_width = 0;

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
	{
	  break;
	}
    }

  return boxed_image;
}
