/******************************************************************/
/* DrawFunctions.c                                                */
/******************************************************************/

#include "DrawFunctions.h"

GtkWidget *drawMain(ViewHandle * MainViewHandle){
 ObjectHandle * NewObject;
 
 GtkWidget *window  = gtk_window_new(GTK_WINDOW_TOPLEVEL);
 NewObject = ObjectHandle_Initialize("MainWindow", window);
 HASH_ADD(HashByName, MainViewHandle->ObjectListByName, Name, sizeof(char) * MAX_HASH_KEY_LENGTH, NewObject);
 HASH_ADD(HashByWidget,MainViewHandle->ObjectListByWidget,Widget,sizeof(GtkWidget *),NewObject);
    
 gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
 gtk_window_set_default_size(GTK_WINDOW(window), 1000, 450);
 gtk_window_set_title(GTK_WINDOW(window), "OCR Program");
      
 g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

 return window;
}

GtkWidget *drawMenuBar(ViewHandle * MainViewHandle){

  ObjectHandle * NewObject;
  GtkWidget *menubar = gtk_menu_bar_new();
  GtkWidget *separator = gtk_separator_menu_item_new();
/*****************************************************************************************************************/
/*RYAN: here is an example of how you can add a new Widget to the data structure*/
/*The onlythinng you need to change is "NewName", NewGtkWidget*"*/
  AddWidgetToViewHandle(MainViewHandle, "MenuBar", menubar);
  AddWidgetToViewHandle(MainViewHandle, "Separator", separator);
/*****************************************************************************************************************/  
  
  /* file options for menubar */
  GtkWidget  *filemenu = gtk_menu_new(),
    *file = gtk_menu_item_new_with_label("File"),
    *open = gtk_menu_item_new_with_label("Open"),
    *save = gtk_menu_item_new_with_label("Save"),
    *quit = gtk_menu_item_new_with_label("Quit");

  AddWidgetToViewHandle(MainViewHandle, "FileMenu", file);
  AddWidgetToViewHandle(MainViewHandle, "OpenFile", open);
  AddWidgetToViewHandle(MainViewHandle, "SaveFile", save);
  AddWidgetToViewHandle(MainViewHandle, "QuitProgram", quit);  

  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file);
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), filemenu);
  gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), open);
  gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), save);
  gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), separator);
  gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), quit);

  /* preprocessor options for menubar */
  GtkWidget *preProcMenu = gtk_menu_new(),
    *preProc       = gtk_menu_item_new_with_label("Preprocessing"),
    *convert       = gtk_menu_item_new_with_label("Convert to Black and White"),
    *removeStain   = gtk_menu_item_new_with_label("Stain Removal"),
    *removeWrinkle = gtk_menu_item_new_with_label("Wrinkle Removal"),
    *rotate        = gtk_menu_item_new_with_label("Rotate  (Level Image)"),
    *lineBound     = gtk_menu_item_new_with_label("Line Boundaries"),
    *crop          = gtk_menu_item_new_with_label("Crop  (Select OCR Region)");

  AddWidgetToViewHandle(MainViewHandle, "PreProcessMenu", preProcMenu);
  AddWidgetToViewHandle(MainViewHandle, "Preprocessing", preProc);
  AddWidgetToViewHandle(MainViewHandle, "ConvertBW", convert);
  AddWidgetToViewHandle(MainViewHandle, "RemoveStain", removeStain);
  AddWidgetToViewHandle(MainViewHandle, "RemoveWrinkle", removeWrinkle);
  AddWidgetToViewHandle(MainViewHandle, "Rotate", rotate);
  AddWidgetToViewHandle(MainViewHandle, "LineBoundary", lineBound);
  AddWidgetToViewHandle(MainViewHandle, "Crop", crop);

  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), preProc);
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(preProc), preProcMenu);
  gtk_menu_shell_append(GTK_MENU_SHELL(preProcMenu), convert);
  gtk_menu_shell_append(GTK_MENU_SHELL(preProcMenu), removeStain);
  gtk_menu_shell_append(GTK_MENU_SHELL(preProcMenu), removeWrinkle);
  gtk_menu_shell_append(GTK_MENU_SHELL(preProcMenu), rotate);
  gtk_menu_shell_append(GTK_MENU_SHELL(preProcMenu), lineBound);
  gtk_menu_shell_append(GTK_MENU_SHELL(preProcMenu), crop);

  /* ocr options for menubar */
  GtkWidget *ocrMenu = gtk_menu_new(),
    *ocr        = gtk_menu_item_new_with_label("OCR"),    
    *performOCR =  gtk_menu_item_new_with_label("Perform OCR");

  AddWidgetToViewHandle(MainViewHandle, "OCRMenu", ocrMenu);
  AddWidgetToViewHandle(MainViewHandle, "OCR", ocr);
  AddWidgetToViewHandle(MainViewHandle, "PerformOCR", performOCR);

  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), ocr);
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(ocr), ocrMenu);
  gtk_menu_shell_append(GTK_MENU_SHELL(ocrMenu), performOCR);

  /* postprocessing options for menubar */
  GtkWidget *postProcMenu = gtk_menu_new(),
    *postProc   = gtk_menu_item_new_with_label("Postprocessing"),
    *edit       = gtk_menu_item_new_with_label("Edit OCR Text Output"),
    *dictionary =  gtk_menu_item_new_with_label("Dictionary Settings");
 
  AddWidgetToViewHandle(MainViewHandle, "PostProcMenu", postProcMenu);
  AddWidgetToViewHandle(MainViewHandle, "Postprocessing", postProc);
  AddWidgetToViewHandle(MainViewHandle, "EditText", edit);
  AddWidgetToViewHandle(MainViewHandle, "Dictionary", dictionary);

  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), postProc);
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(postProc), postProcMenu);
  gtk_menu_shell_append(GTK_MENU_SHELL(postProcMenu), edit);
  gtk_menu_shell_append(GTK_MENU_SHELL(postProcMenu), dictionary);

  g_signal_connect(G_OBJECT(quit), "activate", G_CALLBACK(gtk_main_quit), NULL);   
  g_signal_connect(G_OBJECT(open), "activate", G_CALLBACK(CatchEvent), MainViewHandle);
  g_signal_connect(G_OBJECT(save), "activate", G_CALLBACK(CatchEvent), MainViewHandle);

  g_signal_connect(G_OBJECT(preProc), "activate", G_CALLBACK(CatchEvent), MainViewHandle);
  g_signal_connect(G_OBJECT(convert), "activate", G_CALLBACK(CatchEvent), MainViewHandle);
  g_signal_connect(G_OBJECT(removeStain), "activate", G_CALLBACK(CatchEvent), MainViewHandle);
  g_signal_connect(G_OBJECT(removeWrinkle), "activate", G_CALLBACK(CatchEvent), MainViewHandle);
  g_signal_connect(G_OBJECT(rotate), "activate", G_CALLBACK(CatchEvent), MainViewHandle);
  g_signal_connect(G_OBJECT(lineBound), "activate", G_CALLBACK(CatchEvent), MainViewHandle);
  g_signal_connect(G_OBJECT(crop), "activate", G_CALLBACK(CatchEvent), MainViewHandle);  

  g_signal_connect(G_OBJECT(ocr), "activate", G_CALLBACK(CatchEvent), MainViewHandle);
  g_signal_connect(G_OBJECT(performOCR), "activate", G_CALLBACK(CatchEvent), MainViewHandle);

  g_signal_connect(G_OBJECT(postProc), "activate", G_CALLBACK(CatchEvent), MainViewHandle);
  g_signal_connect(G_OBJECT(edit), "activate", G_CALLBACK(CatchEvent), MainViewHandle);
  g_signal_connect(G_OBJECT(dictionary), "activate", G_CALLBACK(CatchEvent), MainViewHandle);

  return menubar;
}

