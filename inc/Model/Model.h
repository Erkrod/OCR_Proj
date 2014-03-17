#ifndef MODEL_H
#define MODEL_H

#include <unistd.h>
#include <sys/stat.h>

#include "ImageList.h"
#include "ModelStructure.h"
#include "utstring.h"
#include "Image.h"

IMAGE * PreviewLazyIsolateCharacter(IMAGE * image, FontType Font, int fontsize, int scanres);
ILIST * LazyIsolateCharacter(IMAGE * image, FontType Font, int fontsize, int scanres);
IMAGE * PreviewActiveIsolateCharacter(IMAGE * image, FontType Font, int fontsize, int scanres);
ILIST * ActiveIsolateCharacter(IMAGE * image, FontType Font, int fontsize, int scanres);


/*for post processing*/
//UT_array * IdentifyCharacter( IMAGE * Image, ILIST * Template );
void CharProfile_free(void * profile_in);
/* this is the postProcessing function */
/* where the character is chosen and put into a string to be output */
UT_string * postProcessing(UT_array * );
UT_array * postProcessingInitializeDictionary();
UT_array * postProcessingInitializeSpecialChar();
void postProcessingCleanUP(UT_array * , UT_array * );
UT_array * getThreeKeyword(CharProfile *, UT_array *, UT_array *);
UT_string * postProcessingAdvance(UT_array *, UT_array *, UT_array *);
char * getTopProb(CharProfile *);
char * getSecondProb(CharProfile *);
UT_string * wordCompare(UT_array *, UT_array *);
int compareChar(UT_string *, UT_array *);



int SaveImage(const char fname[SLEN], IMAGE *image);
IMAGE * ReadImage(char *ImageFileName);

UT_string * GetCompileMessage(UT_string * code);
int file_exist (char *filename);


UT_icd CharProbability_icd;
UT_icd CharProfile_icd; 


UT_array * IdentifyCharacter( ILIST * imglist, ILIST * Template , int IsolateAlgorithm);
ILIST * InitializeTemplate(void);
int IsPixelBlack(IMAGE * image, int x, int y);
#endif
