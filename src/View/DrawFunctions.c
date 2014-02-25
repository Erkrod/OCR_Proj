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

 AddWidgetToViewHandle(MainViewHandle, "RotateWindow", rotateWin);
 AddWidgetToViewHandle(MainViewHandle, "RotateVbox1", vboxMain);
 AddWidgetToViewHandle(MainViewHandle, "RotateVbox2", vbox);
 AddWidgetToViewHandle(MainViewHandle, "RotateVbox3", vbox2);
 AddWidgetToViewHandle(MainViewHandle, "RotateHbox", hbox);
 AddWidgetToViewHandle(MainViewHandle, "RotateFrame", frame);
 AddWidgetToViewHandle(MainViewHandle, "RotateSpinner", spinner);
 AddWidgetToViewHandle(MainViewHandle, "RotateButton", rotateButton);
 AddWidgetToViewHandle(MainViewHandle, "RotCloseButton", closeButton);
 AddWidgetToViewHandle(MainViewHandle, "RotateLabel", label);
  
 rotateWin = gtk_window_new (GTK_WINDOW_TOPLEVEL);
 gtk_window_set_default_size(GTK_WINDOW(rotateWin), 230, 100);
 g_signal_connect (rotateWin, "destroy",
		   G_CALLBACK (gtk_main_quit),
		   NULL);

 gtk_window_set_title (GTK_WINDOW (rotateWin), "Rotate Image");
 
 vboxMain = gtk_vbox_new (FALSE, 5);
 gtk_container_set_border_width (GTK_CONTAINER (vboxMain), 10);
 gtk_container_add (GTK_CONTAINER (rotateWin), vboxMain);
 
 frame = gtk_frame_new ("Clockwise Rotation");
 gtk_box_pack_start (GTK_BOX (vboxMain), frame, TRUE, TRUE, 0);
 
 vbox = gtk_vbox_new (FALSE, 0);
 gtk_container_set_border_width (GTK_CONTAINER (vbox), 15);
 gtk_container_add (GTK_CONTAINER (frame), vbox);
 
 hbox = gtk_hbox_new (FALSE, 30);
 gtk_box_pack_start (GTK_BOX (vbox), hbox, TRUE, TRUE, 5);
 
 vbox2 = gtk_vbox_new (FALSE, 0);
 gtk_box_pack_start (GTK_BOX (hbox), vbox2, FALSE, TRUE, 5);
 
 label = gtk_label_new ("Degrees :");
 gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);
 gtk_box_pack_start (GTK_BOX (vbox2), label, FALSE, TRUE, 0);
 
 adj = (GtkAdjustment *) gtk_adjustment_new (1.0, 1.0, 360.0, 1.0, 5.0, 0.0);

 spinner = gtk_spin_button_new (adj, 0, 0);
 gtk_spin_button_set_wrap (GTK_SPIN_BUTTON (spinner), TRUE);
 gtk_box_pack_start (GTK_BOX (vbox2), spinner, FALSE, TRUE, 0);
 
 vbox2 = gtk_vbox_new (FALSE, 0);
 gtk_box_pack_start (GTK_BOX (hbox), vbox2, FALSE, TRUE, 5);
 
 rotateButton = gtk_button_new_with_label ("Rotate");
 /* g_signal_connect(rotateButton, "clicked", */
 /* 		  G_CALLBACK (grab_int_value),    */
 /* 		  spinner); */
 g_signal_connect(G_OBJECT(rotateButton), "clicked", G_CALLBACK(CatchEvent), MainViewHandle);

 gtk_box_pack_start (GTK_BOX (vbox2), rotateButton, TRUE, TRUE, 5);
 
 hbox = gtk_hbox_new (FALSE, 0);
 gtk_box_pack_start (GTK_BOX (vboxMain), hbox, FALSE, TRUE, 0);
 
 closeButton = gtk_button_new_with_label ("Close");
 g_signal_connect_swapped (closeButton, "clicked",
			   G_CALLBACK (gtk_widget_destroy),
			   rotateWin);
 gtk_box_pack_start (GTK_BOX (hbox), closeButton, TRUE, TRUE, 5);

 /* gtk_widget_show_all(rotateWin); */

 return rotateWin;
}
