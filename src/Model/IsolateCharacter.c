#include "Model.h"


/***********************************************************
 *			LAZY ISOLATE CHARACTER
 ***********************************************************/
int IsPixelBlack(IMAGE * image, int x, int y){
	if (GetPixelR(image, x, y) >= 50) return 0;
	if (GetPixelG(image, x, y) >= 50) return 0;
	if (GetPixelB(image, x, y) >= 50) return 0;
	return 1;
	/*if (GetPixelR(image, x, y) < 10 && GetPixelG(image, x, y) < 10 && GetPixelB(image, x, y) < 10) return 1;
	return 0;*/
}

void GetIsolateCharacterConstant(FontType Font, int fontsize, int scanres, double * FontHeight, double * FontWidth, double * FontHeightSpace, double * FontWidthSpace, int * TopOffset, int * LeftOffset, int * RightOffset, int * BottomOffset){
	if (Font == CourierNew && fontsize == 12 && scanres == 300){
		*FontHeight = 47.4; 
		*FontWidth = 28.1;
		*FontHeightSpace = 9.1; 
		*FontWidthSpace = 1.80;
		*TopOffset = 7;
		*LeftOffset = 7;
		*RightOffset = 0;
		*BottomOffset = 20;
	} else if (Font == LucidaConsole && fontsize == 10 && scanres == 300){
		*FontHeight = 40.425; 
		*FontWidth = 24;
		*FontHeightSpace = 1.10; 
		*FontWidthSpace = 1.1;
		*TopOffset = 4;
		*LeftOffset = 4;
		*RightOffset = 0;
		*BottomOffset = 7;
	}
}

void GetMargins(IMAGE * image, int TopOffset, int LeftOffset, int RightOffset, int BottomOffset, int * TopMargin, int * LeftMargin, int * RightMargin, int * BottomMargin){
	
	int i, j, BlackPixelCount;
	
	/*find top margin*/
	for (i = 0; i < image->Height && *TopMargin == -1; i++){
		BlackPixelCount = 0;
		for (j = 0; j < image->Width && *TopMargin == -1; j++){
			if (IsPixelBlack(image, j, i)) BlackPixelCount++;
			if (BlackPixelCount > 2) {
				*TopMargin = i >= TopOffset ? i - TopOffset : 0;
			}
		}
	}

	assert(*TopMargin > -1);
	
	/*find bottom margin*/
	for (i = image->Height-1; i > *TopMargin && *BottomMargin == -1; i--){
		BlackPixelCount = 0;
		for (j = 0; j < image->Width && *BottomMargin == -1; j++){
			if (IsPixelBlack(image, j, i)) BlackPixelCount++;
			if (BlackPixelCount > 2) {
				*BottomMargin = i < (image->Height - BottomOffset - 1 ) ? i + BottomOffset : image->Height - 1;
			}
		}
	}
	//*BottomMargin = image->Height - 1;
	assert(*BottomMargin > -1);
	
	/*find left margin*/
	for (i = 0; i < image->Width && *LeftMargin == -1; i++){
		BlackPixelCount = 0;
		for (j = 0; j < image->Height && *LeftMargin == -1; j++){
			if (IsPixelBlack(image, i, j)) BlackPixelCount++;
			if (BlackPixelCount > 2) {
				*LeftMargin = i >= LeftOffset ? i - LeftOffset : 0;
			}
		}
	}

	assert(*LeftMargin > -1);
	
	/*find right margin*/
	/* It seems that this method won't work on right margin
	 * for (i = image->Width-1; i > *LeftMargin  && *RightMargin == -1; i--){
		BlackPixelCount = 0;
		for (j = 0; j < image->Height && *RightMargin == -1; j++){
			if (IsPixelBlack(image, i, j)) BlackPixelCount++;
			if (BlackPixelCount > 5) {
				*RightMargin = i < image->Width - 7 ? i : image->Width - 1;
			}
		}
	}*/
	
	*RightMargin = image->Width - 1;
	assert(*RightMargin > -1);
}

