#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include "Image.h"
#include "ImageList.h"
#include "uthash.h"
#include "utstring.h"
#define MAX_HASH_KEY_LENGTH 20

typedef struct ViewHandleStruct ViewHandle;

typedef enum {SelectCoordinate, Normal} StateEnum;

typedef struct {
	/*EventClass event;*/
#ifndef TEST_VIEW
	ILIST * ImageStack;
#endif
	/*if necessary*/
	/*ModelHandle * MainModelHandle;*/
	ViewHandle * MainViewHandle;
	UT_string * InputImageFileName;
	UT_string * OutputFileName;
	ILIST * MainImageList;
	UT_string * MainOutputString;
	StateEnum State;
	int IsInPreview;
	int InitialState;
} ControlHandle;

typedef struct {
	char Name[MAX_HASH_KEY_LENGTH];
	GtkWidget * Widget;
	UT_hash_handle HashByName;
	UT_hash_handle HashByWidget;
	ViewHandle * MainViewHandle;
} ObjectHandle;

struct ViewHandleStruct {
	ObjectHandle * ObjectListByName, * ObjectListByWidget;
	ControlHandle * MainControlHandle;
};



#endif