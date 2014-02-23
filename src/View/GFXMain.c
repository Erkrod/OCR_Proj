/***********************************************************/
/* GFXMain.c                                               */
/***********************************************************/

#include <gtk/gtk.h>
#include "ClickFunctions.h"
#include "DrawFunctions.h"

int main (int   argc, char *argv[]){
  
 gtk_init(&argc, &argv);  

 GtkWidget *window  = drawMain();  
 GtkWidget *menubar = drawMenuBar();
 GtkWidget *vbox    = gtk_vbox_new(FALSE, 0);    

 gtk_container_add(GTK_CONTAINER(window), vbox);        
 gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 3);

 /* show the window*/
 gtk_widget_show_all(window); 

 gtk_main(); 

 return 0;
}
