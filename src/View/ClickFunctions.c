/*******************************************************************/
/* ClickFunctions.c                                                */
/*******************************************************************/

#include "ClickFunctions.h"

void on_open_clicked(GtkWidget *window, gpointer data){
    
    GtkWidget *openFile;
       
    openFile = gtk_file_chooser_dialog_new("Open File",
                                           NULL,
                                           GTK_FILE_CHOOSER_ACTION_OPEN,
                                           GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                           GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
                                           NULL);
    
    if (gtk_dialog_run (GTK_DIALOG (openFile)) == GTK_RESPONSE_ACCEPT)
    {
        char *filename;
        
        filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (openFile));
        /* open file function here */
        g_free (filename);
    }    
    gtk_widget_destroy (openFile);    
}

void on_rotate_clicked(GtkWidget *window, gpointer data){

}
