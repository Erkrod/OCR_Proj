/***********************************************************/
/* GFXMain.c                                               */
/***********************************************************/

#include <gtk/gtk.h>
#include "View.h"
#include "Control.h"
#include "DrawFunctions.h"

int main (int   argc, char *argv[]){
 
  ViewHandle * MainViewHandle = View_Initialize();
	
  gtk_init(&argc, &argv);  

  GtkWidget *window         = drawMain(MainViewHandle);  
  GtkWidget *menubar        = drawMenuBar(MainViewHandle);
  GtkWidget *vbox           = gtk_vbox_new(FALSE, 0);
  GtkWidget *hbox           = gtk_hbox_new(FALSE, 0);    
  GtkWidget *scrollWinImage = drawImageWindow(MainViewHandle);
  GtkWidget *scrollWinText  = drawTextWindow(MainViewHandle);
  GtkWidget *rotateWindow   = drawRotateWindow(MainViewHandle);
  GtkWidget *cropWindow     = drawCropWindow(MainViewHandle);


  gtk_container_add(GTK_CONTAINER(window), vbox);
  gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 3);
  gtk_box_pack_start(GTK_BOX(vbox), hbox, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(hbox), scrollWinImage, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(hbox), scrollWinText, TRUE, TRUE, 0);
          
  /* show the window*/
  gtk_widget_show_all(window); 
  
  gtk_main(); 
  
  return 0;
}
