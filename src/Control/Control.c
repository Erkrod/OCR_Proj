#include "Control.h"
#include "DrawFunctions.h"


void ClearTextArea(ControlHandle * MainControlHandle);

void AppendTextArea(ControlHandle * MainControlHandle, char * DisplayString);

void UpdateTextArea(ControlHandle * MainControlHandle, char * DisplayString);

char * GetTextArea(ControlHandle * MainControlHandle, char * DisplayString);

ObjectHandle * FindObject(ControlHandle * MainControlHandle, const char * Name);

void show_compilation_msg(ControlHandle * MainControlHandle, const char * CompileMessage);

IMAGE * ResizeFitScreen(ControlHandle * MainControlHandle, IMAGE * original_image);

void UpdateMainOutputString(ControlHandle * MainControlHandle){
	ObjectHandle * CurrObject = FindObject(MainControlHandle, "MainTextArea");
	GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(CurrObject->Widget));;
	GtkTextIter iter1, iter2;
	gtk_text_buffer_get_start_iter(buffer, &iter1);
	gtk_text_buffer_get_end_iter(buffer, &iter2);
	utstring_clear(MainControlHandle->MainOutputString);
	utstring_printf(MainControlHandle->MainOutputString, "%s", gtk_text_buffer_get_text(buffer, &iter1, &iter2, FALSE));
	
}

int GetStainRemovalParams(ControlHandle * MainControlHandle, int * var1, int * var2, int * b_thres, int * dark_limit);

int GetOCRParams(ControlHandle * MainControlHandle, FontType * Font, int * FontSize, int *ScanRes, int *IsoAlg, int *UseDict);

int GetColorFilterParams(ControlHandle * MainControlHandle, int * x, int * y, int *x1, int *y1, int *x2, int *y2, int *new_value, int *thres_value);

ObjectHandle * FindObject(ControlHandle * MainControlHandle, const char * Name){
#ifdef DEBUG
	printf("Finding object with name %s\n", Name);
#endif
	char name[MAX_HASH_KEY_LENGTH];
	ObjectHandle * CurrObject;
	memset(name, 0, sizeof(char) * MAX_HASH_KEY_LENGTH);
	strcpy(name, Name);
	CurrObject = NULL;
	HASH_FIND(HashByName,MainControlHandle->MainViewHandle->ObjectListByName, name, sizeof(char) * MAX_HASH_KEY_LENGTH,CurrObject);
	assert(CurrObject);
	return CurrObject;
}

ControlHandle * Control_Initialize(void){
	ControlHandle * ToReturn = (ControlHandle *) malloc(sizeof(ControlHandle));
	ToReturn->MainViewHandle = View_Initialize(ToReturn);
	ToReturn->MainImageList = NewImageList();
	utstring_new(ToReturn->InputImageFileName);
	utstring_new(ToReturn->MainOutputString);
	utstring_new(ToReturn->OutputFileName);
	ToReturn->State = Normal;
	ToReturn->IsInPreview = 0;
	ToReturn->InitialImage = 1;	
	ToReturn->InitialText = 1;	
	drawAllWindows(ToReturn->MainViewHandle);
	
	/*for post processing*/
	/*utarray_new(ToReturn->KeywordArray, &ut_str_icd);
	utarray_new(ToReturn->SpecialCharArray, &ut_str_icd);
	postProcessingInitialize(ToReturn->KeywordArray, ToReturn->SpecialCharArray);*/
	
	/*read templates*/
	ToReturn->CourierNewTemplate = InitializeTemplate();
	
	/*set initial image and string here*/
	ObjectHandle * ImageDisplay = FindObject(ToReturn, "MainDisplayImage");
	if (file_exist("Images/ocrLarge.png"))
		gtk_image_set_from_file(GTK_IMAGE(ImageDisplay->Widget), "Images/ocrLarge.png");
		
	FILE * file = fopen("README.txt", "r");
	if (file){
		fseek( file , 0L , SEEK_END);
		long lSize = ftell( file );
		rewind( file );
		char * ReadString = (char *) malloc(sizeof(char) * lSize);
		assert(ReadString);
		
		if( 1!=fread( ReadString , lSize, sizeof(char) , file) )
			fclose(file),free(ReadString),fputs("Can't read README.txt",stderr),exit(1);
		fclose(file);
		printf("%s\n", ReadString);
		UpdateTextArea(ToReturn, ReadString);
		free(ReadString);
	}
	
	return ToReturn;
}

void SetCursorImageBox(ControlHandle * MainControlHandle){
	/*set the cursor here*/
	/*find the ImageWindow*/		
	ObjectHandle * CurrObject = FindObject(MainControlHandle, "ImageScrollWindow");
	
	/*put the coordinate selection here temporarily*/
	if (MainControlHandle->State == SelectCoordinate){
		GdkCursor* CrossCursor = gdk_cursor_new(GDK_CROSSHAIR);			
		gdk_window_set_cursor(CurrObject->Widget->window, CrossCursor);
		
	} else {
		/*set cursor to normal*/
		gdk_window_set_cursor(CurrObject->Widget->window, NULL);
	}
}

