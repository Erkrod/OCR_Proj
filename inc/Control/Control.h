#ifndef CONTROL_H
#define CONTROL_H

#include <stdio.h>
#include <stdlib.h>

#include <gtk/gtk.h>
#include "EventStructure.h"

#ifndef TEST_VIEW
#include "Model.h"
#endif

#include "View.h"

typedef struct {
	EventClass event;
#ifndef TEST_VIEW
	ImageList * ImageStack;
#endif
	/*if necessary*/
	/*ModelHandle * MainModelHandle;
	ViewHandle * MainViewHandle;*/
} ControlHandle;

ControlHandle * Control_Initialize(void);
void Control_MainLoop(ControlHandle *);
void Control_CleanUp(ControlHandle *);

/*function to take care of all event*/
ControlHandle * Control_ProcessEvent(ObjectHandle * ClickedObject);

/* functions for menu option clicking event */
void on_open_clicked();

void on_save_clicked(GtkWidget *window, gpointer data);

void on_convertBW_clicked(GtkWidget *window, gpointer data);

void on_stainRem_clicked(GtkWidget *window, gpointer data);

void on_wrinkleRem_clicked(GtkWidget *window, gpointer data);

void on_rotate_clicked();

void on_boundaries_clicked(GtkWidget *window, gpointer data);

void on_crop_clicked(GtkWidget *window, gpointer data);

void on_ocr_clicked(GtkWidget *window, gpointer data);

void on_edit_clicked(GtkWidget *window, gpointer data);

void on_dictionary_clicked(GtkWidget *window, gpointer data);
#endif