IMAGE * PreviewLazyIsolateCharacter(IMAGE * image, FontType Font, int fontsize, int scanres){
	/*variables*/
	int i,j, TopMargin = -1, LeftMargin = -1, BottomMargin = -1, RightMargin = -1;
	int AreaTop, AreaBottom, AreaLeft, AreaRight;
	int CharCounter, LineCounter;
	int k,l;
	
	/*Check for supported font and set constants*/
	double FontHeight = 0, FontWidth = 0;
	double FontHeightSpace = 0, FontWidthSpace = 0;
	int TopOffset = 0, LeftOffset = 0, RightOffset = 0, BottomOffset = 0;
	if (!((Font == CourierNew && fontsize == 12 && scanres == 300) || (Font == LucidaConsole && fontsize == 10 && scanres == 300))){
		printf("Not supported format\n");
		return NULL;
	} else {
		GetIsolateCharacterConstant(Font, fontsize, scanres, &FontHeight, &FontWidth, &FontHeightSpace, &FontWidthSpace, &TopOffset, &LeftOffset, &RightOffset, &BottomOffset);
	}
	
	
	/*clone the image and overwrite the original with marker*/
	IMAGE * ToMarkImage = DuplicateImage(image);

	/*get the margins*/
	GetMargins(image, TopOffset, LeftOffset, RightOffset, BottomOffset, &TopMargin, &LeftMargin, &RightMargin, &BottomMargin);
	
	
	
	/*mark margins*/
	 /*draw top margin*/
	for(l = 0; l < ToMarkImage->Width; l++){
		SetPixelR(ToMarkImage, l,TopMargin, 200);
		SetPixelG(ToMarkImage, l,TopMargin, 40);
		SetPixelB(ToMarkImage, l,TopMargin, 30);
	}
	/*draw left margin*/
	for(l = 0; l < ToMarkImage->Height; l++){
		SetPixelR(ToMarkImage, LeftMargin,l, 200);
		SetPixelG(ToMarkImage, LeftMargin,l, 40);
		SetPixelB(ToMarkImage, LeftMargin,l, 30);
	}
	/*draw right margin*/
	for(l = 0; l < ToMarkImage->Height; l++){
		SetPixelR(ToMarkImage, RightMargin,l, 200);
		SetPixelG(ToMarkImage, RightMargin,l, 40);
		SetPixelB(ToMarkImage, RightMargin,l, 30);
	}
	/*draw bottom margin*/
	for(l = 0; l < ToMarkImage->Width; l++){
		SetPixelR(ToMarkImage, l,BottomMargin, 200);
		SetPixelG(ToMarkImage, l,BottomMargin, 40);
		SetPixelB(ToMarkImage, l,BottomMargin, 30);
	}
	
	/*start cropping*/	
	
	
	LineCounter = 0;
	for (i = TopMargin; i < BottomMargin - FontHeight; i=floor(TopMargin + LineCounter*(FontHeight+FontHeightSpace))){
		LineCounter++;
		CharCounter = 0;
		for (j = LeftMargin; j < RightMargin - (int)FontWidth; j=LeftMargin + floor(CharCounter*(FontWidth+FontWidthSpace))){
			CharCounter++;
			
			AreaTop = i;
			AreaBottom = ceil(i + FontHeight) < image->Height ? ceil(i + FontHeight) : image->Height - 1;
			AreaLeft = j;
			AreaRight = ceil(j + FontWidth) < image->Width ? ceil(j + FontWidth) : image->Width - 1;
	
			/*mark the crop area*/
			/*top*/
			for (k = AreaLeft; k <= AreaRight; k++){
				SetPixelR(ToMarkImage, k,AreaTop, 30);
				SetPixelG(ToMarkImage, k,AreaTop, 40);
				SetPixelB(ToMarkImage, k,AreaTop, 100);			
			}

			/*bottom*/
			for (k = AreaLeft; k <= AreaRight; k++){
				SetPixelR(ToMarkImage, k,AreaBottom, 30);
				SetPixelG(ToMarkImage, k,AreaBottom, 40);
				SetPixelB(ToMarkImage, k,AreaBottom, 100);			
			}
	
			/*left*/
			for(l = AreaTop; l < AreaBottom; l++){
				SetPixelR(ToMarkImage, AreaLeft,l, 30);
				SetPixelG(ToMarkImage, AreaLeft,l, 40);
				SetPixelB(ToMarkImage, AreaLeft,l, 100);
			}

			for(l = AreaTop; l < AreaBottom; l++){
				SetPixelR(ToMarkImage, AreaRight,l, 30);
				SetPixelG(ToMarkImage, AreaRight,l, 40);
				SetPixelB(ToMarkImage, AreaRight,l, 100);
			}
			
	
		}
	}
	return ToMarkImage;
}