void GetClickCoord(ControlHandle * MainControlHandle, int orig_x, int orig_y, int * ret_x, int * ret_y){
	if (MainControlHandle->MainImageList->Last){
		GtkAllocation allocation;
		ObjectHandle * CurrObject;
		CurrObject = FindObject(MainControlHandle, "ImageScrollWindow");
		gtk_widget_get_allocation(CurrObject->Widget, &allocation);
		
		
		/*get image widht and height*/
		
		if (MainControlHandle->DisplayWidth >= allocation.width) *ret_x = orig_x * MainControlHandle->OriginalWidth / MainControlHandle->DisplayWidth;
		else 	*ret_x = (orig_x - (allocation.width - MainControlHandle->DisplayWidth)/2) * MainControlHandle->OriginalWidth / MainControlHandle->DisplayWidth;
		if (MainControlHandle->DisplayHeight >= allocation.height) *ret_y = orig_y * MainControlHandle->OriginalHeight / MainControlHandle->DisplayHeight;
		else 	*ret_y = (orig_y - (allocation.height - MainControlHandle->DisplayHeight)/2)* MainControlHandle->OriginalHeight / MainControlHandle->DisplayHeight;
#ifdef DEBUG
		printf("return value x = %d, y = %d\n", *ret_x, *ret_y);
#endif
	}
}

void Control_MainLoop(ControlHandle * MainHandle){
	
	gtk_main();
}

void Control_CleanUp(ControlHandle * MainHandle){
	utstring_free(MainHandle->InputImageFileName);
	utstring_free(MainHandle->MainOutputString);
	utstring_free(MainHandle->OutputFileName);
	free(MainHandle);
}

void UpdateDisplayImage(ControlHandle * MainControlHandle){
	ObjectHandle * CurrObject;
	CurrObject = FindObject(MainControlHandle, "MainDisplayImage");
	/*save last image to a temp file first*/
	if (MainControlHandle->IsInPreview){
		assert(!SaveImage("Temp", ResizeFitScreen(MainControlHandle, MainControlHandle->PreviewImage)));
		gtk_image_set_from_file(GTK_IMAGE(CurrObject->Widget), "Temp.ppm");		
		gtk_widget_show(CurrObject->Widget);
	} else if (MainControlHandle->MainImageList->Last){
		assert(!SaveImage("Temp", ResizeFitScreen(MainControlHandle, MainControlHandle->MainImageList->Last->Image)));
		gtk_image_set_from_file(GTK_IMAGE(CurrObject->Widget), "Temp.ppm");		
		gtk_widget_show(CurrObject->Widget);
	} else {
		gtk_image_clear(GTK_IMAGE(CurrObject->Widget));
	}
	
	
	
}

void ClearTextArea(ControlHandle * MainControlHandle){
	ObjectHandle * CurrObject = FindObject(MainControlHandle, "MainTextArea");
	GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(CurrObject->Widget));;
	GtkTextIter iter1, iter2;
	gtk_text_buffer_get_start_iter(buffer, &iter1);
	gtk_text_buffer_get_end_iter(buffer, &iter2);
	gtk_text_buffer_delete(buffer, &iter1, &iter2);
}

void AppendTextArea(ControlHandle * MainControlHandle, char * DisplayString){
	if (MainControlHandle->InitialText) ClearTextArea(MainControlHandle);
	ObjectHandle * CurrObject = FindObject(MainControlHandle, "MainTextArea");
	GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(CurrObject->Widget));
	GtkTextIter iter;
	gtk_text_buffer_get_end_iter(buffer, &iter);
	gtk_text_buffer_insert(buffer, &iter, "\n", -1);
	gtk_text_buffer_insert(buffer, &iter, DisplayString, -1);
}

void UpdateTextArea(ControlHandle * MainControlHandle, char * DisplayString){
	ClearTextArea(MainControlHandle);
	
	ObjectHandle * CurrObject = FindObject(MainControlHandle, "MainTextArea");
	GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(CurrObject->Widget));
	GtkTextIter iter;
	gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
	gtk_text_buffer_insert(buffer, &iter, DisplayString, -1);
}

char * GetTextArea(ControlHandle * MainControlHandle, char * DisplayString){
	ObjectHandle * CurrObject = FindObject(MainControlHandle, "MainTextArea");
	GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(CurrObject->Widget));;
	GtkTextIter iter1, iter2;
	gtk_text_buffer_get_start_iter(buffer, &iter1);
	gtk_text_buffer_get_end_iter(buffer, &iter2);
	return gtk_text_buffer_get_text(buffer, &iter1, &iter2, FALSE);
}

