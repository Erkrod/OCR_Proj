#ifndef MODEL_H
#define MODEL_H

#include "ImageList.h"
#include "ModelStructure.h"
#include "utstring.h"
#include "utarray.h"
#include "Image.h"


ILIST * IsolateCharacter(IMAGE * image, int fontsize, int scanres);
UT_array * IdentifyCharacter( IMAGE * Image, ILIST * Template );
/* this is the postProcessing function */
/* where the character is chosen and put into a string to be output */
UT_string * postProcessing(UT_array * );

int SaveImage(const char fname[SLEN], IMAGE *image);
IMAGE * ReadImage(char *ImageFileName);

UT_icd CharProbability_icd = {sizeof(CharProbability), NULL, NULL, NULL };

#endif
