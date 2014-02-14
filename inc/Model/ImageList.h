/*********************************************************************/ 
/* ImageList.h: header file for lists of Images				 		 */ 
/*                                                                   */
/* 10/27/11 Weiwei Chen: initial solution version                    */
/*                       for EECS22 assignment5 FAll2011             */
/*********************************************************************/ 
#ifndef IMAGE_LIST_H
#define IMAGE_LIST_H


#include <stdlib.h>
#include <assert.h>
#include "DIPs.h"
#include "Image.h"

typedef struct ImageList ILIST;
typedef struct ImageEntry IENTRY;

struct ImageList
{  int  Length;    /*Length of the list*/
   IENTRY *First;  /*pointer to the first entry*/
   IENTRY *Last;   /*pointer to the last entry*/
} ;

struct ImageEntry
{  IENTRY *Next;   /*pointer to the next entry*/
   IENTRY *Prev;   /*pointer to the previous entry*/
   ILIST  *List;   /*pointer to the list which this entry belongs to*/
   IMAGE  *Image;  /*pointer to the struct for an image*/
};

/* allocate a new image list */
ILIST *NewImageList(void);

/* delete a image list (and all entries) */
void DeleteImageList(ILIST *l);

/* insert a student into a list */
void AppendImage(ILIST *l, IMAGE *image);

/* reverse an image list */
void ReverseImageList(ILIST *l);

/*crop frames from the list starting from SFrame to EFrame*/
void CropImageList(ILIST *l, unsigned int SFrame, unsigned int EFrame) ; 

/*Resize the image in the list*/
void ResizeImageList(ILIST *l, unsigned int percentage) ; 

/*Fast forward the video*/
unsigned int FastImageList(ILIST *l, unsigned int ff_factor) ; 

#endif /* IMAGE_LIST_H */

/* EOF */
