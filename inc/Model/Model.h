#ifndef MODEL_H
#define MODEL_H

#include "ImageList.h"
#include "ModelStructure.h"
#include "utstring.h"
#include "Image.h"
#include "ImageProcessing.h"
#include <unistd.h>
#include <sys/stat.h>


ILIST * IsolateCharacter(IMAGE * image, int fontsize, int scanres);
UT_array * IdentifyCharacter( ILIST *, ILIST * );
void CharProfile_free(void * profile_in);
/* this is the postProcessing function */
/* where the character is chosen and put into a string to be output */
UT_string * postProcessing(UT_array * );
int file_exist (char *filename);
int SaveImage(const char fname[SLEN], IMAGE *image);
IMAGE * ReadImage(char *ImageFileName);
extern UT_icd CharProfile_icd;
extern UT_icd CharProbability_icd;
ILIST * InitializeTemplate(void);

#endif
