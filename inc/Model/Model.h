#ifndef MODEL_H
#define MODEL_H

#include "ImageList.h"
#include "ModelStructure.h"
#include "utstring.h"

/* this is the postProcessing function */
/* where the character is chosen and put into a string to be output */
UT_string * postProcessing(UT_array * );


IMAGE *ReadImage(const char * fname);
int SaveImage(const char fname[SLEN], IMAGE *image);

#endif