GtkWidget *drawImageWindow(ViewHandle *MainViewHandle){

  GtkWidget *scrollWinImage;
  scrollWinImage = gtk_scrolled_window_new(NULL, NULL);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollWinImage),
				 GTK_POLICY_ALWAYS,
				 GTK_POLICY_ALWAYS);
  AddWidgetToViewHandle(MainViewHandle, "ImageScrollWindow", scrollWinImage);

  return scrollWinImage;
}

GtkWidget *drawTextWindow(ViewHandle *MainViewHandle){

  GtkWidget *scrollWinText;
  scrollWinText = gtk_scrolled_window_new(NULL, NULL);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollWinText),
				 GTK_POLICY_ALWAYS,
				 GTK_POLICY_ALWAYS);
  AddWidgetToViewHandle(MainViewHandle, "TextScrollWindow", scrollWinText);

  return scrollWinText;
}

GtkWidget *drawRotateWindow(ViewHandle * MainViewHandle){

 GtkWidget *rotateWin;    
 GtkWidget *vboxMain;
 GtkWidget *vbox;
 GtkWidget *vbox2;
 GtkWidget *hbox;    
 GtkWidget *frame;
 GtkWidget *spinner;
 GtkWidget *rotateButton;
 GtkWidget *closeButton;
 GtkWidget *label;
 GtkAdjustment *adj;
  
 rotateWin = gtk_window_new (GTK_WINDOW_TOPLEVEL);
 AddWidgetToViewHandle(MainViewHandle, "RotateWindow", rotateWin);
 gtk_window_set_default_size(GTK_WINDOW(rotateWin), 230, 100);
 g_signal_connect (rotateWin, "destroy",
		   G_CALLBACK (gtk_main_quit),
		   NULL);

 gtk_window_set_title (GTK_WINDOW (rotateWin), "Rotate Image");
 
 vboxMain = gtk_vbox_new (FALSE, 5);
 AddWidgetToViewHandle(MainViewHandle, "RotateVbox1", vboxMain);
 gtk_container_set_border_width (GTK_CONTAINER (vboxMain), 10);
 gtk_container_add (GTK_CONTAINER (rotateWin), vboxMain);
 
 frame = gtk_frame_new ("Clockwise Rotation");
 AddWidgetToViewHandle(MainViewHandle, "RotateFrame", frame);
 gtk_box_pack_start (GTK_BOX (vboxMain), frame, TRUE, TRUE, 0);
 
 vbox = gtk_vbox_new (FALSE, 0);
 AddWidgetToViewHandle(MainViewHandle, "RotateVbox2", vbox);
 gtk_container_set_border_width (GTK_CONTAINER (vbox), 15);
 gtk_container_add (GTK_CONTAINER (frame), vbox);
 
 hbox = gtk_hbox_new (FALSE, 30);
 AddWidgetToViewHandle(MainViewHandle, "RotateHbox", hbox);
 gtk_box_pack_start (GTK_BOX (vbox), hbox, TRUE, TRUE, 5);
 
 vbox2 = gtk_vbox_new (FALSE, 0);
 AddWidgetToViewHandle(MainViewHandle, "RotateVbox3", vbox2);
 gtk_box_pack_start (GTK_BOX (hbox), vbox2, FALSE, TRUE, 5);
 
 label = gtk_label_new ("Degrees :");
 AddWidgetToViewHandle(MainViewHandle, "RotateLabel", label);
 gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);
 gtk_box_pack_start (GTK_BOX (vbox2), label, FALSE, TRUE, 0);
 
 adj = (GtkAdjustment *) gtk_adjustment_new (1.0, 1.0, 360.0, 1.0, 5.0, 0.0);

 spinner = gtk_spin_button_new (adj, 0, 0);
 AddWidgetToViewHandle(MainViewHandle, "RotateSpinner", spinner);
 gtk_spin_button_set_wrap (GTK_SPIN_BUTTON (spinner), TRUE);
 gtk_box_pack_start (GTK_BOX (vbox2), spinner, FALSE, TRUE, 0);
 
 vbox2 = gtk_vbox_new (FALSE, 0);
 gtk_box_pack_start (GTK_BOX (hbox), vbox2, FALSE, TRUE, 5);
 
 rotateButton = gtk_button_new_with_label ("Rotate");
 AddWidgetToViewHandle(MainViewHandle, "RotateButton", rotateButton);
 /* g_signal_connect(rotateButton, "clicked", */
 /* 		  G_CALLBACK (grab_int_value),    */
 /* 		  spinner); */
 g_signal_connect(G_OBJECT(rotateButton), "clicked", G_CALLBACK(CatchEvent), MainViewHandle);

 gtk_box_pack_start (GTK_BOX (vbox2), rotateButton, TRUE, TRUE, 5);
 
 hbox = gtk_hbox_new (FALSE, 0);
 gtk_box_pack_start (GTK_BOX (vboxMain), hbox, FALSE, TRUE, 0);
 
 closeButton = gtk_button_new_with_label ("Close");
 AddWidgetToViewHandle(MainViewHandle, "RotCloseButton", closeButton);
 g_signal_connect_swapped (closeButton, "clicked",
			   G_CALLBACK (gtk_widget_destroy),
			   rotateWin);
 gtk_box_pack_start (GTK_BOX (hbox), closeButton, TRUE, TRUE, 5);

 gtk_widget_show_all(rotateWin);

 return rotateWin;
}

