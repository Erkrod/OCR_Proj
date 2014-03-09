#ifndef VIEW_H
#define VIEW_H

#include "stdio.h"
#include "stdlib.h"
#include "uthash.h"
#include "assert.h"
#include "gtk/gtk.h"
#include "Control.h"
#include "DrawFunctions.h"

ViewHandle * View_Initialize(ControlHandle * MainControlHandle);
void AddWidgetToViewHandle(ViewHandle * MainViewHandle, const char * NewName, GtkWidget * NewWidget);
void CatchEvent(GtkWidget *widget, gpointer data);
void CatchGdkEvent(GtkWidget *widget, GdkEvent * event, gpointer data);
ObjectHandle * ObjectHandle_Initialize(const char * name, GtkWidget * widget, ViewHandle * MainViewHandle);
#endif