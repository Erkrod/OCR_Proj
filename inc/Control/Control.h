#ifndef CONTROL_H
#define CONTROL_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gtk/gtk.h>
#include "DataStructures.h"

#ifndef TEST_VIEW
#include "Model.h"
#endif
#include "View.h"



ControlHandle * Control_Initialize(void);
void Control_MainLoop(ControlHandle *);
void Control_CleanUp(ControlHandle *);

/*function to take care of all event*/
void Control_ProcessEvent(ObjectHandle * ClickedObject);

/* functions for menu option clicking event */
void OpenImageFile(UT_string * ImageFileName);
void SaveTextFile(UT_string * OutputFileName);
void show_error(const gchar * ErrorMessage);
void GetCropCoordinate(ControlHandle * MainControlHandle, int * x1, int * y1, int * x2, int * y2);
/*void on_open_clicked();

void on_save_clicked(GtkWidget *window, gpointer data);

void on_convertBW_clicked(GtkWidget *window, gpointer data);

void on_stainRem_clicked(GtkWidget *window, gpointer data);

void on_wrinkleRem_clicked(GtkWidget *window, gpointer data);

void on_rotate_clicked();

void on_boundaries_clicked(GtkWidget *window, gpointer data);

void on_crop_clicked(GtkWidget *window, gpointer data);

void on_ocr_clicked(GtkWidget *window, gpointer data);

void on_edit_clicked(GtkWidget *window, gpointer data);

void on_dictionary_clicked(GtkWidget *window, gpointer data);*/
#endif
