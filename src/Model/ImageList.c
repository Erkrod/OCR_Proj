/*********************************************************************/ 
/* ImageList.c: source code file for lists of Images				 */ 
/*                                                                   */
/* 10/27/11 Weiwei Chen: initial solution version                    */
/*                       for EECS22 assignment5 FAll2011             */
/*********************************************************************/ 

#include "ImageList.h"

/* allocate a new image list */
ILIST *NewImageList(void)
{
	ILIST *newlist = (ILIST *)malloc(sizeof(ILIST));

	if (newlist != NULL)
	{
		newlist->First = NULL;
		newlist->Last = NULL;
		newlist->Length = 0;
	}

	return newlist;
}

/* delete an image list (and all entries) */
void DeleteImageList(ILIST *l)
{
	IENTRY *curr, *succ;
	if (l){
		assert(l);
		curr = l->First;
		while(curr){
			succ = curr->Next;
			assert(curr->List == l);
			if (curr->Image) DeleteImage(curr->Image);
			curr->Image = NULL;
			free(curr);
			curr = succ;
		}

		free(l);
	}
}

/* insert an image into a list */
void AppendImage(ILIST *l, IMAGE *image)
{
	IENTRY *newentry;

	assert(l);

	newentry = (IENTRY *)malloc(sizeof(IENTRY));
	
	if (newentry != NULL)	{
		newentry->Prev 	= NULL;
		newentry->Next 	= NULL;
		newentry->List 	= l;
		newentry->Image = image;
		
		if(!l->First){
			l->First = newentry;
			l->Last = newentry;
		}
		else{
			l->Last->Next = newentry;
			newentry->Prev = l->Last;
			l->Last = newentry;
		}
		l->Length ++;
	}
}

/* reverse an image list */
void ReverseImageList(ILIST *l)
{
	IENTRY *curr, *currTail, *succ;

	assert(l) ; 

	if(l->First){
		l->Last = l->First;
		currTail = l->First;
		curr = currTail->Next;
		currTail->Next = NULL;

		while(curr){
			succ = curr->Next;
			currTail->Prev = curr;
			curr->Next = currTail;
			currTail = curr;
			curr = succ;
		}
		
		currTail->Prev = NULL;
		l->First = currTail;
	}
}

void CropImageList(ILIST *l, unsigned int SFrame, unsigned int EFrame) 
{
	int i ; 
	IENTRY *curr, *succ ; 
	
	assert(l) ; 
	
	i = 1 ; 
	
	curr = l->First ; 
	while (curr) 
	{
		succ = curr->Next ; 
		if (i < SFrame || i > EFrame) 
		{
			DeleteImage(curr->Image);
			curr->Image = NULL ; 
			free (curr) ; 
		}
		else
		{
			if (i == SFrame) 
			{
				l->First = curr ; 
				curr->Prev = NULL ; 
			}
			else if (i == EFrame)
			{
				l->Last = curr ; 
				curr->Next = NULL;
			}			
		}		
		curr = succ ;
		
		i++ ; 
	}		
}

unsigned int FastImageList(ILIST *l, unsigned int ff_factor)
{
	int i ; 
	int j ;
	IENTRY *prev, *curr, *succ ; 
	
	assert(l) ; 
	
	i = 0 ; 
	j = 0 ; 
	curr = l->First ; 
	prev = l->First ;  

	while (curr)
	{
		succ = curr->Next ; 
		if (i%ff_factor == 0) /*keep*/
		{
			if (i > 0)
			{
				prev->Next = curr ; 
				curr->Prev = prev ; 
			}
			prev = curr ; 
			j ++ ; 
		}
		else /*skip*/
		{
			DeleteImage(curr->Image);
			curr->Image = NULL ; 
			free (curr) ; 			
		}
		curr = succ ; 
		i++ ; 
	}
	prev->Next = NULL ; 
	return j ; 
} 

void PopLastImage(ILIST *l){
	if (l->Last){
		if (l->Last == l->First){
			if (l->Last->Image) DeleteImage(l->Last->Image);
			free(l->Last);
			l->Last = NULL;
			l->First = NULL;
		} else {
			if (l->Last->Image) DeleteImage(l->Last->Image);
			l->Last = l->Last->Prev;
			free(l->Last->Next);
			l->Last->Next = NULL;			
		}
	}
}

#if 0
void ResizeImageList(ILIST *l, unsigned int percentage)
{
	IENTRY *curr ; 
	IMAGE*  old_image ; 
	
	assert(l) ; 
	
	curr = l->First ; 	
	while (curr)
	{
		old_image = curr->Image ; 
		curr->Image = Resize(percentage, old_image) ; 

		curr = curr->Next ; 
	}	
} 		
#endif