void SetSentitiveAllWindows(ControlHandle * MainControlHandle, gboolean Sensitivity){
	ObjectHandle * CurrObject;
	char Name1[MAX_HASH_KEY_LENGTH] = "MainWindow";
	char Name2[MAX_HASH_KEY_LENGTH] = "MenuBar";
	char Name3[MAX_HASH_KEY_LENGTH] = "RotateWindow";
	char Name4[MAX_HASH_KEY_LENGTH] = "CropWindow";
	char Name5[MAX_HASH_KEY_LENGTH] = "ColorFilterWindow";
	char Name6[MAX_HASH_KEY_LENGTH] = "OCRWindow";
	/*char Name5[MAX_HASH_KEY_LENGTH] = "OCRWindow";
	char Name5[MAX_HASH_KEY_LENGTH] = "OCRWindow";
	char Name5[MAX_HASH_KEY_LENGTH] = "OCRWindow";*/
	//strcpy(Name, "MainWindow");
	
	HASH_FIND(HashByName,MainControlHandle->MainViewHandle->ObjectListByName, Name1, sizeof(char) * MAX_HASH_KEY_LENGTH,CurrObject);
	assert(CurrObject);
	gtk_widget_set_sensitive(CurrObject->Widget, Sensitivity);
	HASH_FIND(HashByName,MainControlHandle->MainViewHandle->ObjectListByName, Name2, sizeof(char) * MAX_HASH_KEY_LENGTH,CurrObject);
	assert(CurrObject);
	gtk_widget_set_sensitive(CurrObject->Widget, Sensitivity);
	HASH_FIND(HashByName,MainControlHandle->MainViewHandle->ObjectListByName, Name3, sizeof(char) * MAX_HASH_KEY_LENGTH,CurrObject);
	assert(CurrObject);
	gtk_widget_set_sensitive(CurrObject->Widget, Sensitivity);
	HASH_FIND(HashByName,MainControlHandle->MainViewHandle->ObjectListByName, Name4, sizeof(char) * MAX_HASH_KEY_LENGTH,CurrObject);
	assert(CurrObject);
	gtk_widget_set_sensitive(CurrObject->Widget, Sensitivity);
	HASH_FIND(HashByName,MainControlHandle->MainViewHandle->ObjectListByName, Name5, sizeof(char) * MAX_HASH_KEY_LENGTH,CurrObject);
	assert(CurrObject);
	gtk_widget_set_sensitive(CurrObject->Widget, Sensitivity);
	HASH_FIND(HashByName,MainControlHandle->MainViewHandle->ObjectListByName, Name6, sizeof(char) * MAX_HASH_KEY_LENGTH,CurrObject);
	assert(CurrObject);
	gtk_widget_set_sensitive(CurrObject->Widget, Sensitivity);
	
}

void PopPreviewImage(ControlHandle * MainControlHandle){
	MainControlHandle->IsInPreview = 0;	
	if (MainControlHandle->PreviewImage){
		DeleteImage(MainControlHandle->PreviewImage);
		MainControlHandle->PreviewImage = NULL;
	}
}

