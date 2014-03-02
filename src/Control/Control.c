

#include "Control.h"
#include "DrawFunctions.h"



ControlHandle * Control_Initialize(void){
	ControlHandle * ToReturn = (ControlHandle *) malloc(sizeof(ControlHandle));
	ToReturn->MainViewHandle = View_Initialize(ToReturn);
	utstring_new(ToReturn->InputImageFileName);
	utstring_new(ToReturn->MainOutputString);
	utstring_new(ToReturn->OutputFileName);
	drawAllWindows(ToReturn->MainViewHandle);
	return ToReturn;
}

void Control_MainLoop(ControlHandle * MainHandle){
	
	gtk_main();
}

void Control_CleanUp(ControlHandle * MainHandle){
	free(MainHandle);
}

void UpdateDisplayImage(ControlHandle * MainControlHandle){
	ObjectHandle * CurrObject;
	char name[MAX_HASH_KEY_LENGTH];
	strcpy(name, "MainDisplayImage");
	HASH_FIND(HashByName,MainControlHandle->MainViewHandle->ObjectListByName, name, sizeof(char) * MAX_HASH_KEY_LENGTH,CurrObject);
	assert(CurrObject);
	
	/*save last image to a temp file first*/
	if (MainControlHandle->MainImageList->Last){
		assert(SaveImage("Temp", MainControlHandle->MainImageList->Last->Image));
		gtk_image_set_from_file(GTK_IMAGE(CurrObject->Widget), "Temp.ppm");		
		gtk_widget_show(CurrObject->Widget);
	}
	
}

/*function to take care of all event*/
void Control_ProcessEvent(ObjectHandle * ClickedObject){
	
	ViewHandle * MainViewHandle = ClickedObject->MainViewHandle;
	ControlHandle * MainControlHandle = MainViewHandle->MainControlHandle;
	/*ObjectHandle * CurrObject;*/
	
	
	IMAGE * NewImage = NULL;
		
	/* char name[MAX_HASH_KEY_LENGTH];*//* = {"MainWindow", "RotateWindow"};*/
#ifdef DEBUG
	printf("Object clicked has name: %s\n", ClickedObject->Name);
#endif
/*======================================================================*/
	if (strcmp(ClickedObject->Name,"OpenFile") == 0){
		OpenImageFile(MainControlHandle->InputImageFileName);
		
#ifdef DEBUG
		printf("Input file name is %s\n", utstring_body(MainControlHandle->InputImageFileName));
		utstring_printf(MainControlHandle->InputImageFileName, "/home/group1/Programming/EECS22L_Project2/Images/CourierNew12_300DPI.ppm");
#endif
		/*load the image here*/
#if JAMIE_READ_IMAGE
	/*Jamie function*/
#else
		/*ReadImage(*/
		
#endif
		DeleteImageList(MainControlHandle->MainImageList);
		MainControlHandle->MainImageList = NewImageList();
		AppendImage(MainControlHandle->MainImageList, NewImage);
		UpdateDisplayImage(MainControlHandle);
/*======================================================================*/
	} else if (strcmp(ClickedObject->Name,"SaveFile") == 0){
		SaveTextFile(MainControlHandle->OutputFileName);
		FILE * NewFile = fopen(utstring_body(MainControlHandle->OutputFileName), "w");
		if (NewFile){
			fprintf(NewFile, "%s", utstring_body(MainControlHandle->MainOutputString));
			fclose(NewFile);
		} else {
			printf("Can't open file %s\n", utstring_body(MainControlHandle->MainOutputString));
		}
/*======================================================================*/		
	} else if (strcmp(ClickedObject->Name,"ConvertBW") == 0){
		if (!MainControlHandle->MainImageList->Last){
			show_error("No image loaded yet");
		} else {
			NewImage = DuplicateImage(MainControlHandle->MainImageList->Last->Image);
			BlackNWhite(NewImage);
			AppendImage(MainControlHandle->MainImageList, NewImage);
			UpdateDisplayImage(MainControlHandle);
		}
/*======================================================================*/			
	} else if (strcmp(ClickedObject->Name,"RemoveStain") == 0){
		show_error("Not supported yet");
	} else if (strcmp(ClickedObject->Name,"RemoveWrinkle") == 0){
		show_error("Not supported yet");
	} else if (strcmp(ClickedObject->Name,"Rotate") == 0){
		
	} else if (strcmp(ClickedObject->Name,"LineBoundary") == 0){
	
		
	} else if (strcmp(ClickedObject->Name,"Crop") == 0){
		
		
	} else if (strcmp(ClickedObject->Name,"PerformOCR") == 0){
		
	} else if (strcmp(ClickedObject->Name,"EditText") == 0){
		
	} else if (strcmp(ClickedObject->Name,"Dictionary") == 0){
		
	}
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


void SaveTextFile(UT_string * OutputFileName){
	GtkWidget *dialog;

	dialog = gtk_file_chooser_dialog_new ("Save File",
							NULL,
							GTK_FILE_CHOOSER_ACTION_SAVE,
							("_Cancel"), GTK_RESPONSE_CANCEL,
							("_Save"), GTK_RESPONSE_ACCEPT,
							NULL);
	gtk_file_chooser_set_do_overwrite_confirmation (GTK_FILE_CHOOSER (dialog), TRUE);

	/*if (user_edited_a_new_document)*/
		gtk_file_chooser_set_current_name (GTK_FILE_CHOOSER (dialog), "Untitled document");
	/*else
		gtk_file_chooser_set_filename (GTK_FILE_CHOOSER (dialog), filename_for_existing_document);*/

	if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
	{
		char *filename;

		filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
		utstring_printf(OutputFileName, "%s", filename);
		g_free (filename);
	}

	gtk_widget_destroy (dialog);
	
}


void show_error(const gchar * ErrorMessage)
{
  GtkWidget *dialog;
  dialog = gtk_message_dialog_new(NULL,
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            ErrorMessage);
  gtk_window_set_title(GTK_WINDOW(dialog), "Error");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
}

void on_rotate_clicked(){


}

#if 0		/*reserved for beta release: get coordinate by clickon on screen*/
CurrObject = NULL;
GtkRequisition requisition;
	GtkAllocation allocation;
		HASH_FIND(HashByName,MainViewHandle->ObjectListByName, name, sizeof(char) * MAX_HASH_KEY_LENGTH,CurrObject);
		if (CurrObject) {	
			/*printf("%d %d\n", CurrObject->Widget->allocation.x, CurrObject->Widget->allocation.y);
			gtk_widget_size_request(CurrObject->Widget, &requisition);
			printf("Image scroll window is %d wide\n",requisition.width);*/
			gtk_widget_get_allocation(CurrObject->Widget, &allocation);
			printf("Image scroll window is %d wide\n",allocation.width);
			
		}
		else printf("Can't find ImageScrollWindow\n");
#endif