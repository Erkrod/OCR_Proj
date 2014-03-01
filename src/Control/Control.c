

#include "Control.h"
#include "DrawFunctions.h"



ControlHandle * Control_Initialize(void){
	ControlHandle * ToReturn = (ControlHandle *) malloc(sizeof(ControlHandle));
	ToReturn->MainViewHandle = View_Initialize(ToReturn);
	utstring_new(ToReturn->InputImageFileName);
	drawAllWindows(ToReturn->MainViewHandle);
	return ToReturn;
}

void Control_MainLoop(ControlHandle * MainHandle){
	
	gtk_main();
}

void Control_CleanUp(ControlHandle * MainHandle){
	free(MainHandle);
}

/*function to take care of all event*/
void Control_ProcessEvent(ObjectHandle * ClickedObject){
	
	ViewHandle * MainViewHandle = ClickedObject->MainViewHandle;
	ControlHandle * MainControlHandle = MainViewHandle->MainControlHandle;
	ObjectHandle * CurrObject;
	GtkRequisition requisition;
	GtkAllocation allocation;
	 char name[20] = "MainWindow";
#ifdef DEBUG
	printf("Object clicked has name: %s\n", ClickedObject->Name);
#endif
	if (strcmp(ClickedObject->Name,"OpenFile") == 0){
		OpenImageFile(MainControlHandle->InputImageFileName);
		CurrObject = NULL;
		HASH_FIND(HashByName,MainViewHandle->ObjectListByName, name, sizeof(char) * MAX_HASH_KEY_LENGTH,CurrObject);
		if (CurrObject) {	
			/*printf("%d %d\n", CurrObject->Widget->allocation.x, CurrObject->Widget->allocation.y);
			gtk_widget_size_request(CurrObject->Widget, &requisition);
			printf("Image scroll window is %d wide\n",requisition.width);*/
			gtk_widget_get_allocation(CurrObject->Widget, &allocation);
			printf("Image scroll window is %d wide\n",allocation.width);
			
		}
		else printf("Can't find ImageScrollWindow\n");
#ifdef DEBUG
		printf("Input file name is %s\n", utstring_body(MainControlHandle->InputImageFileName));
		utstring_printf(MainControlHandle->InputImageFileName, "/home/group1/Programming/EECS22L_Project2/Images/CourierNew12_300DPI.ppm");
#endif
		/*load the image here*/
		
	}
	/*if (strcmp(ClickedObject->Name,"Rotate") == 0){
        
	}*/
}

void OpenImageFile(UT_string * ImageFileName){
    
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

        utstring_printf(ImageFileName, "%s", filename);
	 

        g_free (filename);
    } else {
	  utstring_printf(ImageFileName, "a");
    }
    gtk_widget_destroy (openFile);    
}


void on_rotate_clicked(){


}
