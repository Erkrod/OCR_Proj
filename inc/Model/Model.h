#ifndef MODEL_H
#define MODEL_H

#include "ModelStructure.h"
#include "utstring.h"
#include "Image.h"


/* this is the postProcessing function */
/* where the character is chosen and put into a string to be output */
UT_string * postProcessing(UT_array * );

IMAGE * ReadImage(char *ImageFileName);

#endif