GtkWidget *drawCropWindow(ViewHandle * MainViewHandle){

 GtkWidget *cropWin;
 GtkWidget *vboxMain, *vbox, *vbox2, *vbox3, *vbox4;
 GtkWidget *hbox, *hbox2;
 GtkWidget *spinner, *spinner2, *spinner3, *spinner4;
 GtkWidget *cropButton, *closeButton;
 GtkWidget *frame;
 GtkWidget *label;
 GtkAdjustment *adj;
  
 cropWin = gtk_window_new (GTK_WINDOW_TOPLEVEL);
 AddWidgetToViewHandle(MainViewHandle, "CropWindow", cropWin);
 gtk_window_set_default_size(GTK_WINDOW(cropWin), 230, 100);
 g_signal_connect (cropWin, "destroy",
 		   G_CALLBACK (gtk_main_quit),
 		   NULL);

 gtk_window_set_title (GTK_WINDOW (cropWin), "Crop Image");
 
 vboxMain = gtk_vbox_new (FALSE, 5);
 AddWidgetToViewHandle(MainViewHandle, "CropVboxMain", vboxMain);
 gtk_container_set_border_width (GTK_CONTAINER (vboxMain), 10);
 gtk_container_add (GTK_CONTAINER (cropWin), vboxMain);
 
 frame = gtk_frame_new (NULL);
 AddWidgetToViewHandle(MainViewHandle, "CropFrame", frame);
 gtk_box_pack_start (GTK_BOX (vboxMain), frame, TRUE, TRUE, 0);
 
 vbox = gtk_vbox_new (FALSE, 0);
 AddWidgetToViewHandle(MainViewHandle, "CropVbox", vbox);
 gtk_container_set_border_width (GTK_CONTAINER (vbox), 15);
 gtk_container_add (GTK_CONTAINER (frame), vbox);

 /* horizontal frame */
 frame = gtk_frame_new ("Horizontal");
 gtk_box_pack_start (GTK_BOX (vbox), frame, TRUE, TRUE, 0);
 
 hbox = gtk_hbox_new (FALSE, 30);
 AddWidgetToViewHandle(MainViewHandle, "CropHbox", hbox);
 gtk_container_set_border_width (GTK_CONTAINER (hbox), 15);
 gtk_container_add (GTK_CONTAINER (frame), hbox);

 label = gtk_label_new ("Begin :");
 AddWidgetToViewHandle(MainViewHandle, "Croplabel", label);
 gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);
 
 adj = (GtkAdjustment *) gtk_adjustment_new (0.0, 0.0, 1000.0, 1.0, 5.0, 0.0);

 spinner = gtk_spin_button_new (adj, 0, 0);
 AddWidgetToViewHandle(MainViewHandle, "CropSpin", spinner);
 gtk_spin_button_set_wrap (GTK_SPIN_BUTTON (spinner), TRUE);

 vbox2 = gtk_vbox_new (FALSE, 0);
 AddWidgetToViewHandle(MainViewHandle, "CropVbox2", vbox2);
 gtk_box_pack_start (GTK_BOX (hbox), vbox2, TRUE, TRUE, 0);
 gtk_box_pack_start (GTK_BOX (vbox2), label, TRUE, TRUE, 0);
 gtk_box_pack_start (GTK_BOX (vbox2), spinner, TRUE, TRUE, 0);

 label = gtk_label_new ("End :");
 gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);
 
 adj = (GtkAdjustment *) gtk_adjustment_new (0.0, 0.0, 1000.0, 1.0, 5.0, 0.0);

 spinner2 = gtk_spin_button_new (adj, 0, 0);
 AddWidgetToViewHandle(MainViewHandle, "CropSpin2", spinner2);
 gtk_spin_button_set_wrap (GTK_SPIN_BUTTON (spinner2), TRUE);

 vbox3 = gtk_vbox_new (FALSE, 0);
 AddWidgetToViewHandle(MainViewHandle, "CropVbox3", vbox3);
 gtk_box_pack_start (GTK_BOX (hbox), vbox3, TRUE, TRUE, 0);
 gtk_box_pack_start (GTK_BOX (vbox3), label, TRUE, TRUE, 0);
 gtk_box_pack_start (GTK_BOX (vbox3), spinner2, TRUE, TRUE, 0);

 /* vertical frame */
 frame = gtk_frame_new ("Vertical");
 gtk_box_pack_start (GTK_BOX (vbox), frame, TRUE, TRUE, 0);
 
 hbox2 = gtk_hbox_new (FALSE, 30);
 AddWidgetToViewHandle(MainViewHandle, "CropHbox2", hbox2);
 gtk_container_set_border_width (GTK_CONTAINER (hbox2), 15);
 gtk_container_add (GTK_CONTAINER (frame), hbox2);

 label = gtk_label_new ("Begin :");
 gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);
 
 adj = (GtkAdjustment *) gtk_adjustment_new (0.0, 0.0, 1000.0, 1.0, 5.0, 0.0);

 spinner3 = gtk_spin_button_new (adj, 0, 0);
 AddWidgetToViewHandle(MainViewHandle, "CropSpin3", spinner3);
 gtk_spin_button_set_wrap (GTK_SPIN_BUTTON (spinner3), TRUE);

 vbox3 = gtk_vbox_new (FALSE, 0);
 gtk_box_pack_start (GTK_BOX (hbox2), vbox3, TRUE, TRUE, 0);
 gtk_box_pack_start (GTK_BOX (vbox3), label, TRUE, TRUE, 0);
 gtk_box_pack_start (GTK_BOX (vbox3), spinner3, TRUE, TRUE, 0);

 label = gtk_label_new ("End :");
 gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);
 
 adj = (GtkAdjustment *) gtk_adjustment_new (0.0, 0.0, 1000.0, 1.0, 5.0, 0.0);

 spinner4 = gtk_spin_button_new (adj, 0, 0);
 AddWidgetToViewHandle(MainViewHandle, "CropSpin4", spinner4);
 gtk_spin_button_set_wrap (GTK_SPIN_BUTTON (spinner4), TRUE);

 vbox4 = gtk_vbox_new (FALSE, 0);
 AddWidgetToViewHandle(MainViewHandle, "CropVbox4", vbox4);
 gtk_box_pack_start (GTK_BOX (hbox2), vbox4, TRUE, TRUE, 0);
 gtk_box_pack_start (GTK_BOX (vbox4), label, TRUE, TRUE, 0);
 gtk_box_pack_start (GTK_BOX (vbox4), spinner4, TRUE, TRUE, 0);

 /* crop button */
 cropButton = gtk_button_new_with_label ("Crop");
 AddWidgetToViewHandle(MainViewHandle, "CropButton", cropButton);
 /* g_signal_connect(cropButton, "clicked", */
 /* 		  G_CALLBACK (gtk_widget_destroy), /\* temporary, need to fix *\/ */
 /* 		  spinner); */
 g_signal_connect(G_OBJECT(cropButton), "clicked", G_CALLBACK(CatchEvent), MainViewHandle);
 gtk_box_pack_start (GTK_BOX (vbox), cropButton, TRUE, TRUE, 5);

 /* close button */
 closeButton = gtk_button_new_with_label ("Close");
 AddWidgetToViewHandle(MainViewHandle, "CropCloseButton", closeButton);
 g_signal_connect_swapped (closeButton, "clicked",
 			   G_CALLBACK (gtk_widget_destroy),
 			   cropWin);
 gtk_box_pack_start (GTK_BOX (vboxMain), closeButton, TRUE, TRUE, 5);

 gtk_widget_show_all(cropWin); 

 return cropWin;
}

