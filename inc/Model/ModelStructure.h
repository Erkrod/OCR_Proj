#ifndef MODEL_STRUCTURE_H
#define MODEL_STRUCTURE_H


#include "utarray.h"

typedef struct {
	char Char;
	int Probability;
	UT_array *nums;
	/*example of usage for UT_array are available in the following files
	RawLibrary/uthash-master/tests/test43.c:  UT_array *pairs, *pairs_cpy;
	RawLibrary/uthash-master/tests/test44.c:  UT_array *a;
	RawLibrary/uthash-master/tests/test45.c:  UT_array *a;
	RawLibrary/uthash-master/tests/test46.c:  UT_array *strs,*strs2;
	RawLibrary/uthash-master/tests/test48.c:  UT_array *nums;
	RawLibrary/uthash-master/tests/test49.c:  UT_array *strs;
	RawLibrary/uthash-master/tests/test50.c:  UT_array *nums;
	RawLibrary/uthash-master/tests/test51.c:  UT_array *pairs;
	RawLibrary/uthash-master/tests/test52.c:  UT_array *intchars;
	RawLibrary/uthash-master/tests/test61.c:  UT_array *strs;
	RawLibrary/uthash-master/tests/test67.c:  UT_array *nums;
	RawLibrary/uthash-master/tests/test80.c:  UT_array *a;
	RawLibrary/uthash-master/tests/test81.c:  UT_array *a;
	RawLibrary/uthash-master/tests/test82.c:  UT_array *a,*b;
	*/
}

#endif