/*function to take care of all event*/
void Control_ProcessEvent(ObjectHandle * ClickedObject, GdkEvent * event){
	
	ViewHandle * MainViewHandle = ClickedObject->MainViewHandle;
	ControlHandle * MainControlHandle = MainViewHandle->MainControlHandle;
	ObjectHandle * CurrObject;
	IMAGE * NewImage = NULL;
	int x1, y1, x2, y2, degree;
		
	/*catch the case that you are selecting coordinate then select another one*/
	if (MainControlHandle->State == SelectCoordinate && strcmp(ClickedObject->Name,"DisplayEventBox")){
		MainControlHandle->State = Normal;
		SetCursorImageBox(MainControlHandle);
	}
	
#ifdef DEBUG
	printf("Object clicked has name: %s\n", ClickedObject->Name);
#endif
/*======================================================================*/
	if (strcmp(ClickedObject->Name,"OpenFile") == 0){
		OpenImageFile(MainControlHandle->InputImageFileName);
		
		/*load the image here*/
		if (utstring_len(MainControlHandle->InputImageFileName) > 0) {
			NewImage = ReadImage(utstring_body(MainControlHandle->InputImageFileName));		
			if (NewImage){
				DeleteImageList(MainControlHandle->MainImageList);
				MainControlHandle->MainImageList = NewImageList();
				MainControlHandle->IsInPreview = 0;
				MainControlHandle->State = Normal;
				AppendImage(MainControlHandle->MainImageList, NewImage);
				UpdateDisplayImage(MainControlHandle);
			} else {
				show_error("Can't read image");
			}
		}
/*======================================================================*/
	} else if (strcmp(ClickedObject->Name,"SaveFile") == 0){
		SaveTextFile(MainControlHandle->OutputFileName);
		if (utstring_len(MainControlHandle->OutputFileName) > 0) {
			FILE * NewFile = fopen(utstring_body(MainControlHandle->OutputFileName), "w");
			if (NewFile){
				fprintf(NewFile, "%s", utstring_body(MainControlHandle->MainOutputString));
				fclose(NewFile);
			} else {
				printf("Can't open file %s\n", utstring_body(MainControlHandle->MainOutputString));
			}
		}
/*======================================================================*/			
	} else if (strcmp(ClickedObject->Name,"UndoPreproc") == 0){
		if (MainControlHandle->IsInPreview == 1) PopPreviewImage(MainControlHandle);
		else PopLastImage(MainControlHandle->MainImageList);
		UpdateDisplayImage(MainControlHandle);
		
/*======================================================================*/		
	} else if (strcmp(ClickedObject->Name,"ConvertBW") == 0){
		if (!MainControlHandle->MainImageList->Last){
			show_error("No image loaded yet");
		} else {
			PopPreviewImage(MainControlHandle);
			NewImage = DuplicateImage(MainControlHandle->MainImageList->Last->Image);
			BlackNWhite(NewImage);
			AppendImage(MainControlHandle->MainImageList, NewImage);
			UpdateDisplayImage(MainControlHandle);
		}
		
/*======================================================================*/
	} else if (strcmp(ClickedObject->Name,"RemoveStain") == 0){
		CurrObject = FindObject(MainControlHandle, "RemoveStainWin");
		gtk_widget_show(CurrObject->Widget);
/*======================================================================*/	
	} else if (strcmp(ClickedObject->Name,"RemoveStainButton") == 0){
		if (MainControlHandle->MainImageList->Last){		
			int var1, var2, b_thres, dark_limit;
			int result = GetStainRemovalParams(MainControlHandle, &var1, &var2, &b_thres, &dark_limit);
			if (result == 0){				
				IMAGE * NewImage = StainRemoval(MainControlHandle->MainImageList->Last->Image, var1, var2, b_thres, dark_limit);
				if (NewImage){
					PopPreviewImage(MainControlHandle);
					AppendImage(MainControlHandle->MainImageList, NewImage);
					UpdateDisplayImage(MainControlHandle);
				} else show_error("Can't perform Stain Removal");				
			} else if (result == 1){
				show_error("Invalid Variance 1");
			} else if (result == 2){
				show_error("Invalid Variance 2");
			} else if (result == 3){
				show_error("Invalid Black threshold");
			} else if (result == 4){
				show_error("Invalid dark limiter");
			}
		}		
/*======================================================================*/
	} else if (strcmp(ClickedObject->Name,"ColorFilter") == 0){
		CurrObject = FindObject(MainControlHandle, "ColorFilterWindow");
		gtk_widget_show(CurrObject->Widget);	

/*======================================================================*/
	} else if (strcmp(ClickedObject->Name,"FilterButton") == 0){	
		if (!MainControlHandle->MainImageList->Last){
			show_error("No image loaded yet");
		} else {
			int x, y, x1, y1, x2, y2, new_pix, thres;
			int result = GetColorFilterParams(MainControlHandle, &x, &y, &x1, &y1, &x2, &y2, &new_pix, &thres);
			IMAGE * NewImage;
			switch (result){
				case 1:
					show_error("Invalid Reference point X coordinate");
					break;
				case 2:
					show_error("Invalid Reference point Y coordinate");
					break;
				case 3:
					show_error("Invalid Area X1 coordinate");
					break;
				case 4:
					show_error("Invalid Area Y1 coordinate");
					break;
				case 5:
					show_error("Invalid Area X2 coordinate");
					break;
				case 6:
					show_error("Invalid Area Y2 coordinate");
					break;
				case 7:
					show_error("Invalid New pixel value");
					break;
				case 8:
					show_error("Invalid threshold value");
					break;
				case 0:
					NewImage = ColorFilter(MainControlHandle->MainImageList->Last->Image, x, y, x1, y1, x2, y2, new_pix, thres);
					if (!NewImage) show_error("Can't color filter this image");
					else {
						PopPreviewImage(MainControlHandle);
						AppendImage(MainControlHandle->MainImageList, NewImage);
						UpdateDisplayImage(MainControlHandle);
					}
			}
		}
		
/*======================================================================*/
	} else if (strcmp(ClickedObject->Name,"RefSelCoord") == 0){	
		MainControlHandle->State = SelectCoordinate;
		MainControlHandle->XCoordObject = FindObject(MainControlHandle, "Xspinner");
		MainControlHandle->YCoordObject = FindObject(MainControlHandle, "Yspinner");
		SetCursorImageBox(MainControlHandle);
	
/*======================================================================*/
	} else if (strcmp(ClickedObject->Name,"AreaSelCoord1") == 0){	
		MainControlHandle->State = SelectCoordinate;
		MainControlHandle->XCoordObject = FindObject(MainControlHandle, "X1spinner");
		MainControlHandle->YCoordObject = FindObject(MainControlHandle, "Y1spinner");
		SetCursorImageBox(MainControlHandle);

/*======================================================================*/
	} else if (strcmp(ClickedObject->Name,"AreaSelCoord2") == 0){	
		MainControlHandle->State = SelectCoordinate;
		MainControlHandle->XCoordObject = FindObject(MainControlHandle, "X2spinner");
		MainControlHandle->YCoordObject = FindObject(MainControlHandle, "Y2spinner");
		SetCursorImageBox(MainControlHandle);
		
/*======================================================================*/	
	} else if (strcmp(ClickedObject->Name,"Rotate") == 0){
		PopPreviewImage(MainControlHandle);		
		CurrObject = FindObject(MainControlHandle, "RotateWindow");
		gtk_widget_show(CurrObject->Widget);		
/*======================================================================*/		
	} else if (strcmp(ClickedObject->Name,"RotateButton") == 0){	
		if (!MainControlHandle->MainImageList->Last){
			show_error("No image loaded yet");
		} else {			
			CurrObject = FindObject(MainControlHandle, "RotateSpinner");
			degree = floor(gtk_spin_button_get_value(GTK_SPIN_BUTTON(CurrObject->Widget)));
			NewImage = Rotate(MainControlHandle->MainImageList->Last->Image, degree);
			if (NewImage){
				PopPreviewImage(MainControlHandle);
				AppendImage(MainControlHandle->MainImageList, NewImage);
				UpdateDisplayImage(MainControlHandle);
			} else show_error("Can't rotate this image. Maybe you don't have correct netpbm version.");				
		}
/*======================================================================*/		
	} else if (strcmp(ClickedObject->Name,"Crop") == 0){		
		CurrObject = FindObject(MainControlHandle, "CropWindow");		
		gtk_widget_show(CurrObject->Widget);		
		
/*======================================================================*/
	} else if (strcmp(ClickedObject->Name,"CropButton") == 0){
		if (!MainControlHandle->MainImageList->Last){
			show_error("No image loaded yet");
		} else {			
			int result = GetCropCoordinate(MainControlHandle, &x1, &y1, &x2, &y2);
			if (result == 5){
				show_error("No image loaded yet");
			} else if (result == 1){
				show_error("Invalid X1");
			} else if (result == 2){
				show_error("Invalid Y1");
			} else if (result == 3){
				show_error("Invalid X2");
			} else if (result == 4){
				show_error("Invalid Y2");
			} else {
				PopPreviewImage(MainControlHandle);
				NewImage = CropImage(MainControlHandle->MainImageList->Last->Image, x1, y1, x2, y2);
				AppendImage(MainControlHandle->MainImageList, NewImage);
				UpdateDisplayImage(MainControlHandle);
			}
		}
/*======================================================================*/
	} else if (strcmp(ClickedObject->Name,"CropCoord1") == 0){	
		MainControlHandle->State = SelectCoordinate;
		MainControlHandle->XCoordObject = FindObject(MainControlHandle, "CropSpin");
		MainControlHandle->YCoordObject = FindObject(MainControlHandle, "CropSpin2");
		SetCursorImageBox(MainControlHandle);
/*======================================================================*/	
	} else if (strcmp(ClickedObject->Name,"CropCoord2") == 0){	
		MainControlHandle->State = SelectCoordinate;
		MainControlHandle->XCoordObject = FindObject(MainControlHandle, "CropSpin3");
		MainControlHandle->YCoordObject = FindObject(MainControlHandle, "CropSpin4");
		SetCursorImageBox(MainControlHandle);
		
/*======================================================================*/		
	} else if (strcmp(ClickedObject->Name,"PerformOCR") == 0){
		CurrObject = FindObject(MainControlHandle,"OCRWindow");
		gtk_widget_show(CurrObject->Widget);
		
/*======================================================================*/		
	} else if (strcmp(ClickedObject->Name,"OCRButton") == 0){
		if (!MainControlHandle->MainImageList->Last){
			show_error("No image loaded yet");
		} else {			
			/*get information about font, font size and scan resolution*/
			FontType Font = CourierNew; int FontSize = 12, ScanRes = 300;
			int IsolateAlgorithm = 0, UseDictionary = 0;
			int result = GetOCRParams(MainControlHandle, &Font, &FontSize, &ScanRes, &IsolateAlgorithm, &UseDictionary);
			if (result == 1){
				show_error("Invalid Font");
			} else if (result == 2){
				show_error("Invalid FontSize");
			} else if (result == 3){
				show_error("Invalid Scan resolution");
			} else if (result == 4){
				show_error("Invalid Isolate Algorithm");
			} else if (result == 5){
				show_error("Invalid PostProcessing option");
			} else {
				/*cut the image into pieces and display it*/
				
				ILIST * CutList = NULL;
				if (IsolateAlgorithm == 0) CutList = LazyIsolateCharacter(MainControlHandle->MainImageList->Last->Image, Font, FontSize, ScanRes);
				else if (IsolateAlgorithm == 1) CutList = ActiveIsolateCharacter(MainControlHandle->MainImageList->Last->Image, Font, FontSize, ScanRes);
				if (!CutList) show_error("Can't perform OCR on this image.");
				else {
					/*Identify them into probability*/
					UT_array * temp_array = IdentifyCharacter(CutList, MainControlHandle->CourierNewTemplate);
					DeleteImageList(CutList);
										
					/*post processing*/
					UT_string * temp_string = postProcessing(temp_array);
					utstring_clear(MainControlHandle->MainOutputString);
					utstring_printf(MainControlHandle->MainOutputString, "%s", utstring_body(temp_string));
					
					/*display the text*/				
					AppendTextArea(MainControlHandle,utstring_body(MainControlHandle->MainOutputString));
				}
			}
			
			
			
			
		}
/*======================================================================*/		
	} else if (strcmp(ClickedObject->Name,"PreviewIsolate") == 0){
		if (!MainControlHandle->MainImageList->Last){
			show_error("No image loaded yet");
		} else {			
			/*get information about font, font size and scan resolution*/
			FontType Font = CourierNew; int FontSize = 12, ScanRes = 300;
			int IsolateAlgorithm = 0, UseDictionary = 0;
			int result = GetOCRParams(MainControlHandle, &Font, &FontSize, &ScanRes, &IsolateAlgorithm, &UseDictionary);
			if (result == 1){
				show_error("Invalid Font");
			} else if (result == 2){
				show_error("Invalid FontSize");
			} else if (result == 3){
				show_error("Invalid Scan resolution");
			} else if (result == 4){
				show_error("Invalid Isolate Algorithm");
			} else if (result == 5){
				show_error("Invalid PostProcessing option");
			} else {	
				IMAGE * PreviewImage = NULL;
				if (IsolateAlgorithm == 0) PreviewImage = PreviewLazyIsolateCharacter(MainControlHandle->MainImageList->Last->Image, Font, FontSize, ScanRes);
				else if (IsolateAlgorithm == 1) PreviewImage = PreviewActiveIsolateCharacter(MainControlHandle->MainImageList->Last->Image, Font, FontSize, ScanRes);				
				if(!PreviewImage){show_error("Can't perform Isolate character on this image");}
				else {
					if (MainControlHandle->PreviewImage) DeleteImage(MainControlHandle->PreviewImage);
					MainControlHandle->PreviewImage = PreviewImage;
					MainControlHandle->IsInPreview = 1;
					UpdateDisplayImage(MainControlHandle);				
				}
			}
		}
/*======================================================================*/
	} else if (strcmp(ClickedObject->Name,"EditText") == 0){		
		/*write it to a temp file*/
		FILE * NewFile = fopen("TempOutputText.txt", "w");
		if (!NewFile){
			show_error("Can't write to TempOutputText.txt");
		} else {
			fprintf(NewFile, "%s", utstring_body(MainControlHandle->MainOutputString));
			fclose(NewFile);			
			if (0 != system("gedit TempOutputText.txt")) show_error("Can't run gedit on TempOutputText.txt");
		}
		
/*======================================================================*/
	} else if (strcmp(ClickedObject->Name,"CompileCode") == 0){
		UpdateMainOutputString(MainControlHandle);
		
		if (utstring_len(MainControlHandle->MainOutputString) > 0){
			UT_string * msg = GetCompileMessage(MainControlHandle->MainOutputString);
			show_compilation_msg(MainControlHandle, utstring_body(msg));
			utstring_free(msg);
		}
	
/*======================================================================*/
	} else if (strcmp(ClickedObject->Name,"DisplayEventBox") == 0){		
		if (MainControlHandle->State == SelectCoordinate){
			int XClicked = 0, YClicked = 0;
			//printf("original event data x = %lf; y = %lf\n", event->button.x, event->button.y);
			GetClickCoord(MainControlHandle, event->button.x, event->button.y, &XClicked, &YClicked);
			if (MainControlHandle->MainImageList->Last){
				if (XClicked >= 0 && XClicked < MainControlHandle->MainImageList->Last->Image->Width &&
					YClicked >= 0 && YClicked < MainControlHandle->MainImageList->Last->Image->Height){
					gtk_spin_button_set_value(GTK_SPIN_BUTTON (MainControlHandle->XCoordObject->Widget), XClicked); 
					gtk_spin_button_set_value(GTK_SPIN_BUTTON (MainControlHandle->YCoordObject->Widget), YClicked); 
				}
			}
			MainControlHandle->State = Normal;
			SetCursorImageBox(MainControlHandle);
			//printf("Translated coordinates are x = %d, y = %d\n", XClicked, YClicked);
		}

/*======================================================================*/	
	} else if (strcmp(ClickedObject->Name,"About") == 0){
		drawAboutWindow(MainControlHandle->MainViewHandle);
		
/*======================================================================*/	
	} else if (strcmp(ClickedObject->Name,"UserManual") == 0){		
		CurrObject = FindObject(MainControlHandle, "HelpWinMain");
		gtk_widget_show(CurrObject->Widget);
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
    
     utstring_clear(ImageFileName);
    if (gtk_dialog_run (GTK_DIALOG (openFile)) == GTK_RESPONSE_ACCEPT)
    {
        char *filename;        
        filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (openFile));
	 
        utstring_printf(ImageFileName, "%s", filename);
        g_free (filename);
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

int GetOCRParams(ControlHandle * MainControlHandle, FontType * Font, int * FontSize, int *ScanRes, int *IsoAlg, int *UseDict){
	ObjectHandle * CurrObject = FindObject(MainControlHandle, "FontComboBox");
	switch(gtk_combo_box_get_active(GTK_COMBO_BOX(CurrObject->Widget))){
		case 0:
			*Font = CourierNew;
			break;
		case 1:
			*Font = LucidaConsole;
			break;
		default:					
			return 1;
			break;
	}
	CurrObject = FindObject(MainControlHandle, "FontSizeComboBox");
	switch(gtk_combo_box_get_active(GTK_COMBO_BOX(CurrObject->Widget))){
		case 0:
			*FontSize = 10;
			break;
		case 1:
			*FontSize = 12;
			break;
		default:
			return 2;
			break;
	}
	CurrObject = FindObject(MainControlHandle, "ScanResComboBox");
	switch(gtk_combo_box_get_active(GTK_COMBO_BOX(CurrObject->Widget))){
		case 0:
			*ScanRes = 300;
			break;		
		default:
			return 3;
			break;
	}
	CurrObject = FindObject(MainControlHandle, "LazyRadio");
	ObjectHandle * CurrObject2 = FindObject(MainControlHandle, "ActiveRadio");
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(CurrObject->Widget))){
		*IsoAlg = 0;
	} else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(CurrObject2->Widget))) {
		*IsoAlg = 1;
	} else return 4;
	
	CurrObject = FindObject(MainControlHandle, "DictionaryCombo");
	switch(gtk_combo_box_get_active(GTK_COMBO_BOX(CurrObject->Widget))){
		case 0:
			*UseDict = 1;
			break;
		case 1:
			*UseDict = 0;
			break;
		default:
			return 5;
			break;
	}
	return 0;
}