GtkWidget *drawColorFilterWindow(ViewHandle * MainViewHandle){

 GtkWidget *filterWin;
 GtkWidget *vboxMain, *vbox, *vbox2, *vbox3, *hbox;
 GtkWidget *frame;
 GtkWidget *radio1, *radio2;
 GtkWidget *spinner;
 GtkWidget *filterButton, *closeButton;
 GtkWidget *label;
 GtkAdjustment *adj;
  
 filterWin = gtk_window_new (GTK_WINDOW_TOPLEVEL);
 AddWidgetToViewHandle(MainViewHandle, "ColorFilterWindow", filterWin);
 gtk_window_set_default_size(GTK_WINDOW(filterWin), 230, 100);
 g_signal_connect (filterWin, "destroy",
 		   G_CALLBACK (gtk_main_quit),
 		   NULL);

 gtk_window_set_title (GTK_WINDOW (filterWin), "Color Filter");
 
 vboxMain = gtk_vbox_new (FALSE, 5);
 AddWidgetToViewHandle(MainViewHandle, "vboxMain", vboxMain);
 gtk_container_set_border_width (GTK_CONTAINER (vboxMain), 10);
 gtk_container_add (GTK_CONTAINER (filterWin), vboxMain);
 
 frame = gtk_frame_new (NULL);
 AddWidgetToViewHandle(MainViewHandle, "frame", frame);
 gtk_box_pack_start (GTK_BOX (vboxMain), frame, TRUE, TRUE, 0);
 
 vbox = gtk_vbox_new (FALSE, 0);
 AddWidgetToViewHandle(MainViewHandle, "vbox", vbox);
 gtk_container_set_border_width (GTK_CONTAINER (vbox), 15);
 gtk_container_add (GTK_CONTAINER (frame), vbox);

 /* xy frame */
 frame = gtk_frame_new (NULL);
 gtk_box_pack_start (GTK_BOX (vbox), frame, TRUE, TRUE, 0);

 vbox2 = gtk_vbox_new (FALSE, 0);
 AddWidgetToViewHandle(MainViewHandle, "vbox2", vbox2);
 gtk_container_set_border_width (GTK_CONTAINER (vbox2), 15);
 gtk_container_add (GTK_CONTAINER (frame), vbox2);

 hbox = gtk_hbox_new (FALSE, 0);
 AddWidgetToViewHandle(MainViewHandle, "hbox", hbox);
 gtk_box_pack_start (GTK_BOX (vbox2), hbox, TRUE, TRUE, 0);

 label = gtk_label_new ("X:    ");
 AddWidgetToViewHandle(MainViewHandle, "label", label);
 gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);

 adj = (GtkAdjustment *) gtk_adjustment_new (0.0, 0.0, 1000.0, 1.0, 5.0, 0.0);
 spinner = gtk_spin_button_new (adj, 0, 0);
 AddWidgetToViewHandle(MainViewHandle, "spinner", spinner);
 gtk_spin_button_set_wrap (GTK_SPIN_BUTTON (spinner), TRUE);

 gtk_box_pack_start (GTK_BOX (hbox), label, TRUE, TRUE, 0);
 gtk_box_pack_start (GTK_BOX (hbox), spinner, FALSE, TRUE, 0);
 label = gtk_label_new ("           ");
 gtk_box_pack_start (GTK_BOX (hbox), label, TRUE, TRUE, 0);

 label = gtk_label_new ("Y:    ");
 gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);

 adj = (GtkAdjustment *) gtk_adjustment_new (0.0, 0.0, 1000.0, 1.0, 5.0, 0.0);
 spinner = gtk_spin_button_new (adj, 0, 0);
 gtk_spin_button_set_wrap (GTK_SPIN_BUTTON (spinner), TRUE);

 gtk_box_pack_start (GTK_BOX (hbox), label, TRUE, TRUE, 0);
 gtk_box_pack_start (GTK_BOX (hbox), spinner, FALSE, TRUE, 0);

 hbox = gtk_hbox_new (FALSE, 0);
 gtk_box_pack_start (GTK_BOX (vbox2), hbox, TRUE, TRUE, 0);

 label = gtk_label_new ("X1:  ");
 gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);

 adj = (GtkAdjustment *) gtk_adjustment_new (0.0, 0.0, 1000.0, 1.0, 5.0, 0.0);
 spinner = gtk_spin_button_new (adj, 0, 0);
 gtk_spin_button_set_wrap (GTK_SPIN_BUTTON (spinner), TRUE);

 gtk_box_pack_start (GTK_BOX (hbox), label, TRUE, TRUE, 0);
 gtk_box_pack_start (GTK_BOX (hbox), spinner, FALSE, TRUE, 0);

 label = gtk_label_new ("           ");
 gtk_box_pack_start (GTK_BOX (hbox), label, TRUE, TRUE, 0);

 label = gtk_label_new ("Y1:  ");
 gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);

 adj = (GtkAdjustment *) gtk_adjustment_new (0.0, 0.0, 1000.0, 1.0, 5.0, 0.0);
 spinner = gtk_spin_button_new (adj, 0, 0);
 gtk_spin_button_set_wrap (GTK_SPIN_BUTTON (spinner), TRUE);

 gtk_box_pack_start (GTK_BOX (hbox), label, TRUE, TRUE, 0);
 gtk_box_pack_start (GTK_BOX (hbox), spinner, FALSE, TRUE, 0);

 hbox = gtk_hbox_new (FALSE, 0);
 gtk_box_pack_start (GTK_BOX (vbox2), hbox, TRUE, TRUE, 0);

 label = gtk_label_new ("X2:  ");
 gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);

 adj = (GtkAdjustment *) gtk_adjustment_new (0.0, 0.0, 1000.0, 1.0, 5.0, 0.0);
 spinner = gtk_spin_button_new (adj, 0, 0);
 gtk_spin_button_set_wrap (GTK_SPIN_BUTTON (spinner), TRUE);

 gtk_box_pack_start (GTK_BOX (hbox), label, TRUE, TRUE, 0);
 gtk_box_pack_start (GTK_BOX (hbox), spinner, FALSE, TRUE, 0);

 label = gtk_label_new ("           ");
 gtk_box_pack_start (GTK_BOX (hbox), label, TRUE, TRUE, 0);

 label = gtk_label_new ("Y2:  ");
 gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);

 adj = (GtkAdjustment *) gtk_adjustment_new (0.0, 0.0, 1000.0, 1.0, 5.0, 0.0);
 spinner = gtk_spin_button_new (adj, 0, 0);
 gtk_spin_button_set_wrap (GTK_SPIN_BUTTON (spinner), TRUE);

 gtk_box_pack_start (GTK_BOX (hbox), label, TRUE, TRUE, 0);
 gtk_box_pack_start (GTK_BOX (hbox), spinner, FALSE, TRUE, 0);

 /* radio frame */
 frame = gtk_frame_new (NULL);
 gtk_box_pack_start (GTK_BOX (vbox), frame, TRUE, TRUE, 0);

 vbox3 = gtk_vbox_new (FALSE, 0);
 AddWidgetToViewHandle(MainViewHandle, "vbox3", vbox3);
 gtk_container_set_border_width (GTK_CONTAINER (vbox3), 15);
 gtk_container_add (GTK_CONTAINER (frame), vbox3);

 radio1 = gtk_radio_button_new_with_label(NULL, "Make Pixel Black");
 AddWidgetToViewHandle(MainViewHandle, "Radio1", radio1);
 g_signal_connect(G_OBJECT(radio1), "clicked", G_CALLBACK(CatchEvent), MainViewHandle);
 radio2 = gtk_radio_button_new_with_label_from_widget (GTK_RADIO_BUTTON (radio1),
						       "Make Pixel White");
 AddWidgetToViewHandle(MainViewHandle, "Radio2", radio2);
 g_signal_connect(G_OBJECT(radio2), "clicked", G_CALLBACK(CatchEvent), MainViewHandle);
 
 gtk_box_pack_start (GTK_BOX (vbox3), radio1, TRUE, TRUE, 0);
 gtk_box_pack_start (GTK_BOX (vbox3), radio2, FALSE, TRUE, 0);

 /* color filter button */
 filterButton = gtk_button_new_with_label ("Color Filter");
 AddWidgetToViewHandle(MainViewHandle, "FilterButton", filterButton);
 /* g_signal_connect(filterButton, "clicked", */
 /* 		  G_CALLBACK (gtk_widget_destroy), */
 /* 		  spinner); */
 g_signal_connect(G_OBJECT(filterButton), "clicked", G_CALLBACK(CatchEvent), MainViewHandle);
 gtk_box_pack_start (GTK_BOX (vbox), filterButton, TRUE, TRUE, 5);

 /* close button */
 closeButton = gtk_button_new_with_label ("Close");
 AddWidgetToViewHandle(MainViewHandle, "CloseButton", closeButton);
 g_signal_connect_swapped (closeButton, "clicked",
 			   G_CALLBACK (gtk_widget_destroy),
 			   filterWin);
 gtk_box_pack_start (GTK_BOX (vboxMain), closeButton, TRUE, TRUE, 5);

 gtk_widget_show_all(filterWin); 

 return filterWin;
}

