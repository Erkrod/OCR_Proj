

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
	char name[MAX_HASH_KEY_LENGTH] =  "MainDisplayImage";
	/*strcpy(name, "MainDisplayImage");*/
	HASH_FIND(HashByName,MainControlHandle->MainViewHandle->ObjectListByName, name, sizeof(char) * MAX_HASH_KEY_LENGTH,CurrObject);
	assert(CurrObject);
	
	/*save last image to a temp file first*/
	if (MainControlHandle->MainImageList->Last){
		assert(!SaveImage("Temp", MainControlHandle->MainImageList->Last->Image));
		gtk_image_set_from_file(GTK_IMAGE(CurrObject->Widget), "Temp.ppm");		
		gtk_widget_show(CurrObject->Widget);
	}
	
}

/*function to take care of all event*/
void Control_ProcessEvent(ObjectHandle * ClickedObject){
	
	ViewHandle * MainViewHandle = ClickedObject->MainViewHandle;
	ControlHandle * MainControlHandle = MainViewHandle->MainControlHandle;
	ObjectHandle * CurrObject;
	IMAGE * NewImage = NULL;
	int x1, y1, x2, y2, degree;
		
	/* char name[MAX_HASH_KEY_LENGTH];*//* = {"MainWindow", "RotateWindow"};*/
#ifdef DEBUG
	printf("Object clicked has name: %s\n", ClickedObject->Name);
#endif
/*======================================================================*/
	if (strcmp(ClickedObject->Name,"OpenFile") == 0){
		OpenImageFile(MainControlHandle->InputImageFileName);
		/*NEED TO PUT A FILTER HERE*/
		/*load the image here*/
		NewImage = ReadImage(utstring_body(MainControlHandle->InputImageFileName));		
		if (NewImage){
			DeleteImageList(MainControlHandle->MainImageList);
			MainControlHandle->MainImageList = NewImageList();
			AppendImage(MainControlHandle->MainImageList, NewImage);
			UpdateDisplayImage(MainControlHandle);
		} else {
			show_error("Can't read image");
		}
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
/*======================================================================*/	
	} else if (strcmp(ClickedObject->Name,"Rotate") == 0){	
		char nameRotateWindow[MAX_HASH_KEY_LENGTH] =  "RotateWindow";
		HASH_FIND(HashByName,MainControlHandle->MainViewHandle->ObjectListByName, nameRotateWindow, sizeof(char) * MAX_HASH_KEY_LENGTH,CurrObject);
		assert(CurrObject);
		gtk_widget_show(CurrObject->Widget);		
/*======================================================================*/		
	} else if (strcmp(ClickedObject->Name,"RotateButton") == 0){	
		if (!MainControlHandle->MainImageList->Last){
			show_error("No image loaded yet");
		} else {
			char nameRotateDegreeBox[MAX_HASH_KEY_LENGTH] =  "RotateSpinner";
			HASH_FIND(HashByName,MainControlHandle->MainViewHandle->ObjectListByName, nameRotateDegreeBox, sizeof(char) * MAX_HASH_KEY_LENGTH,CurrObject);
			assert(CurrObject);
			degree = floor(gtk_spin_button_get_value(GTK_SPIN_BUTTON(CurrObject->Widget)));
			NewImage = Rotate(MainControlHandle->MainImageList->Last->Image, degree);
			AppendImage(MainControlHandle->MainImageList, NewImage);
			UpdateDisplayImage(MainControlHandle);
		}
	} else if (strcmp(ClickedObject->Name,"LineBoundary") == 0){
	
/*======================================================================*/		
	} else if (strcmp(ClickedObject->Name,"Crop") == 0){
		char nameCropWindow[MAX_HASH_KEY_LENGTH] =  "CropWindow";
		HASH_FIND(HashByName,MainControlHandle->MainViewHandle->ObjectListByName, nameCropWindow, sizeof(char) * MAX_HASH_KEY_LENGTH,CurrObject);
		assert(CurrObject);
		gtk_widget_show(CurrObject->Widget);		
		
		
/*======================================================================*/
	} else if (strcmp(ClickedObject->Name,"CropButton") == 0){
		if (!MainControlHandle->MainImageList->Last){
			show_error("No image loaded yet");
		} else {
			GetCropCoordinate(MainControlHandle, &x1, &y1, &x2, &y2);
			if (x1 > MainControlHandle->MainImageList->Last->Image->Width ||
				x2 > MainControlHandle->MainImageList->Last->Image->Width ||
				y1 > MainControlHandle->MainImageList->Last->Image->Height ||
				y2 > MainControlHandle->MainImageList->Last->Image->Height)
				show_error("Coordinates out of bound");
			else {
				NewImage = CropImage(MainControlHandle->MainImageList->Last->Image, x1, y1, x2, y2);
				AppendImage(MainControlHandle->MainImageList, NewImage);
				UpdateDisplayImage(MainControlHandle);
			}
		}
		
		
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
	  utstring_clear(ImageFileName);
        utstring_printf(ImageFileName, "%s", filename);
        g_free (filename);
    } else {
	  utstring_clear(ImageFileName);
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
		utstring_clear(OutputFileName);
		utstring_printf(OutputFileName, "%s", filename);
		g_free (filename);
	}

	gtk_widget_destroy (dialog);
	
}

void GetCropCoordinate(ControlHandle * MainControlHandle, int * x1, int * y1, int * x2, int * y2){
	char name1[MAX_HASH_KEY_LENGTH] =  "CropSpin";
	char name2[MAX_HASH_KEY_LENGTH] =  "CropSpin2";
	char name3[MAX_HASH_KEY_LENGTH] =  "CropSpin3";
	char name4[MAX_HASH_KEY_LENGTH] =  "CropSpin4";
	ObjectHandle * CurrObject;
	HASH_FIND(HashByName,MainControlHandle->MainViewHandle->ObjectListByName, name1, sizeof(char) * MAX_HASH_KEY_LENGTH,CurrObject);
	assert(CurrObject);
	*x1 = floor(gtk_spin_button_get_value(GTK_SPIN_BUTTON(CurrObject->Widget)));
	HASH_FIND(HashByName,MainControlHandle->MainViewHandle->ObjectListByName, name2, sizeof(char) * MAX_HASH_KEY_LENGTH,CurrObject);
	assert(CurrObject);
	*y1 = floor(gtk_spin_button_get_value(GTK_SPIN_BUTTON(CurrObject->Widget)));
	HASH_FIND(HashByName,MainControlHandle->MainViewHandle->ObjectListByName, name3, sizeof(char) * MAX_HASH_KEY_LENGTH,CurrObject);
	assert(CurrObject);
	*x2 = floor(gtk_spin_button_get_value(GTK_SPIN_BUTTON(CurrObject->Widget)));
	HASH_FIND(HashByName,MainControlHandle->MainViewHandle->ObjectListByName, name4, sizeof(char) * MAX_HASH_KEY_LENGTH,CurrObject);
	assert(CurrObject);
	*y2 = floor(gtk_spin_button_get_value(GTK_SPIN_BUTTON(CurrObject->Widget)));
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