int GetCropCoordinate(ControlHandle * MainControlHandle, int * x1, int * y1, int * x2, int * y2){
	if (!MainControlHandle->MainImageList->Last) return 5;
	
	IMAGE * CurrImage = MainControlHandle->MainImageList->Last->Image;
	
	ObjectHandle * CurrObject = FindObject(MainControlHandle, "CropSpin");
	*x1 = floor(gtk_spin_button_get_value(GTK_SPIN_BUTTON(CurrObject->Widget)));
	if (*x1 < 0 || *x1 >= CurrImage->Width) return 1;
	CurrObject = FindObject(MainControlHandle, "CropSpin2");
	*y1 = floor(gtk_spin_button_get_value(GTK_SPIN_BUTTON(CurrObject->Widget)));
	if (*y1 < 0 || *y1 >= CurrImage->Height) return 2;
	CurrObject = FindObject(MainControlHandle, "CropSpin3");
	*x2 = floor(gtk_spin_button_get_value(GTK_SPIN_BUTTON(CurrObject->Widget)));
	if (*x2 < 0 || *x2 >= CurrImage->Width) return 3;
	CurrObject = FindObject(MainControlHandle, "CropSpin4");
	*y2 = floor(gtk_spin_button_get_value(GTK_SPIN_BUTTON(CurrObject->Widget)));
	if (*y2 < 0 || *y2 >= CurrImage->Height) return 4;
	return 0;
}