ILIST * LazyIsolateCharacter(IMAGE * image, FontType Font, int fontsize, int scanres){
	/*variables*/
	int i,j, TopMargin = -1, LeftMargin = -1, BottomMargin = -1, RightMargin = -1;
	int AreaTop, AreaBottom, AreaLeft, AreaRight;
	int CharCounter, LineCounter;
	
	IMAGE * img;
	/*Check for supported font and set constants*/
	double FontHeight = 0, FontWidth = 0;
	double FontHeightSpace = 0, FontWidthSpace = 0;
	int TopOffset = 0, LeftOffset = 0, RightOffset = 0, BottomOffset = 0;
	if (!((Font == CourierNew && fontsize == 12 && scanres == 300) || (Font == LucidaConsole && fontsize == 10 && scanres == 300))){
		printf("Not supported format\n");
		return NULL;
	} else {
		GetIsolateCharacterConstant(Font, fontsize, scanres, &FontHeight, &FontWidth, &FontHeightSpace, &FontWidthSpace, &TopOffset, &LeftOffset, &RightOffset, &BottomOffset);
	}
	
		
	
	ILIST * imglist = NewImageList();
	
	/*get the margins*/
	GetMargins(image, TopOffset, LeftOffset, RightOffset, BottomOffset, &TopMargin, &LeftMargin, &RightMargin, &BottomMargin);

	/*start cropping*/	
	
	
	LineCounter = 0;
	for (i = TopMargin; i < BottomMargin - FontHeight; i=floor(TopMargin + LineCounter*(FontHeight+FontHeightSpace))){
		LineCounter++;
		CharCounter = 0;
		for (j = LeftMargin; j < RightMargin - (int)FontWidth; j=LeftMargin + floor(CharCounter*(FontWidth+FontWidthSpace))){
			CharCounter++;
			
			AreaTop = i;
			AreaBottom = ceil(i + FontHeight) < image->Height ? ceil(i + FontHeight) : image->Height - 1;
			AreaLeft = j;
			AreaRight = ceil(j + FontWidth) < image->Width ? ceil(j + FontWidth) : image->Width - 1;
			
			img = CropImage(image,AreaLeft, AreaTop, AreaRight, AreaBottom);			
			AppendImage(imglist, img);

		}
		AppendImage(imglist, NULL);
	}
	return imglist;
}

/***********************************************************
 *			ACTIVE ISOLATE CHARACTER
 ***********************************************************/
IMAGE * PreviewActiveIsolateCharacter(IMAGE * image, FontType Font, int fontsize, int scanres)
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
  boxed_image = DuplicateImage(image);
 /* boxed_image = CreateImage(image->Width, image->Height);
  for (y=0; y<image->Height; y++)
    for(x=0; x<image->Width; x++)
      {
	temp_R = GetPixelR(image,x,y);
	temp_G = GetPixelG(image,x,y);
	temp_B = GetPixelB(image,x,y);
	
	SetPixelR(boxed_image,x,y,temp_R);
	SetPixelG(boxed_image,x,y,temp_G);
	SetPixelB(boxed_image,x,y,temp_B);
      }*/

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


ILIST * ActiveIsolateCharacter(IMAGE * image, FontType Font, int fontsize, int scanres)
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


