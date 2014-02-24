

#include "Control.h"


ControlHandle * Control_Initialize(void){
	ControlHandle * ToReturn = (ControlHandle *) malloc(sizeof(ControlHandle));
	return ToReturn;
}

void Control_MainLoop(ControlHandle * MainHandle){
	gtk_main();
}

void Control_CleanUp(ControlHandle * MainHandle){
	free(MainHandle);
}

/*function to take care of all event*/
ControlHandle * Control_ProcessEvent(ObjectHandle * ClickedObject){
	printf("Object clicked has name: %s\n", ClickedObject->Name);
	if (strcmp(ClickedObject->Name,"OpenFile") == 0){
		printf("Put the function to open file here\n");
		on_open_clicked();
	}
}

void on_open_clicked(){
    
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
