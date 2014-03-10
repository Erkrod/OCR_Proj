/******************************************************************/
/* DrawFunctions.h                                                */
/******************************************************************/

#ifndef DRAWFUNCTIONS_H
#define DRAWFUNCTIONS_H

#include <gtk/gtk.h>
/*#include "ClickFunctions.h"*/
#include "View.h"

GtkWidget *drawMain(ViewHandle * MainViewHandle);

GtkWidget *drawMenuBar(ViewHandle * MainViewHandle);

GtkWidget *drawImageWindow(ViewHandle *MainViewHandle);

GtkWidget *drawTextWindow(ViewHandle *MainViewHandle);

GtkWidget *drawRotateWindow(ViewHandle * MainViewHandle);

GtkWidget *drawCropWindow(ViewHandle * MainViewHandle);

GtkWidget *drawColorFilterWindow(ViewHandle * MainViewHandle);

GtkWidget *drawOCRWindow(ViewHandle * MainViewHandle);

GtkWidget *drawStainRemoveWindow(ViewHandle * MainViewHandle);

GtkWidget * drawAboutWindow(ViewHandle * MainViewHandle);
GtkWidget *drawHelpWindow(ViewHandle * MainViewHandle);

void drawAllWindows(ViewHandle * MainViewHandle);

#endif
