/*******************************************************************/
/* ClickFunctions.h                                                */
/*******************************************************************/

#ifndef CLICKFUNCTIONS_H
#define CLICKFUNCTIONS_H

#include <gtk/gtk.h>

void on_open_clicked(GtkWidget *window, gpointer data);

void on_save_clicked(GtkWidget *window, gpointer data);

void on_convertBW_clicked(GtkWidget *window, gpointer data);

void on_stainRem_clicked(GtkWidget *window, gpointer data);

void on_wrinkleRem_clicked(GtkWidget *window, gpointer data);

void on_rotate_clicked(GtkWidget *window, gpointer data);

void on_boundaries_clicked(GtkWidget *window, gpointer data);

void on_crop_clicked(GtkWidget *window, gpointer data);

void on_ocr_clicked(GtkWidget *window, gpointer data);

void on_edit_clicked(GtkWidget *window, gpointer data);

void on_dictionary_clicked(GtkWidget *window, gpointer data);

#endif
