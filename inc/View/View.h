#ifndef VIEW_H
#define VIEW_H

#include "stdio.h"
#include "stdlib.h"
#include "uthash.h"
#include "assert.h"
#include "gtk/gtk.h"

#define MAX_HASH_KEY_LENGTH 20

typedef struct {
	char Name[MAX_HASH_KEY_LENGTH];
	GtkWidget * Widget;
	UT_hash_handle HashByName;
	UT_hash_handle HashByWidget;
} ObjectHandle;

typedef struct {
	ObjectHandle * ObjectListByName, * ObjectListByWidget;
} ViewHandle;

ViewHandle * View_Initialize(void);
void AddWidgetToViewHandle(ViewHandle * MainViewHandle, const char * NewName, GtkWidget * NewWidget);
void CatchEvent(GtkWidget *widget, gpointer data);
ObjectHandle * ObjectHandle_Initialize(const char * name, GtkWidget * widget);
#endif