int GetStainRemovalParams(ControlHandle * MainControlHandle, int * var1, int * var2, int * b_thres, int * dark_limit){
	ObjectHandle * CurrObject = FindObject(MainControlHandle, "Var1Spinner");
	*var1 = floor(gtk_spin_button_get_value(GTK_SPIN_BUTTON(CurrObject->Widget)));
	if (*var1 < 0 || *var1 > 255) return 1;
	CurrObject = FindObject(MainControlHandle, "Var2Spinner");
	*var2 = floor(gtk_spin_button_get_value(GTK_SPIN_BUTTON(CurrObject->Widget)));
	if (*var2 < 0 || *var2 > 255) return 2;
	CurrObject = FindObject(MainControlHandle, "BrightSpinner");
	*b_thres = floor(gtk_spin_button_get_value(GTK_SPIN_BUTTON(CurrObject->Widget)));
	if (*b_thres < 0 || *b_thres > 255) return 3;
	CurrObject = FindObject(MainControlHandle, "DarkenSpinner");
	*dark_limit = floor(gtk_spin_button_get_value(GTK_SPIN_BUTTON(CurrObject->Widget)));
	if (*dark_limit < 0 || *dark_limit > 255) return 4;
	return 0;
}

int GetColorFilterParams(ControlHandle * MainControlHandle, int * x, int * y, int *x1, int *y1, int *x2, int *y2, int * new_value, int * thres_value){
	if (!MainControlHandle->MainImageList->Last) return 9;
	
	IMAGE * CurrImage = MainControlHandle->MainImageList->Last->Image;
	
	ObjectHandle * CurrObject = FindObject(MainControlHandle, "Xspinner");
	*x = floor(gtk_spin_button_get_value(GTK_SPIN_BUTTON(CurrObject->Widget)));
	if (*x < 0 || *x >= CurrImage->Width) return 1;
	
	CurrObject = FindObject(MainControlHandle, "Yspinner");
	*y = floor(gtk_spin_button_get_value(GTK_SPIN_BUTTON(CurrObject->Widget)));
	if (*y < 0 || *y >= CurrImage->Height) return 2;
	
	CurrObject = FindObject(MainControlHandle, "X1spinner");
	*x1 = floor(gtk_spin_button_get_value(GTK_SPIN_BUTTON(CurrObject->Widget)));
	if (*x1 < 0 || *x1 >= CurrImage->Width) return 3;
	
	CurrObject = FindObject(MainControlHandle, "Y1spinner");
	*y1 = floor(gtk_spin_button_get_value(GTK_SPIN_BUTTON(CurrObject->Widget)));
	if (*y1 < 0 || *y1 >= CurrImage->Height) return 4;
	
	CurrObject = FindObject(MainControlHandle, "X2spinner");
	*x2 = floor(gtk_spin_button_get_value(GTK_SPIN_BUTTON(CurrObject->Widget)));
	if (*x2 < 0 || *x2 >= CurrImage->Width) return 5;
	
	CurrObject = FindObject(MainControlHandle, "Y2spinner");
	*y2 = floor(gtk_spin_button_get_value(GTK_SPIN_BUTTON(CurrObject->Widget)));
	if (*y2 < 0 || *y2 >= CurrImage->Height) return 6;
	
	
	CurrObject = FindObject(MainControlHandle, "NewPixSpinner");
	*new_value = floor(gtk_spin_button_get_value(GTK_SPIN_BUTTON(CurrObject->Widget)));
	if (*new_value < 0 || *new_value > 255) return 7;
	CurrObject = FindObject(MainControlHandle, "ThresSpinner");
	*thres_value = floor(gtk_spin_button_get_value(GTK_SPIN_BUTTON(CurrObject->Widget)));
	if (*thres_value < 0 || *thres_value > 255) return 8;
	
	return 0;
}

