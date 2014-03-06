#include "Model.h"


#if 1

int IsPixelBlack(IMAGE * image, int x, int y){
	if (GetPixelR(image, x, y) >= 50) return 0;
	if (GetPixelG(image, x, y) >= 50) return 0;
	if (GetPixelB(image, x, y) >= 50) return 0;
	return 1;
	/*if (GetPixelR(image, x, y) < 10 && GetPixelG(image, x, y) < 10 && GetPixelB(image, x, y) < 10) return 1;
	return 0;*/
}

ILIST * IsolateCharacter(IMAGE * image, FontType Font, int fontsize, int scanres){
	/*variables*/
	int i,j, BlackPixelCount, TopMargin = -1, LeftMargin = -1, BottomMargin = -1, RightMargin = -1;
	
	/*Check for supported font and set constants*/
	double FontHeight, FontWidth;
	double FontHeightSpace, FontWidthSpace;
	int TopOffset, LeftOffset, RightOffset, BottomOffset;
	if (Font == CourierNew && fontsize == 12 && scanres == 300){
		FontHeight = 47.4; 
		FontWidth = 28.1;
		FontHeightSpace = 9.1; 
		FontWidthSpace = 1.80;
		TopOffset = 7;
		LeftOffset = 7;
		BottomOffset = 7;
	} else if (Font == LucidaConsole && fontsize == 10 && scanres == 300){
		FontHeight = 40.425; 
		FontWidth = 24;
		FontHeightSpace = 1.10; 
		FontWidthSpace = 1.1;
		TopOffset = 4;
		LeftOffset = 4;
		BottomOffset = 7;
	} else return NULL;
		
		
	
	ILIST * imglist = NewImageList();

	/*find top margin*/
	for (i = 0; i < image->Height && TopMargin == -1; i++){
		BlackPixelCount = 0;
		for (j = 0; j < image->Width && TopMargin == -1; j++){
			if (IsPixelBlack(image, j, i)) BlackPixelCount++;
			if (BlackPixelCount > 2) {
				TopMargin = i >= TopOffset ? i - TopOffset : 0;
			}
		}
	}

	assert(TopMargin > -1);
	
	/*find bottom margin*/
	for (i = image->Height-1; i > TopMargin && BottomMargin == -1; i--){
		BlackPixelCount = 0;
		for (j = 0; j < image->Width && BottomMargin == -1; j++){
			if (IsPixelBlack(image, j, i)) BlackPixelCount++;
			if (BlackPixelCount > 5) {
				BottomMargin = i < (image->Height - BottomOffset - 1 ) ? i + BottomOffset : image->Height - 1;
			}
		}
	}

	assert(BottomMargin > -1);

	/*find left margin*/
	for (i = 0; i < image->Width && LeftMargin == -1; i++){
		BlackPixelCount = 0;
		for (j = 0; j < image->Height && LeftMargin == -1; j++){
			if (IsPixelBlack(image, i, j)) BlackPixelCount++;
			if (BlackPixelCount > 2) {
				LeftMargin = i >= LeftOffset ? i - LeftOffset : 0;
			}
		}
	}

	assert(LeftMargin > -1);
	
	/*find right margin*/
	/* It seems that this method won't work on right margin
	 * for (i = image->Width-1; i > LeftMargin  && RightMargin == -1; i--){
		BlackPixelCount = 0;
		for (j = 0; j < image->Height && RightMargin == -1; j++){
			if (IsPixelBlack(image, i, j)) BlackPixelCount++;
			if (BlackPixelCount > 5) {
				RightMargin = i < image->Width - 7 ? i : image->Width - 1;
			}
		}
	}*/
	
	RightMargin = image->Width - 1;
	assert(RightMargin > -1);
	
	/*start cropping*/
	
	int AreaTop, AreaBottom, AreaLeft, AreaRight;
	int CharCounter, LineCounter;
	IMAGE * TempImage, *img;
	int k,l;
#ifdef DEBUG
	BottomMargin = image->Height - 1;
	IMAGE * ToCheckImage = DuplicateImage(image);
	/*draw top margin*/
	for(l = 0; l < image->Width; l++){
		SetPixelR(ToCheckImage, l,TopMargin, 200);
		SetPixelG(ToCheckImage, l,TopMargin, 40);
		SetPixelB(ToCheckImage, l,TopMargin, 30);
	}
	/*draw left margin*/
	for(l = 0; l < image->Height; l++){
		SetPixelR(ToCheckImage, LeftMargin,l, 200);
		SetPixelG(ToCheckImage, LeftMargin,l, 40);
		SetPixelB(ToCheckImage, LeftMargin,l, 30);
	}
	/*draw right margin*/
	for(l = 0; l < image->Height; l++){
		SetPixelR(ToCheckImage, RightMargin,l, 200);
		SetPixelG(ToCheckImage, RightMargin,l, 40);
		SetPixelB(ToCheckImage, RightMargin,l, 30);
	}
	/*draw bottom margin*/
	for(l = 0; l < image->Width; l++){
		SetPixelR(ToCheckImage, l,BottomMargin, 200);
		SetPixelG(ToCheckImage, l,BottomMargin, 40);
		SetPixelB(ToCheckImage, l,BottomMargin, 30);
	}
#endif	
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
			
			
#ifdef DEBUG	
			/*mark the crop area*/
			/*top*/
			for (k = AreaLeft; k <= AreaRight; k++){
				SetPixelR(ToCheckImage, k,AreaTop, 30);
				SetPixelG(ToCheckImage, k,AreaTop, 40);
				SetPixelB(ToCheckImage, k,AreaTop, 100);			
			}

			/*bottom*/
			for (k = AreaLeft; k <= AreaRight; k++){
				SetPixelR(ToCheckImage, k,AreaBottom, 30);
				SetPixelG(ToCheckImage, k,AreaBottom, 40);
				SetPixelB(ToCheckImage, k,AreaBottom, 100);			
			}
	
			/*left*/
			for(l = AreaTop; l < AreaBottom; l++){
				SetPixelR(ToCheckImage, AreaLeft,l, 30);
				SetPixelG(ToCheckImage, AreaLeft,l, 40);
				SetPixelB(ToCheckImage, AreaLeft,l, 100);
			}

			for(l = AreaTop; l < AreaBottom; l++){
				SetPixelR(ToCheckImage, AreaRight,l, 30);
				SetPixelG(ToCheckImage, AreaRight,l, 40);
				SetPixelB(ToCheckImage, AreaRight,l, 100);
			}
#endif			
	
#if 0
			TempImage = DuplicateImage(image);
#else
			TempImage = image;
#endif
			img = CropImage(TempImage,AreaLeft, AreaTop, AreaRight, AreaBottom);
			
			AppendImage(imglist, img);

		}
	}
#ifdef DEBUG
	SaveImage("CheckIsolate", ToCheckImage);
	DeleteImage(ToCheckImage);
#endif
	return imglist;
}

#else
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
		/*printf("x coordinate is %d and slice color is %lf\n", x,slice_color);*/
	      if (x_border_start == -1)
		x_border_start = x-1; 
	    }
	} /*for x*/
      if (x_border_end != -1) /* border start and end has been defined*/
	break;
    }
    
  char_width = x_border_end - x_border_start;
  IMAGE * TempImage;
  for ( y=start_y; y<(image->Height-start_y-char_height); y=y+char_height )
    for ( x=x_border_start; x < image->Width-char_width; x=x+char_width)
      {
	TempImage = DuplicateImage(image);
	img = CropImage(TempImage,x,y,x+char_width,y+char_height);
	AppendImage(imglist, img);
      }
  /*printf("The x_border_start is %d. The x_border_end is %d. The char_width is %d.\n", x_border_start, x_border_end, char_width);*/
  /*printf("char height is %d, start_y is %d, image height is %d\n", char_height, start_y, image->Height);*/
  return imglist;
}
#endif

