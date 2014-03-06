#ifndef MODEL_STRUCTURE_H
#define MODEL_STRUCTURE_H


#include "utarray.h"

typedef struct {
	char Char;
	int Probability;
} CharProbability;

typedef struct {
	UT_array * CharChoices;
	char CharChosen;
} CharProfile;

typedef enum {CourierNew, LucidaConsole} FontType;

#define SLEN 80

#endif