void show_error(const char * ErrorMessage)
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

void show_compilation_msg(ControlHandle * MainControlHandle, const char * CompileMessage)
{
	/*show the widget*/
	ObjectHandle * CurrObject = FindObject(MainControlHandle, "CompileWinMain");
	gtk_widget_show(CurrObject->Widget);
	
	/*clear the text*/
	CurrObject = FindObject(MainControlHandle, "CompileTextArea");
	GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(CurrObject->Widget));;
	GtkTextIter iter1, iter2;
	gtk_text_buffer_get_start_iter(buffer, &iter1);
	gtk_text_buffer_get_end_iter(buffer, &iter2);
	gtk_text_buffer_delete(buffer, &iter1, &iter2);
	
	/*set the text*/
	gtk_text_buffer_get_end_iter(buffer, &iter1);
	gtk_text_buffer_insert(buffer, &iter1, CompileMessage, -1);
	
}

IMAGE * ResizeFitScreen(ControlHandle * MainControlHandle, IMAGE * original_image){
	GtkAllocation allocation;
	ObjectHandle * CurrObject;
	int new_width, new_height;
	CurrObject = FindObject(MainControlHandle, "ImageScrollWindow");
	gtk_widget_get_allocation(CurrObject->Widget, &allocation);
	if (original_image->Width >= original_image->Height){
		new_width = allocation.height * original_image->Width / original_image->Height; 
		new_height = allocation.height;
	} else {
		new_height = allocation.width * original_image->Height / original_image->Width; 
		new_width = allocation.width;
	}
	MainControlHandle->DisplayWidth = new_width;
	MainControlHandle->DisplayHeight = new_height;
	MainControlHandle->OriginalWidth = original_image->Width;
	MainControlHandle->OriginalHeight = original_image->Height;
	return Resize(original_image, new_width, new_height);
}