GtkWidget *drawOCRWindow(ViewHandle * MainViewHandle){

 GtkWidget *ocrWin;
 GtkWidget *vboxMain, *vbox, *vbox2;
 GtkWidget *hbox, *hbox2;
 GtkWidget *frame;
 GtkWidget *combo;
 GtkWidget *ocrButton, *closeButton;
 GtkWidget *label;

 ocrWin = gtk_window_new (GTK_WINDOW_TOPLEVEL);
 AddWidgetToViewHandle(MainViewHandle, "OCRWindow", ocrWin);
 gtk_window_set_default_size(GTK_WINDOW(ocrWin), 230, 100);
 g_signal_connect (ocrWin, "destroy",
 		   G_CALLBACK (gtk_main_quit),
 		   NULL);
 gtk_window_set_title (GTK_WINDOW (ocrWin), "OCR");
 
 vboxMain = gtk_vbox_new (FALSE, 5);
 AddWidgetToViewHandle(MainViewHandle, "vboxMain", vboxMain);
 gtk_container_set_border_width (GTK_CONTAINER (vboxMain), 10);
 gtk_container_add (GTK_CONTAINER (ocrWin), vboxMain);
 
 frame = gtk_frame_new(NULL);
 AddWidgetToViewHandle(MainViewHandle, "frame", frame);
 gtk_box_pack_start(GTK_BOX(vboxMain), frame, TRUE, TRUE, 0);

 vbox = gtk_vbox_new (FALSE, 0);
 AddWidgetToViewHandle(MainViewHandle, "vbox", vbox);
 gtk_container_set_border_width (GTK_CONTAINER (vbox), 15);
 gtk_container_add (GTK_CONTAINER (frame), vbox);

 /* fonts frame */
 frame = gtk_frame_new (NULL);
 gtk_box_pack_start (GTK_BOX (vbox), frame, TRUE, TRUE, 0);

 vbox2 = gtk_vbox_new (FALSE, 0);
 AddWidgetToViewHandle(MainViewHandle, "vbox2", vbox2);
 gtk_container_set_border_width (GTK_CONTAINER (vbox2), 15);
 gtk_container_add (GTK_CONTAINER (frame), vbox2);

 /* Font */
 hbox = gtk_hbox_new (FALSE, 0);
 AddWidgetToViewHandle(MainViewHandle, "hbox", hbox);
 gtk_box_pack_start (GTK_BOX (vbox2), hbox, TRUE, TRUE, 0);

 label = gtk_label_new ("Font:");
 AddWidgetToViewHandle(MainViewHandle, "label", label);
 gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);
 
 combo = gtk_combo_box_new_text();
 AddWidgetToViewHandle(MainViewHandle, "ComboBox", combo);
 gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "Font 1" );
 gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "Font 2" );
 gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "Font 3" );

 gtk_box_pack_start (GTK_BOX (hbox), label, TRUE, TRUE, 0);
 gtk_box_pack_start (GTK_BOX (hbox), combo, FALSE, TRUE, 0);

 /* Font Size */
 hbox2 = gtk_hbox_new (FALSE, 0);
 AddWidgetToViewHandle(MainViewHandle, "hbox2", hbox2);
 gtk_box_pack_start (GTK_BOX (vbox2), hbox2, TRUE, TRUE, 0);

 label = gtk_label_new ("Font Size:");
 gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);
 
 combo = gtk_combo_box_new_text();

 gtk_widget_set_size_request(GTK_WIDGET(combo), 72, -1);
 gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "1" );
 gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "2" );
 gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "3" );

 gtk_box_pack_start (GTK_BOX (hbox2), label, TRUE, TRUE, 0);
 gtk_box_pack_start (GTK_BOX (hbox2), combo, FALSE, TRUE, 0);

 /* Font Resolution */
 hbox2 = gtk_hbox_new (FALSE, 0);
 gtk_box_pack_start (GTK_BOX (vbox2), hbox2, TRUE, TRUE, 0);

 label = gtk_label_new ("Scan Resolution:  ");
 gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);
 
 combo = gtk_combo_box_new_text();

 gtk_widget_set_size_request(GTK_WIDGET(combo), 72, -1);
 gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "1" );
 gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "2" );
 gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "3" );

 gtk_box_pack_start (GTK_BOX (hbox2), label, TRUE, TRUE, 0);
 gtk_box_pack_start (GTK_BOX (hbox2), combo, FALSE, TRUE, 0);

 /* ocr button */
 ocrButton = gtk_button_new_with_label ("Perform OCR");
 AddWidgetToViewHandle(MainViewHandle, "OCRButton", ocrButton);
 /* g_signal_connect(ocrButton, "clicked", */
 /* 		  G_CALLBACK (gtk_widget_destroy), */
 /* 		  ocrWin); */
 g_signal_connect(G_OBJECT(ocrButton), "clicked", G_CALLBACK(CatchEvent), MainViewHandle);
 gtk_box_pack_start (GTK_BOX (vbox), ocrButton, TRUE, TRUE, 5);

 /* close button */
 closeButton = gtk_button_new_with_label ("Close");
 AddWidgetToViewHandle(MainViewHandle, "CloseButton", closeButton);
 /* g_signal_connect_swapped (closeButton, "clicked", */
 /* 			   G_CALLBACK (gtk_widget_destroy), */
 /* 			   ocrWin); */
 g_signal_connect_swapped (closeButton, "clicked",
 			   G_CALLBACK (gtk_widget_destroy),
 			   ocrWin);
 gtk_box_pack_start (GTK_BOX (vboxMain), closeButton, TRUE, TRUE, 5);

 gtk_widget_show_all(ocrWin); 

 return ocrWin;
}
